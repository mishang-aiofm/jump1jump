// Jump1Jump.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ADBHelper.h"
#include "JumpHelper.h"




int _tmain(int argc, char* argv[])
{
	if(argc>1)
		JumpHelper::factor=atof(argv[1]);
	
	JumpHelper jumper;
	jumper.Do();
	return 0;
}

