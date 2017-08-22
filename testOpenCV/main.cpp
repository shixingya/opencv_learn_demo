#include <opencv.hpp>
#include <Windows.h>  
#include <iostream>   
#include <string>   
using namespace cv;

void ImageCorrosion(Mat &img) //图像腐蚀
{
	Mat element =getStructuringElement(MORPH_RECT,Size(2,5));
	Mat desImage;
	erode(img, desImage, element);
	imshow("图像腐蚀",desImage);
}

void ImageBlurred(Mat &img) //图像模糊
{
	Mat desImage;
	blur(img,desImage,Size(7,7));
	imshow("图像模糊",desImage);
}

void ImageCanny(Mat &img)// canny 边缘检测
{
	Mat dstImage,edge,grayImage;

	//1.创建于img同类型和大小的矩阵dstImage;
	dstImage.create(img.size(), img.type());

	//2.将原图转换为灰度图像
	//此代码的OpenCV2 版为
	//cvtColor(img, grayImage, CV_BGR2GRAY);
	//此代码的OpenCV3 版为
	cvtColor(img, grayImage, COLOR_BGR2GRAY);

	//3.先使用3*3 内核来降噪
	blur(grayImage, edge, Size(3,3));
	//4.运行Canny算子
	Canny(edge,edge, 3,9,3);
	imshow("canny 边缘检测",edge);
}
void read_ShowVideo(const char* video_path) //读取视频
{
	VideoCapture capture;
	wchar_t exeFullPath[MAX_PATH]; // Full path
	std::string strPath = "";
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	char ch[260];
	 char DefChar = ' ';
	WideCharToMultiByte(CP_ACP,0,exeFullPath,-1, ch,260,&DefChar, NULL);

	//A std:string  using the char* constructor. 
	std::string ss(ch);
	int lastPos=ss.find_last_of("\\");
 
	ss=ss.substr(0,lastPos+1) +"video.avi";
	capture.open(ss);
	while (1)
	{
		Mat frame;
		capture>>frame;
		imshow("读取视频",frame);
		waitKey(20);
	}
};
void read_getCameraData() //摄像头采集图像
{
	VideoCapture capture;
	capture.open(0);
	while (1)
	{
		Mat frame;
		capture>>frame;
		//ImageCanny(frame); 高斯模糊
		imshow("读取视频",frame);
		waitKey(20);
	}
};

int ppmain()
{
	Mat img=imread("C://Users//Administrator//Pictures//1.png");
	//imshow("原图",img);
	//ImageCorrosion(img);
	//ImageBlurred(img);
	//ImageCanny(img);
	//read_ShowVideo("video.avi");
	read_getCameraData();
	//int a[5]={8,3,1,5,0};
	//bubbleSort(a,5);
	waitKey(0);
	return 0;
}
