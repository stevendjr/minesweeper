#pragma once

#include<fstream>
#include"structs.h"
#include"my_custom.h"

using namespace my_using;

void get_info(ifstream & fin,scoreboard_info & info)//获取计分板信息
{
	fin>>info.gameplayed>>info.gamewon;
}

void change_write_info(scoreboard_info & info,bool & iswin)//修改并写入计分板信息
{
	ofstream fout("gameinfo.json");//打开文件
	info.gameplayed++;//增加一局
	if(iswin)//赢了
	{
		info.gamewon++;//赢了一局
	}
	fout<<info.gameplayed<<" "<<info.gamewon;//输出
	fout.close();//关闭文件
}
