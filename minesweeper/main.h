#pragma once
////////////////////////////////////lib.h///////////////////////////////////////
//lib.h:main.cpp需要包含的头文件

//底层函数头文件
#include<windows.h>//windows控制台函数
#include<tchar.h>//字符串的细节

////////////////////////////////////////////////////////////////////////////////

//高级函数头文件 / C/C++运行库
#include<iostream>//控制台输入输出流
#include<fstream>//文件输入输出流
#include<cstdio>//用于使用sprintf,remove
#include<cstdlib>//用于使用exit,rand,srand
#include<ctime>//用于使用time,clock

////////////////////////////////////////////////////////////////////////////////

//自己定义的头文件
#include"include/chartype.h"
#include"include/my_custom.h"//自定义名称
#include"include/my_error.h"//自定义错误码
#include"include/funcs.h"//独立函数
#include"include/structs.h"//结构变量

#define DLL_IMPORT
#include"include/mouse.h"//鼠标控制
#include"include/gameinfo.h"//游戏信息存储
#include"include/button.h"//按钮

////////////////////////////////////lib.h///////////////////////////////////////
