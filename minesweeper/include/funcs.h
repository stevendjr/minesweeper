#pragma once
////////////////////////////////////funcs.h/////////////////////////////////////
//funcs.h:独立的功能函数

//inline bool KEY_DOWN(int key)//是否按下了某键
//{
//	return((GetAsyncKeyState(key) bitand 0x8000)?true:false);
//}

inline void color(int a)//改变输出颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

inline void gotoxy(short x,short y)//改变输出位置
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{x,y});
}

////////////////////////////////////funcs.h/////////////////////////////////////
