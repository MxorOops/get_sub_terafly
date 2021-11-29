
TEMPLATE	= lib
CONFIG	+= qt plugin warn_off
#CONFIG	+= x86_64
VAA3DPATH = D:/V3D/v3d_external
INCLUDEPATH	+= $$VAA3DPATH/v3d_main/basic_c_fun

HEADERS	+= get_sub_terafly_plugin.h
SOURCES	+= get_sub_terafly_plugin.cpp
SOURCES	+= $$VAA3DPATH/v3d_main/basic_c_fun/v3d_message.cpp

TARGET	= $$qtLibraryTarget(get_sub_terafly)
DESTDIR	= $$VAA3DPATH/bin/plugins/Shuhan/get_sub_terafly/
