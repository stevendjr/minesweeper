//ɨ����Ϸ2.0.1
//ע���˰汾�����scoreboard����ʹ��
////////////////////////////////////////////////////////////////////////////////
#include "main.h"
using namespace my_using;

int mines[height][length];//�����ʾ��ͼ�Ķ�ά����
bool ispr[height][length];//�ǲ����Ѿ���ӡ��
bool isfl[height][length];//�ǲ����Ѿ���������
HANDLE window;//���ھ��
INPUT_RECORD input[128];//�����¼���
DWORD input_num;//�����¼�����
bool isrun;//������Ϸ����
clock_t start;//һ����Ϸ��ʼʱ�ļ�ʱ

void out_gezi()//�����Ϸ����
{
	gotoxy(0, 3);//�����ʼλ��
	color(back_white);//���ð�ɫ����ɫ
	_tout << "��";//������Ͻ�
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "������";
	}
	_tout << "������" ;
	for (int i = 0; i < height - 1; i++)
	{
		_tout << " " << endl << "��";
		for (int j = 0; j < length - 1; j++)
		{
			_tout << "  ��";
		}
		_tout << "  �� ";
		_tout << endl << "��";
		for (int j = 0; j < length - 1; j++)
		{
			_tout << "������";
		}
		_tout << "������";
	}
	_tout << " " << endl << "��";
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "  ��";
	}
	_tout << "  �� ";
	_tout << endl << "��";
	for (int j = 0; j < length - 1; j++)
	{
		_tout << "������";
	}
	_tout << "������ ";
}

void print(int i, int j) //��������������
{
	int col = back_white;//���ñ���ɫ
	switch (mines[i][j])//���ݸ�������ѡ����ɫ
	{
		case -1://����������
			col |= FOREGROUND_INTENSITY | FOREGROUND_RED;//����ɫ
			break;
		case 0:
			col |= FOREGROUND_BLUE;//��ɫ
			break;
		case 1:
			col |= FOREGROUND_INTENSITY | FOREGROUND_GREEN;//����ɫ
			break;
		case 2:
			col |= FOREGROUND_RED | FOREGROUND_GREEN;//��ɫ
			break;
		case 3:
			col |= FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;//����ɫ
			break;
		case 4:
			col |= FOREGROUND_BLUE | FOREGROUND_GREEN;//����ɫ
			break;
		default:
			col |= FOREGROUND_RED;//��ɫ
			break;
	}
	gotoxy((i + 1) * 3 - 1, j * 2 + 4);//���㲢����ָ��λ��
	color(col);//������ɫ
	if (mines[i][j] == -1)//�������
		_tout << "X";
	else//����
		_tout << mines[i][j];//ԭ�����
}

void spawn(int o, int p) //����ɨ�׵�ͼ
{
	srand((unsigned)time(0));//�����������
	int x, y,lei;
	int i, j, k, l; //ѭ������
	i=0;
	while(i<num)//�������������
	{
		x=rand()%height;//���������
		y=rand()%length;//���������
		if(mines[x][y]==-1//����������Ѿ�����
				or (x>=o-1 and x<=o+1 and y>=p-1 and y<=p+1)//�����ڵ��λ�ø���
				)
			continue;//������λ��
		mines[x][y]=-1;//���򣬽��ø�����Ϊ��
		i++;//������������
	}
	for (i = 0; i < height; i++)
		for (j = 0; j < length; j++)
		{
			if (mines[i][j] != -1) //����ø����ף����ж�����
			{
				lei = 0;//����Ϊ0
				for (k = i - (i != 0); k <= i + (i != height - 1); k++)
					for (l = j - (j != 0); l <= j + (j != length - 1); l++)
						if (mines[k][l] == -1)//����
							lei++;//������1
				mines[i][j] = lei; //���븽������
			}
		}//�Ը��Ӹ����׵ļ���
}

int menu(int i) //����˵�ʱ�Ĳ���
{
	if (mouse_click(input,new_game.a, new_game.b, i, MK_LEFT))//�����new_game��ť
	{
		unbtnshow(new_game.a, new_game.b);
		unbtnshow(restart.a,restart.b);
		unbtnshow(m_exit.a, m_exit.b);//����������ť
		return NEW_GAME;
	}
	else if(mouse_click(input,restart.a, restart.b, i, MK_LEFT))
	{
		unbtnshow(new_game.a, new_game.b);
		unbtnshow(restart.a,restart.b);
		unbtnshow(m_exit.a, m_exit.b);//����������ť
		return RESTART;
	}
	else if (mouse_click(input,m_exit.a, m_exit.b, i, MK_LEFT))//�����exit��ť
	{
		system("cls");//����
		exit(0);//�˳���Ϸ
	}
	return NONE;//û�е��
}

bool fan(int x, int y) //����һ������
{
	if (ispr[y][x])//�Ѿ�������
		return false;//û�б�ը
	print(x, y);//��ʾ����
	switch (mines[x][y])
	{
		case -1://����������
			return true;//��ը��
		case 0://�����հ���
			for (int l = x - (x != 0); l <= x + (x != height - 1); l++)
				for (int k = y - (y != 0); k <= y + (y != length - 1); k++)
				{
					if (mines[l][k] != -1 //������
							and !ispr[k][l]//û����ʾ
							)
					{
						ispr[y][x] = true;//��ӡ��
						fan(l, k);//�ݹ鷭����һ��
					}
				}
			break;
		default:
			ispr[y][x] = true;//����
			break;
	}
	return false;//û�б�ը
	//ע��ע�������������ʱ�Ĳ���˳��Ӧ���������ڵڶ����������������ڵ�һ������
}

/*void pr_ispr()//���Ժ����������
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
void flag(int y, int x, int &leicnt) //�����ӻ�γ�����
{
	if (!ispr[y][x])//û����ʾ
	{
		gotoxy((x + 1) * 3 - 1, y * 2 + 4);//����ָ��λ��
		color(FOREGROUND_RED | FOREGROUND_INTENSITY | back_white);//������ɫ
		if (!isfl[y][x])//û�в�����
		{
			_tout << TEXT("F");
			isfl[y][x] = true;//�Ѿ�����
			--leicnt;//������1
		}
		else//�Ѿ�����
		{
			_tout << " ";
			isfl[y][x] = false;//�γ�����
			++leicnt;//������1
		}
	}
}

void initialize()//��ʼ�µ�һ����Ϸʱ�ĳ�ʼ��
{
	memset(ispr, false, sizeof(ispr));//��մ�ӡ����
	memset(isfl, false, sizeof(isfl));//������ӵ�ͼ
	system("cls");//����
	system("color F0");//���ñ���
	char st[80];//׼�����õ��ַ���
	sprintf_s(st, (size_t)_countof(st), "mode con cols=%d lines=%d", length * 7, height * 2 + 6);//���ַ�������ı�
	system(st);//���ÿ���̨�ĳ��Ϳ�
	SetConsoleMode(window, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
	               ENABLE_MOUSE_INPUT);
	button_show(times.a, times.b, " ");//���ʱ���
	button_show(minecnt.a, minecnt.b, " ");//���������
	button_show(score.a,score.b,"scoreboard");
	button_show(reset_score.a,reset_score.b,"reset score ");
	gotoxy(2, 1);
	_tout << TEXT("time:");
	gotoxy(length + 2, 1);
	_tout << TEXT(":");
	gotoxy(length + 7, 1);
	_tout << TEXT("X:");
	start = clock();//�õ���ʼʱ��
	out_gezi();//�������
}

void out_time()//�����ʱ��Ϣ
{
	color(back_white);
	gotoxy(length, 1);
	clock_t rtnow = (clock() - start) / CLOCKS_PER_SEC;//������ʱ��������ʱ��-��ʼʱ�䣩/ʱ�䵥λ
	if (rtnow / 600 == 0)//�������10����
		_tout << 0;//��0
	_tout << rtnow / 60;//�������
	gotoxy(length + 3, 1);
	if (rtnow % 60 / 10 == 0)//�����������10��
		_tout << 0;//��0
	_tout << rtnow % 60;//�����
}

void out_leicnt(int leicnt)//���ʣ������
{
	gotoxy(length * 3 - 1, 1);
	if (leicnt >= 0 and leicnt < 10)//������0~9֮��
		_tout << TEXT(" ");//���ո�
	_tout << leicnt;//�������
	//ע����δ����޷���ȷ����leicnt<=-10 or leicnt>=100ʱ�����
}

bool win()//�ǲ����Ѿ�Ӯ��
{
	bool flag = true;//��־����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (mines[i][j] != -1 and not ispr[j][i])//�����ﲻ���ײ���û�з���
			{
				flag = false;//û��Ӯ
			}
		}
	}
	return flag;
}

void gameover(scoreboard_info & info,bool & iswin)
{
	isrun=false;
	change_write_info(info,iswin);
	color(back_white);//���ñ���
	gotoxy(length * 3 + 4, 1);//����ָ��λ��
	_tout<<"                                ";
	gotoxy(length * 3 + 4, 2);//����ָ��λ��
	_tout<<"                        ";
	gotoxy(length * 3 + 4, 1);//����ָ��λ��
	if (iswin)//��Ӯ��
		_tout << TEXT("��Ӯ�ˡ�ף������");
	else//������
		_tout << TEXT("������˼�������ˡ�����һ�Σ�");
	button_show(new_game.a, new_game.b, "new_game");//���new_game��ť
	button_show(restart.a,restart.b,"restart ");//���restart��ť
	button_show(m_exit.a, m_exit.b, "exit");//���exit��ť
}

void doublekey(console_pos get,bool & iswin,scoreboard_info & info)//˫�����
{
	int cnt = 0;
	for (int k = get.X - (get.X != 0); k <= get.X + (get.X != height - 1); k++)
		for (int l = get.Y - (get.Y != 0); l <= get.Y + (get.Y != length - 1); l++)
			if (isfl[k][l])//��������
				cnt++;
	//�鿴���������Ӹ���
	if (cnt == mines[get.Y][get.X])//�����к͸�����������ͬ����������
	{
		for (int k = get.X - (get.X != 0); k <= get.X + (get.X != height - 1); k++)
			for (int l = get.Y - (get.Y != 0); l <= get.Y + (get.Y != length - 1); l++)
				if (!ispr[k][l] and !isfl[k][l])//û�д�ӡ��Ҳû������
					if (fan(l, k))//�������ף�����
					{
						iswin = false;
						gameover(info,iswin);
						return;
					}
	}
	//ע�����������˫���Զ��������������һ�񸽽�����Ѿ�����˸������������ӣ���˫������
	//�����������ӣ���ʹ��ұ��������
}

void mouse(int a,int & leicnt,scoreboard_info & info)//�й����Ĳ���
{
	static bool iswin,//Ӯ��
		isfirst = true,isrestart=false;//�ǵ�һ�ε��
	//pr_ispr();
	console_pos get;//�õ���λ��
	if (isrun)//������Ϸ
	{
		if (win())//Ӯ��
		{
			iswin = true;//��Ӯ��Ϊ��
			gameover(info,iswin);
			return;
		}
		get = click_gezi(input,a, MK_LEFT);//����ĸ���
		if (get.X != -1//�㵽������
				and !input[a].Event.MouseEvent.dwEventFlags//�ǰ��°�ť
				)
		{
			switch (input[a].Event.MouseEvent.dwButtonState)//���µ����ĸ���ť
			{
				case MK_LEFT://���
					if (isfirst and not isrestart)//�ǵ�һ�ε��
					{
						memset(mines, false, sizeof(mines));//��յ�ͼ
						spawn(get.X, get.Y);//���ɵ�ͼ
						isfirst = false;//���ڲ��ǵ�һ�ε��
					}
					if (!isfl[get.X][get.Y])//���������û������
					{
						if (fan(get.Y, get.X))//�����������
						{
							iswin = false;//����Ӯ��
							gameover(info,iswin);
							return;
						}
					}
					break;
				case MK_RIGHT://�Ҽ�
					flag(get.X, get.Y, leicnt);//�����ӻ�γ�����
					break;
				case MK_LEFT | MK_RIGHT://����˫��
					doublekey(get,iswin,info);
			}
		}
		else if(mouse_click(input,score.a,score.b,a,MK_LEFT))//�����scoreboard��ť
		{
			TCHAR szpath[30]=TEXT("scoreboard.exe");
			STARTUPINFO startinfo={sizeof(STARTUPINFO),NULL,NULL};
			PROCESS_INFORMATION ppi={0};
			if(not CreateProcess(NULL,
					szpath,//������
					NULL,NULL,false,//Ĭ�ϰ�ȫ�Ͳ��̳�
					CREATE_NEW_CONSOLE,//ʹ���¿���̨
					NULL,NULL,//�޻������Ĭ��Ŀ¼
					&startinfo,//������Ϣ
					&ppi)//���̾��
					)
			{
				error(CANNOT_START_SCOREBOARD);//�޷���scoreboard����
			}
		}
		else if(mouse_click(input,reset_score.a,reset_score.b,a,MK_LEFT))//�����reset score��ť
		{
			remove("gameinfo.json");//ɾ���ļ�
		}
	}
	else
	{
		switch(menu(a))
		{
			case NEW_GAME:
				initialize();//��ʼ��
				isrun = true;//����Ϸ����
				isfirst = true;//�ȴ���һ�ε��
				leicnt=num;//��ʼ���׼���
				isrestart=false;//�����µ�ͼ
				break;
			case RESTART:
				initialize();//��ʼ��
				isrun = true;//����Ϸ����
				isfirst = true;//�ȴ���һ�ε��
				leicnt=num;//��ʼ���׼���
				isrestart=true;//���µ�ͼ
				gotoxy(length * 3 + 4, 1);//����ָ��λ��
				_tout<<TEXT("��һ�ֵ���Ϸ����һ����ͬ��С�ģ�");
				gotoxy(length * 3 + 4, 2);//����ָ��λ��
				_tout<<TEXT("����һ�ε����Ϳ��ܻ��䡣");
		}
	}
}

void key(int i)//�йؼ��̰����Ĳ�����������������ʹ��
{
	//ע����������Ҫʵ�ֵĹ��ܣ�
	//   1.ͨ���������ٿ���Ϸ
	//   2.ͨ����ͷ���ƶ���ͨ���س���������ͨ���ո�����/������
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
	{//����Ҫ��
		return;
	}
	else
	{//������Ҫ��
		_tout<<TEXT("��ϵͳ����Windows 10�������Ϸֻ����Windows 10�����С�");
		Sleep(2000);
		exit(0);
	}
}

int _tmain()//������
{
	compare_version();//�Ƚ�ϵͳ�汾
	window = GetStdHandle(STD_INPUT_HANDLE);//��ȡ���ھ��
	SetConsoleTitle(TEXT("ɨ��"));//���ô��ڱ���
	initialize();//��ʼ��
	isrun = true;//����Ϸ����
	int leicnt = num;//��ʼ���׼���
	ifstream fin("gameinfo.json");//�򿪶����ļ�
	scoreboard_info info;//��Ϣ
	if(fin.is_open())//����
	{
		get_info(fin,info);//����Ϣ
	}
	else
	{
		memset(&info,0,sizeof(info));//�����Ϣ�ṹ
	}
	fin.close();//�ر��ļ�
	while (true)
	{
		ReadConsoleInput(window, input, 128, &input_num);//��ȡ���뻺�����¼�
		if (isrun)//������
		{
			out_time();//���ʱ��
			out_leicnt(leicnt);//�������
		}
		for (int i = 0; i < int(input_num); i++)//�������ʱ��
		{
			switch (input[i].EventType)//�¼�����
			{
				case MOUSE_EVENT://����¼�
					mouse(i,leicnt,info);
					break;
				case MENU_EVENT:
				case FOCUS_EVENT:
					break;//�����ڲ��¼�
				case KEY_EVENT://�����¼�
					key(i);
					break;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
//copyright stevendjr ��Ȩ����
