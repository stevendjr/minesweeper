#pragma once
////////////////////////////////////lib.h///////////////////////////////////////
//lib.h:main.cpp��Ҫ������ͷ�ļ�

//�ײ㺯��ͷ�ļ�
#include<windows.h>//windows����̨����
#include<tchar.h>//�ַ�����ϸ��

////////////////////////////////////////////////////////////////////////////////

//�߼�����ͷ�ļ� / C/C++���п�
#include<iostream>//����̨���������
#include<fstream>//�ļ����������
int __cdecl sprintf(char * __restrict__ _Dest,
	const char * __restrict__ _Format,...);
#include<cstdlib>//����ʹ��exit,rand,srand
#include<ctime>//����ʹ��time,clock

////////////////////////////////////////////////////////////////////////////////

//�Լ������ͷ�ļ�
#include"lib/my_custom.h"//�Զ������� 
#include"lib/funcs.h"//�������� 
#include"lib/button.h"//��ť���� 
#include"lib/structs.h"//�ṹ����
#include"lib/variables.h"//�������� 
#include"lib/mouse.h"//������ 
#include"lib/gameinfo.h"

////////////////////////////////////lib.h///////////////////////////////////////
