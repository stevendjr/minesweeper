#include<iso646.h>
#include"my_custom.h"

#pragma comment(lib,"lib/mouse.lib")

#ifdef DLL_IMPORT
#define MOUSEDLL __declspec(dllimport)
#else
#define MOUSEDLL __declspec(dllexport)
#endif

extern "C"
{
	MOUSEDLL bool equal(COORD p1,COORD p2);//����COORD�Ĳ���������
	MOUSEDLL COORD mouse_click_pos(PINPUT_RECORD input,int i);//����ڿ���̨�ϵ����λ��
	MOUSEDLL bool mouse_click(PINPUT_RECORD input,COORD p1,COORD p2,int i,DWORD key);//�Ƿ�������ָ����������
	MOUSEDLL bool mouse_click_point(PINPUT_RECORD input,COORD p1,int i,DWORD key);//�Ƿ�������ָ����λ��
	MOUSEDLL COORD click_gezi(PINPUT_RECORD input,int x,DWORD key);//���ص���ĸ������У�������ڸ����ϣ��򷵻�-1
}
