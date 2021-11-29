/* get_sub_terafly_plugin.cpp
 * This is a test plugin, you can use it as a demo.
 * 2021-11-8 : by YourName
 */
 
#include "v3d_message.h"
#include <vector>
#include "get_sub_terafly_plugin.h"
#include <sstream>
#include <iostream>
#include <QFileInfo>
#include "basic_surf_objs.h"
#include <Python.h>
using namespace std;
Q_EXPORT_PLUGIN2(get_sub_terafly, TestPlugin);

static bool is_domenu = true;
static QString img_name_need_read;
static QString marker_name_need_read;
static QString tswc1_need_read;
static QString tswc2_need_read;
static QString gswc_need_read;
static QString swc_name_need_read;
static QString save_dir="";
static V3DLONG x_radius;
static V3DLONG y_radius;
static V3DLONG z_radius;
 
QStringList TestPlugin::menulist() const
{
	return QStringList() 
		<<tr("get_sub_terafly")
		<<tr("about");
}

QStringList TestPlugin::funclist() const
{
	return QStringList()
		<<tr("get_sub")
		<<tr("help");
}

void TestPlugin::domenu(const QString &menu_name, V3DPluginCallback2 &callback, QWidget *parent)
{
    if (menu_name == tr("get_sub_terafly"))
    {
       int flag=get_sub_terafly(callback,parent);
       if (flag==1)
       {
            cout<<endl;
            cout<<"************************"<<endl;
            cout<<"*get_sub_terafly finished!*"<<endl;
            cout<<"************************"<<endl;
       }
    }
	else
	{
        v3d_msg(tr("You can get the binary image by this plugin. "
            "Developed by Shuhan Wu, 2021-10-11"));
	}
}

bool TestPlugin::dofunc(const QString & func_name, const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback,  QWidget * parent)
{
	vector<char*> infiles, inparas, outfiles;
	if(input.size() >= 1) infiles = *((vector<char*> *)input.at(0).p);
	if(input.size() >= 2) inparas = *((vector<char*> *)input.at(1).p);
	if(output.size() >= 1) outfiles = *((vector<char*> *)output.at(0).p);

    if (func_name == tr("get_sub_terafly"))
	{
        v3d_msg("To be implemented1.");
	}
	else return false;

	return true;
}


int get_sub_terafly(V3DPluginCallback2 &callback,QWidget *parent)
{
    //程序可以在terafly模式下挖出子图
    //步骤：打开一张terafly图。在terafly窗口点上marker。选择保存子图的目录。将以marker为中心挖出一个以x_radius，y_radius，z_radius为半径的子图。
    QString inimg_file = callback.getPathTeraFly();
    LandmarkList terafly_landmarks = callback.getLandmarkTeraFly();

    int x_radius = 128;
    int y_radius = 128;
    int z_radius = 128;
    //************set update the dialog
    QDialog * dialog = new QDialog();

    //*************set spinbox
    QSpinBox *x_radius_spinbox = new QSpinBox();
    x_radius_spinbox->setRange(0,10000);
    x_radius_spinbox->setValue(x_radius);
    QSpinBox *y_radius_spinbox = new QSpinBox();
    y_radius_spinbox->setRange(0,10000);
    y_radius_spinbox->setValue(y_radius);
    QSpinBox *z_radius_spinbox = new QSpinBox();
    z_radius_spinbox->setRange(0,10000);
    z_radius_spinbox->setValue(z_radius);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(new QLabel("x radius of the subblock"),0,0);
    layout->addWidget(x_radius_spinbox, 0,1,1,5);
    layout->addWidget(new QLabel("y radius of the subblock"),1,0);
    layout->addWidget(y_radius_spinbox, 1,1,1,5);
    layout->addWidget(new QLabel("z radius of the subblock"),2,0);
    layout->addWidget(z_radius_spinbox, 2,1,1,5);


    QHBoxLayout *hbox2 = new QHBoxLayout();
    QPushButton *ok = new QPushButton(" ok ");
    ok->setDefault(true);
    QPushButton *cancel = new QPushButton("cancel");
    hbox2->addWidget(cancel);
    hbox2->addWidget(ok);

    layout->addLayout(hbox2,6,0,1,6);
    dialog->setLayout(layout);
    QObject::connect(ok, SIGNAL(clicked()), dialog, SLOT(accept()));
    QObject::connect(cancel, SIGNAL(clicked()), dialog, SLOT(reject()));

    //**************run the dialog
    if(dialog->exec() != QDialog::Accepted)
    {
        if (dialog)
        {
            delete dialog;
            dialog=0;
            cout<<"delete dialog"<<endl;
        }
        return false;
    }
//    LandmarkList terafly_landmarks;
//    terafly_landmarks.clear();
//    for(int i=128;i<=2187;i=i+256)
//        for(int j=128;j<=1643;j=j+256)
//            for(int k=128;k<690;k=k+256)
//            {
//                LocationSimple p;
//                p.x=i;
//                p.y=j;
//                p.z=k;
//                p.color.r=255;
//                p.color.g=0;
//                p.color.b=0;
//                terafly_landmarks.push_back(p);
//            }




    //***************get the dialog return values
    x_radius = x_radius_spinbox->value();
    y_radius = y_radius_spinbox->value();
    z_radius = z_radius_spinbox->value();

    if (dialog)
    {
        delete dialog;
        dialog=0;
        cout<<"delete dialog"<<endl;
    }
    QString dir = "";
    dir = QFileDialog::getExistingDirectory(0,
                                  "choose the save dir",
                                  QObject::tr("(*.*)"
                                  ));

//    for(V3DLONG m=0;m<terafly_landmarks.size();m++)
//    {
//        LocationSimple t;
//        t.x = terafly_landmarks[m].x;
//        t.y = terafly_landmarks[m].y;
//        t.z = terafly_landmarks[m].z;


    for(V3DLONG m=0;m<terafly_landmarks.size();m++)
	//for(V3DLONG m=0;m<1;m++)
    {
        LocationSimple t;
        t.x = terafly_landmarks[m].x;
        t.y = terafly_landmarks[m].y;
        t.z = terafly_landmarks[m].z;

        V3DLONG im_cropped_sz[4];

        unsigned char * im_cropped = 0;
        V3DLONG pagesz;
        double l_x = x_radius;
        double l_y = y_radius;
        double l_z = z_radius;

        V3DLONG xb = t.x-l_x;
        V3DLONG xe = t.x+l_x-1;
        V3DLONG yb = t.y-l_y;
        V3DLONG ye = t.y+l_y-1;
        V3DLONG zb = t.z-l_z;
        V3DLONG ze = t.z+l_z-1;
        pagesz = (xe-xb+1)*(ye-yb+1)*(ze-zb+1);
        im_cropped_sz[0] = xe-xb+1;
        im_cropped_sz[1] = ye-yb+1;
        im_cropped_sz[2] = ze-zb+1;
        im_cropped_sz[3] = 1;


        try {im_cropped = new unsigned char [pagesz];}
        catch(...)  {v3d_msg("cannot allocate memory for image_mip."); return false;}


        im_cropped = callback.getSubVolumeTeraFly(inimg_file.toStdString(),xb,xe+1,
                                                  yb,ye+1,zb,ze+1);
        QString tmpstr = "";
//        tmpstr.append("_x").append(QString::number(terafly_landmarks[m].x,'f',3));
//        tmpstr.append("_y").append(QString::number(terafly_landmarks[m].y,'f',3));
//        tmpstr.append("_z").append(QString::number(terafly_landmarks[m].z,'f',3));
        tmpstr.setNum(m+1);
        QString default_name = "TeraSub_"+tmpstr+".tif";
        QString save_path_img = dir+"\\"+default_name;
		//cout <<  55 << endl;
		//printf("%d,%d,%d,%d",im_cropped[0],im_cropped[1],im_cropped[2],im_cropped[3]);
		
		simple_saveimage_wrapper(callback, save_path_img.toStdString().c_str(),(unsigned char *)im_cropped,im_cropped_sz,1);
		if(im_cropped) {delete []im_cropped; im_cropped = 0;}

	}
		
		string indir = string(dir.toStdString().data());

						//printf("%s\n",indir);

		
		Py_SetPythonHome(L"D:/anaconda3/envs/pytorch");
		Py_Initialize();
		PyObject *init_dir = PyList_New(0);	

				//printf("%s\n",indir);

		PyList_Append(init_dir,Py_BuildValue("(s)", indir));

				//printf("%s\n",init_dir);

		PyObject *Module = NULL;
		PyObject *Func = NULL;
		//int argc = 1;
		//wchar_t * argv[] = { L" " };
		//PySys_SetArgv(argc, argv);   //加入argv参数 否则出错
		PyObject *Args = PyTuple_New(1);
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('../../../DL/2021final')");
		Module = PyImport_ImportModule("test1000_many_pad_skunet2decoders_dicesigmoid_padz_Tera17_dicesigmoid"); 
		//Module = PyImport_ImportModule("demo");
		if (Module == NULL)
		{
			Py_Finalize();
			v3d_msg("fail to import module!");
			return -1;
		} 
		Func = PyObject_GetAttrString(Module,"main");
		//Func = PyObject_GetAttrString(Module,"print_hello");
		if (Func == NULL)
		{
			Py_Finalize();
			v3d_msg("fail to import function!");
			return -1;
		}
		PyTuple_SetItem(Args,0,init_dir);	
			PyEval_CallObject(Func, Args);
			//PyEval_CallObject(Func, NULL);


		Py_Finalize();




}

