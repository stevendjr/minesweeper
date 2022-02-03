#pragma once
///////////////////////////////////variables.h//////////////////////////////////
//variables.h:有关变量

int mines[height][length];//定义表示地图的二维数组 
bool ispr[height][length];//是不是已经打印了
bool isfl[height][length];//是不是已经插了旗子
HANDLE window;//窗口句柄
INPUT_RECORD input[128];//输入事件池
DWORD input_num;//输入事件数量
bool isrun;//正在游戏界面 
clock_t start;//一局游戏开始时的计时 

///////////////////////////////////variables.h//////////////////////////////////
