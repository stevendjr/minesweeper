//扫雷游戏2.0.1
//注：此版本需配合scoreboard程序使用
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
using namespace my_using;

int mines[height][length];//定义表示地图的二维数组
bool ispr[height][length];//是不是已经打印了
bool isfl[height][length];//是不是已经插了旗子
HANDLE window;//窗口句柄
INPUT_RECORD input[128];//输入事件池
DWORD input_num;//输入事件数量
bool isrun;//正在游戏界面
clock_t start;//一局游戏开始时的计时

void out_gezi()//输出游戏棋盘
{
	gotoxy(0, 3);//到达初始位置
	color(back_white);//设置白色背景色
	_tout << "┏";//输出左上角
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "━━┳";
	}
	_tout << "━━┓" ;
	for (int i = 0; i < height - 1; i++)
	{
		_tout << " " << endl << "┃";
		for (int j = 0; j < length - 1; j++)
		{
			_tout << "  ┃";
		}
		_tout << "  ┃ ";
		_tout << endl << "┣";
		for (int j = 0; j < length - 1; j++)
		{
			_tout << "━━╋";
		}
		_tout << "━━┫";
	}
	_tout << " " << endl << "┃";
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "  ┃";
	}
	_tout << "  ┃ ";
	_tout << endl << "┗";
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "━━┻";
	}
	_tout << "━━┛ ";
}

void print(int i, int j) //输出格子里的内容
{
	int col = back_white;//设置背景色
	switch (mines[i][j])//根据格子内容选择颜色
	{
		case -1://格子里是雷
			col |= FOREGROUND_INTENSITY | FOREGROUND_RED;//亮红色
			break;
		case 0:
			col |= FOREGROUND_BLUE;//蓝色
			break;
		case 1:
			col |= FOREGROUND_INTENSITY | FOREGROUND_GREEN;//亮绿色
			break;
		case 2:
			col |= FOREGROUND_RED | FOREGROUND_GREEN;//黄色
			break;
		case 3:
			col |= FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;//亮紫色
			break;
		case 4:
			col |= FOREGROUND_BLUE | FOREGROUND_GREEN;//深蓝色
			break;
		default:
			col |= FOREGROUND_RED;//红色
			break;
	}
	gotoxy((i + 1) * 3 - 1, j * 2 + 4);//计算并来到指定位置
	color(col);//设置颜色
	if (mines[i][j] == -1)//如果是雷
		_tout << "X";
	else//否则
		_tout << mines[i][j];//原样输出
}

void spawn(int o, int p) //生成扫雷地图
{
	srand((unsigned)time(0));//设置随机种子
	int x, y,lei;
	int i, j, k, l; //循环变量
	i=0;
	while(i<num)//如果还能再生成
	{
		x=rand()%height;//随机的行数
		y=rand()%length;//随机的列数
		if(mines[x][y]==-1//如果格子里已经有雷
				or (x>=o-1 and x<=o+1 and y>=p-1 and y<=p+1)//或者在点击位置附近
				)
			continue;//跳过此位置
		mines[x][y]=-1;//否则，将该格子设为雷
		i++;//增加已有雷数
	}
	for (i = 0; i < height; i++)
		for (j = 0; j < length; j++)
		{
			if (mines[i][j] != -1) //如果该格不是雷，则判断雷数
			{
				lei = 0;//雷数为0
				for (k = i - (i != 0); k <= i + (i != height - 1); k++)
					for (l = j - (j != 0); l <= j + (j != length - 1); l++)
						if (mines[k][l] == -1)//是雷
							lei++;//雷数加1
				mines[i][j] = lei; //填入附近雷数
			}
		}//对格子附近雷的计算
}

int menu(int i) //进入菜单时的操作
{
	if (mouse_click(input,new_game.a, new_game.b, i, MK_LEFT))//点击了new_game按钮
	{
		unbtnshow(new_game.a, new_game.b);
		unbtnshow(restart.a,restart.b);
		unbtnshow(m_exit.a, m_exit.b);//隐藏三个按钮
		return NEW_GAME;
	}
	else if(mouse_click(input,restart.a, restart.b, i, MK_LEFT))
	{
		unbtnshow(new_game.a, new_game.b);
		unbtnshow(restart.a,restart.b);
		unbtnshow(m_exit.a, m_exit.b);//隐藏三个按钮
		return RESTART;
	}
	else if (mouse_click(input,m_exit.a, m_exit.b, i, MK_LEFT))//点击了exit按钮
	{
		system("cls");//清屏
		exit(0);//退出游戏
	}
	return NONE;//没有点击
}

bool fan(int x, int y) //翻开一个格子
{
	if (ispr[y][x])//已经翻开了
		return false;//没有爆炸
	print(x, y);//显示内容
	switch (mines[x][y])
	{
		case -1://格子里是雷
			return true;//爆炸了
		case 0://翻开空白区
			for (int l = x - (x != 0); l <= x + (x != height - 1); l++)
				for (int k = y - (y != 0); k <= y + (y != length - 1); k++)
				{
					if (mines[l][k] != -1 //不是雷
							and !ispr[k][l]//没有显示
							)
					{
						ispr[y][x] = true;//打印了
						fan(l, k);//递归翻开下一个
					}
				}
			break;
		default:
			ispr[y][x] = true;//翻开
			break;
	}
	return false;//没有爆炸
	//注：注意这个函数调用时的参数顺序，应将行数放在第二个参数，列数放在第一个参数
}

/*void pr_ispr()//调试函数，请忽略
{
	gotoxy(0, 20);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			_tout << ispr[i][j];
		}
		_tout << endl;
	}
}
*/
void flag(int y, int x, int &leicnt) //插旗子或拔出旗子
{
	if (!ispr[y][x])//没有显示
	{
		gotoxy((x + 1) * 3 - 1, y * 2 + 4);//来到指定位置
		color(FOREGROUND_RED | FOREGROUND_INTENSITY | back_white);//设置颜色
		if (!isfl[y][x])//没有插旗子
		{
			_tout << TEXT("F");
			isfl[y][x] = true;//已经插了
			--leicnt;//雷数减1
		}
		else//已经插了
		{
			_tout << " ";
			isfl[y][x] = false;//拔出旗子
			++leicnt;//雷数加1
		}
	}
}

void initialize()//开始新的一局游戏时的初始化
{
	memset(ispr, false, sizeof(ispr));//清空打印格子
	memset(isfl, false, sizeof(isfl));//清空棋子地图
	system("cls");//清屏
	system("color F0");//设置背景
	char st[80];//准备设置的字符串
	sprintf_s(st, (size_t)_countof(st), "mode con cols=%d lines=%d", length * 7, height * 2 + 6);//向字符串输出文本
	system(st);//设置控制台的长和宽
	SetConsoleMode(window, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
	               ENABLE_MOUSE_INPUT);
	button_show(times.a, times.b, " ");//输出时间框
	button_show(minecnt.a, minecnt.b, " ");//输出雷数框
	button_show(score.a,score.b,"scoreboard");
	button_show(reset_score.a,reset_score.b,"reset score ");
	gotoxy(2, 1);
	_tout << TEXT("time:");
	gotoxy(length + 2, 1);
	_tout << TEXT(":");
	gotoxy(length + 7, 1);
	_tout << TEXT("X:");
	start = clock();//得到开始时间
	out_gezi();//输出棋盘
}

void out_time()//输出用时信息
{
	color(back_white);
	gotoxy(length, 1);
	clock_t rtnow = (clock() - start) / CLOCKS_PER_SEC;//计算用时：（现在时间-开始时间）/时间单位
	if (rtnow / 600 == 0)//如果不满10分钟
		_tout << 0;//补0
	_tout << rtnow / 60;//输出分钟
	gotoxy(length + 3, 1);
	if (rtnow % 60 / 10 == 0)//如果秒数不满10秒
		_tout << 0;//补0
	_tout << rtnow % 60;//输出秒
}

void out_leicnt(int leicnt)//输出剩余雷数
{
	gotoxy(length * 3 - 1, 1);
	if (leicnt >= 0 and leicnt < 10)//雷数在0~9之间
		_tout << TEXT(" ");//补空格
	_tout << leicnt;//输出雷数
	//注：这段代码无法正确处理leicnt<=-10 or leicnt>=100时的情况
}

bool win()//是不是已经赢了
{
	bool flag = true;//标志变量
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (mines[i][j] != -1 and not ispr[j][i])//格子里不是雷并且没有翻开
			{
				flag = false;//没有赢
			}
		}
	}
	return flag;
}

void gameover(scoreboard_info & info,bool & iswin)
{
	isrun=false;
	change_write_info(info,iswin);
	color(back_white);//设置背景
	gotoxy(length * 3 + 4, 1);//到达指定位置
	_tout<<"                                ";
	gotoxy(length * 3 + 4, 2);//到达指定位置
	_tout<<"                        ";
	gotoxy(length * 3 + 4, 1);//到达指定位置
	if (iswin)//是赢了
		_tout << TEXT("你赢了。祝贺您！");
	else//是输了
		_tout << TEXT("不好意思，您输了。再试一次！");
	button_show(new_game.a, new_game.b, "new_game");//输出new_game按钮
	button_show(restart.a,restart.b,"restart ");//输出restart按钮
	button_show(m_exit.a, m_exit.b, "exit");//输出exit按钮
}

void doublekey(console_pos get,bool & iswin,scoreboard_info & info)//双键点击
{
	int cnt = 0;
	for (int k = get.X - (get.X != 0); k <= get.X + (get.X != height - 1); k++)
		for (int l = get.Y - (get.Y != 0); l <= get.Y + (get.Y != length - 1); l++)
			if (isfl[k][l])//插了旗子
				cnt++;
	//查看附近的旗子个数
	if (cnt == mines[get.Y][get.X])//附近有和格子里数字相同数量的旗子
	{
		for (int k = get.X - (get.X != 0); k <= get.X + (get.X != height - 1); k++)
			for (int l = get.Y - (get.Y != 0); l <= get.Y + (get.Y != length - 1); l++)
				if (!ispr[k][l] and !isfl[k][l])//没有打印，也没有旗子
					if (fan(l, k))//翻出了雷，下略
					{
						iswin = false;
						gameover(info,iswin);
						return;
					}
	}
	//注：这个功能是双键自动翻开，在玩家这一格附近如果已经标记了格子数量的旗子，按双键就能
	//翻开其他格子，即使玩家标错了旗子
}

void mouse(int a,int & leicnt,scoreboard_info & info)//有关鼠标的操作
{
	static bool iswin,//赢了
		isfirst = true,isrestart=false;//是第一次点击
	//pr_ispr();
	console_pos get;//得到的位置
	if (isrun)//正在游戏
	{
		if (win())//赢了
		{
			iswin = true;//输赢设为真
			gameover(info,iswin);
			return;
		}
		get = click_gezi(input,a, MK_LEFT);//点击的格子
		if (get.X != -1//点到格子上
				and !input[a].Event.MouseEvent.dwEventFlags//是按下按钮
				)
		{
			switch (input[a].Event.MouseEvent.dwButtonState)//按下的是哪个按钮
			{
				case MK_LEFT://左键
					if (isfirst and not isrestart)//是第一次点击
					{
						memset(mines, false, sizeof(mines));//清空地图
						spawn(get.X, get.Y);//生成地图
						isfirst = false;//现在不是第一次点击
					}
					if (!isfl[get.X][get.Y])//如果格子上没有旗子
					{
						if (fan(get.Y, get.X))//如果翻出了雷
						{
							iswin = false;//不是赢了
							gameover(info,iswin);
							return;
						}
					}
					break;
				case MK_RIGHT://右键
					flag(get.X, get.Y, leicnt);//插旗子或拔出旗子
					break;
				case MK_LEFT | MK_RIGHT://左右双键
					doublekey(get,iswin,info);
			}
		}
		else if(mouse_click(input,score.a,score.b,a,MK_LEFT))//点击了scoreboard按钮
		{
			TCHAR szpath[30]=TEXT("scoreboard.exe");
			STARTUPINFO startinfo={sizeof(STARTUPINFO),NULL,NULL};
			PROCESS_INFORMATION ppi={0};
			if(not CreateProcess(NULL,
					szpath,//命令行
					NULL,NULL,false,//默认安全和不继承
					CREATE_NEW_CONSOLE,//使用新控制台
					NULL,NULL,//无环境块和默认目录
					&startinfo,//启动信息
					&ppi)//进程句柄
					)
			{
				error(CANNOT_START_SCOREBOARD);//无法打开scoreboard程序
			}
		}
		else if(mouse_click(input,reset_score.a,reset_score.b,a,MK_LEFT))//点击了reset score按钮
		{
			remove("gameinfo.json");//删除文件
		}
	}
	else
	{
		switch(menu(a))
		{
			case NEW_GAME:
				initialize();//初始化
				isrun = true;//在游戏界面
				isfirst = true;//等待第一次点击
				leicnt=num;//初始化雷计数
				isrestart=false;//不更新地图
				break;
			case RESTART:
				initialize();//初始化
				isrun = true;//在游戏界面
				isfirst = true;//等待第一次点击
				leicnt=num;//初始化雷计数
				isrestart=true;//更新地图
				gotoxy(length * 3 + 4, 1);//到达指定位置
				_tout<<TEXT("这一局的游戏和上一次相同。小心！");
				gotoxy(length * 3 + 4, 2);//到达指定位置
				_tout<<TEXT("您第一次单击就可能会输。");
		}
	}
}

void key(int i)//有关键盘按键的操作，保留，供将来使用
{
	//注：接下来需要实现的功能：
	//   1.通过键盘来操控游戏
	//   2.通过箭头来移动，通过回车来翻开，通过空格来插/拔旗子
}

void compare_version()
{
	OSVERSIONINFOEX osver={sizeof(OSVERSIONINFOEX)};
	osver.dwMajorVersion=6;
	osver.dwMinorVersion=2;
	osver.dwPlatformId=VER_PLATFORM_WIN32_NT;
	DWORDLONG dwlConditionMask=0;
	VER_SET_CONDITION(dwlConditionMask,VER_MAJORVERSION,VER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask,VER_MINORVERSION,VER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask,VER_PLATFORMID,VER_EQUAL);
	if(VerifyVersionInfo(&osver,
			VER_MAJORVERSION bitor VER_MINORVERSION bitor VER_PLATFORMID,
			dwlConditionMask))
	{//满足要求
		return;
	}
	else
	{//不满足要求
		_tout<<TEXT("此系统不是Windows 10。这个游戏只能在Windows 10上运行。");
		Sleep(2000);
		exit(0);
	}
}

int _tmain()//主函数
{
	compare_version();//比较系统版本
	window = GetStdHandle(STD_INPUT_HANDLE);//获取窗口句柄
	SetConsoleTitle(TEXT("扫雷"));//设置窗口标题
	initialize();//初始化
	isrun = true;//在游戏界面
	int leicnt = num;//初始化雷计数
	ifstream fin("gameinfo.json");//打开读入文件
	scoreboard_info info;//信息
	if(fin.is_open())//打开了
	{
		get_info(fin,info);//读信息
	}
	else
	{
		memset(&info,0,sizeof(info));//清空信息结构
	}
	fin.close();//关闭文件
	while (true)
	{
		ReadConsoleInput(window, input, 128, &input_num);//读取输入缓冲区事件
		if (isrun)//在运行
		{
			out_time();//输出时间
			out_leicnt(leicnt);//输出雷数
		}
		for (int i = 0; i < int(input_num); i++)//逐个检索时间
		{
			switch (input[i].EventType)//事件类型
			{
				case MOUSE_EVENT://鼠标事件
					mouse(i,leicnt,info);
					break;
				case MENU_EVENT:
				case FOCUS_EVENT:
					break;//两个内部事件
				case KEY_EVENT://按键事件
					key(i);
					break;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
//copyright stevendjr 版权所有
