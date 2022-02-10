#include<iostream>
#include<fstream>
#include"my_custom.h"
#include"structs.h"

#pragma comment(lib,"lib/gameinfo.lib")

#ifndef DLL_IMPORT
#define GAMEINFODLL __declspec(dllexport)
#else
#define GAMEINFODLL __declspec(dllimport)
#endif

extern "C"
{
	GAMEINFODLL void get_info(std::ifstream & fin,scoreboard_info & info);//获取计分板信息
	GAMEINFODLL void change_write_info(scoreboard_info & info,bool & iswin);//修改并写入计分板信息
}
