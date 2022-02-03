#pragma once
//////////////////////////////////////structs.h/////////////////////////////////
//structs.h:有关结构体的定义及变量

typedef struct rect_
{
	console_pos a;
	console_pos b;
}rect;

rect times//时间
{
	{0,0},
	{length+5,2}
},
minecnt//雷计数
{
	{length+5,0},
	{length*2+10,2}
},
new_game//新游戏按钮
{
	{length*3+2,3},
	{length*4+8,5}
},
restart//重新开始按钮
{
	{length*3+2,6},
	{length*4+8,8}
},
m_exit//退出按钮
{
	{length*3+2,9},
	{length*4+8,11}
},
score
{
	{length*3+2,3},
	{length*4+8,5}
};//各种按钮的位置 

typedef struct scoreboard_info_
{
	int gameplayed;//已玩次数
	int gamewon;//已胜次数
}scoreboard_info;

//////////////////////////////////////structs.h/////////////////////////////////
