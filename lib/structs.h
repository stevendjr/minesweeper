#pragma once
//////////////////////////////////////structs.h/////////////////////////////////
//structs.h:�йؽṹ��Ķ��弰����

typedef struct rect_
{
	console_pos a;
	console_pos b;
}rect;

rect times//ʱ��
{
	{0,0},
	{length+5,2}
},
minecnt//�׼���
{
	{length+5,0},
	{length*2+10,2}
},
new_game//����Ϸ��ť
{
	{length*3+2,3},
	{length*4+8,5}
},
restart//���¿�ʼ��ť
{
	{length*3+2,6},
	{length*4+8,8}
},
m_exit//�˳���ť
{
	{length*3+2,9},
	{length*4+8,11}
},
score
{
	{length*3+2,3},
	{length*4+8,5}
};//���ְ�ť��λ�� 

typedef struct scoreboard_info_
{
	int gameplayed;//�������
	int gamewon;//��ʤ����
}scoreboard_info;

//////////////////////////////////////structs.h/////////////////////////////////
