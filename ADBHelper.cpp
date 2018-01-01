#include "StdAfx.h"
#include "ADBHelper.h"
#include <stdlib.h>


void ADBHelper::cap_pull_screen()
{
	system("adb shell screencap -p /sdcard/jump1jump.png");
	system("adb pull /sdcard/jump1jump.png");
}

void ADBHelper::jump(int press_time)
{
	char cmd[256]={0};
	sprintf(cmd,"adb shell input swipe 320 410 320 410 %d",press_time);
	system(cmd);
}
