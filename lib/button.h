#pragma once
/////////////////////////////////////button.h///////////////////////////////////
//button.h:有关按钮的一系列操作

#include"my_custom.h"
#include"funcs.h"
using namespace my_using; 

void button_show(console_pos upleft,console_pos downright,const char *text)
//输出按钮 
{
	gotoxy(upleft.X,upleft.Y);
	cout<<"┏";
	for(int i=upleft.X; i<downright.X-1; i++)
	{
		cout<<"━";
	}
	cout<<"┓ ";
	gotoxy(upleft.X,upleft.Y+1);
	for(int i=upleft.Y+1; i<downright.Y; i++)
	{
		cout<<"┃ ";
		if(i==(upleft.Y+downright.Y)/2)
		{
			for(int i=0; i<(downright.X-upleft.X-1-int(strlen(text)))/2-1; i++)
			{
				cout<<" ";
			}
			for(int i=0; i<int(strlen(text)); i++)
				cout<<text[i];
			for(int i=0; i<(downright.X-upleft.X-1-int(strlen(text)))/2-1; i++)
			{
				cout<<" ";
			}
		}
		else
		{
			for(int j=upleft.X+1; j<downright.X-2; j++)
			{
				cout<<" ";
			}
		}
		cout<<" ┃ ";
		gotoxy(upleft.X,i+1);
	}
	cout<<"┗";
	for(int i=upleft.X; i<downright.X-1; i++)
	{
		cout<<"━";
	}
	cout<<"┛ ";
}

void unbtnshow(console_pos upleft,console_pos downright)
//让按钮消失 
{
	gotoxy(upleft.X,upleft.Y);
	for(int j=upleft.Y; j<downright.Y+1; j++)
	{
		for(int i=upleft.X; i<downright.X+1; i++)
		{
			cout<<" ";
		}
		gotoxy(upleft.X,j+1);
	}
}

///////////////////////////////////button.h/////////////////////////////////////
