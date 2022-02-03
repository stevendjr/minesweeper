#pragma once
//////////////////////////////////mouse.h///////////////////////////////////////
//mouse.h:����������ĺ���

inline bool operator==(COORD p1,COORD p2)//����COORD�Ĳ���������
{
	return(p1.X==p2.X and p1.Y==p2.Y);
}

inline COORD mouse_click_pos(int i)//����ڿ���̨�ϵ����λ��
{
	return input[i].Event.MouseEvent.dwMousePosition;
}

bool mouse_click(COORD p1,COORD p2,int i,DWORD key)//�Ƿ�������ָ����������
{
	COORD p=mouse_click_pos(i);
	if(p.X>=p1.X and p.X<=p2.X and p.Y>=p1.Y and p.Y<=p2.Y and 
		input[i].Event.MouseEvent.dwButtonState == key and
		!input[i].Event.MouseEvent.dwEventFlags)
	{
		return true;
	}
	return false;
}

bool mouse_click(COORD p1,int i,DWORD key)//�Ƿ�������ָ����λ��
{
	COORD p=mouse_click_pos(i);
	if(p==p1 and input[i].Event.MouseEvent.dwButtonState == key and
		!input[i].Event.MouseEvent.dwEventFlags)
	{
		return true;
	}
	return false;
}

COORD click_gezi(int x,DWORD key)//���ص���ĸ������У�������ڸ����ϣ��򷵻�-1
{
	COORD pos,returned,get;
	for(int i=0;i<height;i++)
		for(int j=0;j<length;j++)
		{
			get=mouse_click_pos(x);
			pos.X=(i+1)*3-1;
			pos.Y=j*2+4;
			if(get==pos)
			{
				returned.Y=i;
				returned.X=j;
				return returned;
			} 
		}
	returned.X=-1;
	returned.Y=-1;
	return returned;
}

//ע����δ���Ƚϵײ㣬���߲���ϸ����ֻ��֪�����÷�������
////////////////////////////////////mouse.h/////////////////////////////////////
