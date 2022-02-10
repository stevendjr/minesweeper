#include<iso646.h>
#include"my_custom.h"

#pragma comment(lib,"lib/mouse.lib")

#ifdef DLL_IMPORT
#define MOUSEDLL __declspec(dllimport)
#else
#define MOUSEDLL __declspec(dllexport)
#endif

extern "C"
{
	MOUSEDLL bool equal(COORD p1,COORD p2);//对于COORD的操作符重载
	MOUSEDLL COORD mouse_click_pos(PINPUT_RECORD input,int i);//鼠标在控制台上点击的位置
	MOUSEDLL bool mouse_click(PINPUT_RECORD input,COORD p1,COORD p2,int i,DWORD key);//是否点击在了指定的区域内
	MOUSEDLL bool mouse_click_point(PINPUT_RECORD input,COORD p1,int i,DWORD key);//是否点击在了指定的位置
	MOUSEDLL COORD click_gezi(PINPUT_RECORD input,int x,DWORD key);//返回点击的格子行列，如果不在格子上，则返回-1
}
