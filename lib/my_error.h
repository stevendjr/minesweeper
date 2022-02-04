#pragma once

///////////////////////////////////my_error.h///////////////////////////////////
//my_error.h:定义的错误处理

#include"my_custom.h"
#include"funcs.h"
using namespace my_using;

#define CANNOT_START_SCOREBOARD 0xe0000001

void error(int errcode)
{
	gotoxy(0,length*2+5);
	cout<<"error:"<<hex<<errcode<<dec;
}

/////////////////////////////////////my_error.h/////////////////////////////////
