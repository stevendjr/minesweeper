#pragma once
//////////////////////////////////mouse.h///////////////////////////////////////
//mouse.h:管理鼠标点击的函数

inline bool operator==(COORD p1,COORD p2)//对于COORD的操作符重载
{
	return(p1.X==p2.X and p1.Y==p2.Y);
}

inline COORD mouse_click_pos(int i)//鼠标在控制台上点击的位置
{
	return input[i].Event.MouseEvent.dwMousePosition;
}

bool mouse_click(COORD p1,COORD p2,int i,DWORD key)//是否点击在了指定的区域内
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

bool mouse_click(COORD p1,int i,DWORD key)//是否点击在了指定的位置
{
	COORD p=mouse_click_pos(i);
	if(p==p1 and input[i].Event.MouseEvent.dwButtonState == key and
		!input[i].Event.MouseEvent.dwEventFlags)
	{
		return true;
	}
	return false;
}

COORD click_gezi(int x,DWORD key)//返回点击的格子行列，如果不在格子上，则返回-1
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

//注：这段代码比较底层，读者不必细读，只需知道调用方法即可
////////////////////////////////////mouse.h/////////////////////////////////////
