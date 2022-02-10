#include<iostream>
#include"my_custom.h"
#include"funcs.h"

#pragma comment(lib,"lib/button.lib")

#ifdef DLL_IMPORT
#define BUTTONDLL __declspec(dllimport)
#else
#define BUTTONDLL __declspec(dllexport)
#endif

extern "C"
{
	BUTTONDLL void button_show(console_pos upleft,console_pos downright,const char *text);
	BUTTONDLL void unbtnshow(console_pos upleft,console_pos downright);
}
