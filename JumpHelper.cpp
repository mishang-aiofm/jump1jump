#include "StdAfx.h"
#include "JumpHelper.h"
#include "include\opencv\highgui.h"
#include "ADBHelper.h"

#define WINDOWNAME	"Jump1Jump By chuanch@ustc"
float JumpHelper::factor=1.0f;
void onClick(int event,int x,int y,int flags,void* param)
{
	if(event!=CV_EVENT_LBUTTONUP)
		return;
	JumpHelper*	jumper=(JumpHelper*)param;
	jumper->target_pos_x=x;
	jumper->target_pos_y=y;
	CvPoint chessLoc=jumper->LocateChess();
	printf("target position:(%d,%d)",x,y);
	float distance=sqrt(powf(jumper->target_pos_x-chessLoc.x,2)+powf(jumper->target_pos_y-chessLoc.y,2));
	ADBHelper::jump(distance*JumpHelper::factor);
	Sleep(1000);
	ADBHelper::cap_pull_screen();
	jumper->ReadImage();
	jumper->Show();
}
JumpHelper::JumpHelper(void)
{	
	image=NULL;
	img_chess_template=NULL;
	matchResult=NULL;
	img_chess_template=cvLoadImage("chess.png");
	cvNamedWindow(WINDOWNAME,0);
	cvSetMouseCallback(WINDOWNAME,onClick,(void*)this);
}


JumpHelper::~JumpHelper(void)
{
	cvReleaseImage(&image);
	cvReleaseImage(&img_chess_template);
	cvReleaseImage(&matchResult);
}


void JumpHelper::Do()
{	
	ADBHelper::cap_pull_screen();
	ReadImage();
	LocateChess();
	Show();
	cvWaitKey(0);
}

void JumpHelper::ReadImage()
{
	const char* filename="jump1jump.png";
	if (image)
	{
		cvReleaseImage(&image);
	}
	
	image=cvLoadImage(filename);
	if (!matchResult)
	{
		cvResizeWindow(WINDOWNAME,image->width/3,image->height/3);
		matchResult=cvCreateImage(cvSize(image->width-img_chess_template->width+1,image->height-img_chess_template->height+1),IPL_DEPTH_32F,1);
	}
}


CvPoint JumpHelper::LocateChess()
{	
	cvMatchTemplate(image,img_chess_template,matchResult,CV_TM_SQDIFF);
	double min_val=0,max_val=0;
	CvPoint min_loc,max_loc;
	cvMinMaxLoc(matchResult,&min_val,&max_val,&min_loc,&max_loc);
	cvRectangle(image,min_loc,cvPoint(min_loc.x+img_chess_template->width,min_loc.y+img_chess_template->height),cvScalar(0,0,255),2);
	printf("chess location:(%d,%d)\n",min_loc.x,min_loc.y);
	return cvPoint(min_loc.x+img_chess_template->width/2,min_loc.y+img_chess_template->height);
}

void JumpHelper::Show()
{	
	cvShowImage(WINDOWNAME,image);
	cvResizeWindow(WINDOWNAME,image->width/3,image->height/3);
}
