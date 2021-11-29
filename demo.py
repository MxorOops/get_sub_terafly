# -*-coding:utf-8 -*-
import io
import sys
#改变标准输出的默认编码
sys.stdout=io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')
# from cv2 import cv2
# import libtiff
# import numpy as np


# def py_binarization(data_list, XDim, YDim, ZDim, CDim):
#     with open(r'C:\Users\37992\Desktop\demo.txt', 'w') as f:
#         f.write(str(max(data_list)))
#     image = np.array(data_list).reshape([XDim, YDim, ZDim, CDim])
#     image = image.transpose(0, 1, 3, 2)
#     for z in range(image.shape[3]):
#         if image.shape[2] != 1:
#             img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#     with open('C:/Users/37992/Desktop/demo.txt', 'a') as f:
#         f.write('\nsuccess1')
#     image = (image >= thres).astype(int) * 255
#     with open('C:/Users/37992/Desktop/demo.txt', 'a') as f:
#         f.write('\nsuccess2')
#     image_list = list(image.reshape([XDim * YDim * ZDim * CDim]))
#     with open('C:/Users/37992/Desktop/demo.txt', 'a') as f:
#         f.write('\nsuccess')
#         f.write('\n' + str(min(image_list)))
#     return image_list
#
# def getsub(data_list, XDim, YDim, ZDim, CDim):
#     with open(r'C:\Users\37992\Desktop\demo.txt', 'w') as f:
#         f.write(str(max(data_list)))
#     image = np.array(data_list).reshape([XDim, YDim, ZDim, CDim])
#     image = image.transpose(0, 1, 3, 2)
#     for z in range(image.shape[3]):
#     	image_list = list(image.reshape([XDim * YDim * ZDim * CDim]))
#     with open('C:/Users/37992/Desktop/demo.txt', 'a') as f:
#         f.write('\n' + str(image_list))
#     return image_list

def get_sub(data_list, XDim, YDim, ZDim, CDim):
    with open(r'C:\Users\37992\Desktop\demo.txt', 'a') as f:
        f.write( str(data_list) + '\n\n')

def print_hello(data_list, XDim, YDim, ZDim, CDim):
    with open(r'C:\Users\37992\Desktop\demo.txt', 'a') as f:
        f.write('\nhello world!')


# def show_image(path1, path2):
#     # with open(r'C:\Users\37992\Desktop\demo.txt', 'a') as f:
#     #     f.write('\n' + path)
#     #     img = cv2.imread(path, -1)
#     #     f.write('\n' + str(img.shape))
#     # cv2.imshow('1', img)
#     # if cv2.waitKey(0) == 27:
#     #     cv2.destroyAllWindows()
#     tif1 = libtiff.TIFF.open(path1, mode='r')
#     tif2 = libtiff.TIFF.open(path2, mode='r')
#     image1 = tif1.read_image()
#     image2 = tif2.read_image()
#     try:
#         # with open(r'C:\Users\37992\Desktop\demo.txt', 'a') as f:
#         #     f.write('\n' + str(image.shape))
#         cv2.imshow('1', image1)
#         cv2.imshow('2', image2)
#         if cv2.waitKey(0) == 27:
#             cv2.destroyAllWindows()
#     except:
#         with open(r'C:\Users\37992\Desktop\demo.txt', 'a') as f:
#             f.write('\nfail')


if __name__ == '__main__':
    print_hello()
    pass
