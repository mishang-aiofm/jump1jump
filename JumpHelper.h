#pragma once
#include "include/opencv/cv.h"
class JumpHelper
{
public:
	JumpHelper(void);
	~JumpHelper(void);
	
	void	Do();

	void	ReadImage();
	CvPoint	LocateChess();
	void	Show();
	int target_pos_x;
	int target_pos_y;
	static float factor;
private:
	IplImage*	image;
	IplImage*	img_chess_template;
	IplImage*	matchResult;
	
};

