#pragma once

#include<fstream>
#include"structs.h"
#include"my_custom.h"

using namespace my_using;

void get_info(ifstream & fin,scoreboard_info & info)//��ȡ�Ʒְ���Ϣ
{
	fin>>info.gameplayed>>info.gamewon;
}

void change_write_info(scoreboard_info & info,bool & iswin)//�޸Ĳ�д��Ʒְ���Ϣ
{
	ofstream fout("gameinfo.json");//���ļ�
	info.gameplayed++;//����һ��
	if(iswin)//Ӯ��
	{
		info.gamewon++;//Ӯ��һ��
	}
	fout<<info.gameplayed<<" "<<info.gamewon;//���
	fout.close();//�ر��ļ�
}
