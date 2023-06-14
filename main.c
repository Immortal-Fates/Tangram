/*****************************************************************//**
 * \file   main.c
 * \brief  ����������ʵ���������ĳ�ʼ��
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/

#include "Header.h"

int game_status = 3;
int MapNumber_MAX;
int Is_Hint = 0;
double current_time = 0.0;
int page;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}
void main() {
	current_time = TIME_LEFT;//����60s����Ϸʱ��
	game_status = 3;
	MapNumber_MAX = 7;

	SetWindowTitle("Tangram");
	SetWindowSize(WindowWidth, WindowHeight);
	InitGraphics();
	InitColor(); //��ʼ����ɫ shape.c
	//timer -> timer.c
	registerTimerEvent(timer);
	startTimer(0, TIME_INTERVAL);

	//keyboard -> keyboardEvent.c
	registerKeyboardEvent(KeyboardEventProcess);
	
	//mouse	-> mouseEvent.c
	registerMouseEvent(MouseEventProcess);

	registerCharEvent(CharEventProcess);
	
	//��ʼ�����ɰ� shape.c
	Initshape();

	//��ʼ����ͼ map.c
	GenerateMap();
	InitMap();
	Generate_subMap();

	//��ʼ���û�
	user_init();
	display();
}
void display() {
	/**
	 * \brief ��ʾ��Ϸ���溯�������ڿ��Ʋ�ͬҳ�����ת��ͼ�λ���
	 * 
	 * \param game_status ��Ϸ״̬
	 *						-1 : �ڶ������� -2 : ��Ϸʤ������ -3 : ��Ϸʧ�ܽ���
	 *						0,1: ��Ϸ����	2 : ������Ϸ		 3 : ��ʼ����
	 *						4  : ���а�		5 : �Զ�������ɰ� 6 : �Զ������ɰ����
	 *						7  : ѡ���ͼ����8 : ��Ϣ��ʾ����
	 * \relates ��Ҫע����ǣ���Ϸ�������ʾ��ͨ�����ϵ�ˢ����ʵ�ֵģ������ÿ��ˢ��ʱ�������display����
	 *			��display�����У������game_status��ֵ���жϵ�ǰӦ����ʾ�ĸ�����
	 *			
	 *			�ڸ��Ļ��ʴ�ϸ��������ɫ�������ɫ�������С��ʱ����Ҫע����ǣ���Щ���Եĸı���ȫ�ֵģ�������Ҫ��ʱ��ԭ�����������
	 */
	DisplayClear();
	/*Part �������ֵ�����*/
	if (game_status != 0 && game_status != 1 && game_status != 6)
	{
		mciSendString("close bkmusic", NULL, 0, NULL);		//ֹͣ����BGM
		Is_Hint = 0;
	}
	if (game_status != -2)
	{
		mciSendString("close game_win", NULL, 0, NULL);
	}
	if (game_status != -3)
	{
		mciSendString("close game_lose", NULL, 0, NULL);
	}

	/*Part �����������*/
	switch (game_status)
	{
		case -1:		//page one
		{
			InitButton();
			background();
			SetPointSize(30);
			if (button(GenUIID(0), 4.6, 5, WindowWidth / 3, 1, "continue")) {
				current_time = TIME_LEFT;
				Read_File();
				game_status = 0;
			}
			if (button(GenUIID(0), 4.6, 4, WindowWidth / 3, 1, "new game")) {
				game_status = 7;
			}
			if (button(GenUIID(0), 4.6, 3, WindowWidth / 3, 1, "ranklist")) {
				game_status = 4;
			}
			if (button(GenUIID(0), 4.6, 2, WindowWidth / 3, 1, "return")) {
				game_status = 3;
			}
			break;
		}
		case -2:		//game win
		{
			InitButton();	//�����������	button.c
			EchoInfo();		//��ʾ������ʱ��	button.c
			win_page();		//��ʾ�ɹ�����	ui.c
			user_save();	//�����û���Ϣ	user.c
			SetPointSize(20);
			if (button(GenUIID(0), 5.9, 3, WindowWidth / 5, 0.5, "new game")) {
				game_status = 7;
			}
			SetPointSize(1);
			break;
		}
		case -3:		//game lose
		{
			InitButton();	//����������� button.c
			EchoInfo();		//��ʾ������ʱ��	button.c
			lose_page();	//��ʾʧ�ܽ���	ui.c
			SetPointSize(20);
			if (button(GenUIID(0), 5.9, 3, WindowWidth / 5, 0.5, "new game")) {
				game_status = 7;
			}
			SetPointSize(1);
			break;
		}
		case -4:		//user register
		{

			background();
			user_login_button();
			break;
		}
		case 0: case 1: //running //pause
		{	
			_background();	//��������ͼ��	ui.c
			InitButton();	//�����������	button.c
			EchoInfo();		//��ʾ������ʱ��	button.c
			menu();			//��ʾ�˵���	ui.c
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //ѭ����������
			/*Part ��״�͵�ͼ�Ļ���*/
			Shape* temp = head;
			while (temp) {
				DrawShape(temp);
				temp = temp->next;
			}
			DrawMap(current_map);
			DrawSubmap(current_map);
			break; 
		}//end of case 1
		case 2:			//restart ������Ϸ���������ɵ�ͼ����״�����¿�ʼ��ʱ
		{
			current_time = TIME_LEFT;
			delete_shape();
			Initshape();
			DrawMap(current_map);
			game_status = 0;
			break;
		}
		case 3:			//page zero
		{
			DisplayClear();
			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			welcome();				//��ʾ��ӭ����	ui.c
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
			break; 
		}
		case 4:			//ranklist
		{
			background();				//��������ͼ��	ui.c
			echo_ranklist(current_map);	//��ʾ���а�		ranklist.c
			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			char scoreDisplay[100];
			SetPenColor("#001e1d");
			sprintf(scoreDisplay, "current_map: %d", current_map + 1);
			MovePen(7, 8.70);
			DrawTextString(scoreDisplay);
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
			if (button(GenUIID(1), 12.5, 5, WindowWidth / 10, 0.4, "page")) {
				current_map += 1;
				current_map %= MapNumber_MAX;
				display();
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}
			break; 
		}
		case 5:			//solve
		{
			background();	//��������ͼ��	ui.c
			//solve();		//�Զ����		solve.c
			break;
		}
		case 6:			//createMap
		{
			background();
			InitButton();
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //ѭ����������
			SetPointSize(80);
			drawBox(7.0, 8, 0, 0, 0, "Create The Map", "0", "blue");
			SetPointSize(30);
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = 7;
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "save")) {
				//DIY_map();
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = 7;
			}
			break;
		}
		case 7:			//new game
		{
			background();
			InitButton();
			SetPointSize(80);
			drawBox(7.0, 8, 0, 0, 0, "Select The Map", "0", "blue");
			SetPointSize(30);
			char button_num[20];
			double px[5] = { 2.1,5.1,8.1,11.1 };
			double py[3] = { 5,2 };
			for (int i = page*8; i < min(page*8+8,MapNumber_MAX); i++) {
				sprintf(button_num, "%d", i+1);
				if (button(GenUIID(i), px[i%4], py[i%8/4], WindowWidth / 10, 0.4, button_num)) {
					game_status = 2;
					current_map = i;
				}
			}
			if (button(GenUIID(0), 7.3, 1, WindowWidth / 10, 0.4, "next")) {
				page++;
				page = min(page, (MapNumber_MAX - 1) / 8);
			}
			if (button(GenUIID(1), 5.9, 1, WindowWidth / 10, 0.4, "before")) {
				page--;
				page = max(page, 0);
			}
			if (button(GenUIID(2), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}
			if (button(GenUIID(3), 12, 8, WindowWidth / 10, 0.4, "createMap"))
				game_status = 6;
			break;
		}
		case 8:			//game intro ��Ϣ��ʾ����
		{
			InitButton();	//������ť	  ui.c
			background();	//��������ͼ�� ui.c
			echo_intro();	//��ʾ��Ϣ��ʾ ui.c
		}
		default:
			break;
	}
}


