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
int colorindex = 0; //��˸ʱ��ɫ�±�


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
	Read_color();
	InitColor(); //��ʼ����ɫ shape.c
	//timer -> timer.c
	registerTimerEvent(timer);
	startTimer(0, TIME_INTERVAL);
	startTimer(1, 500);

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
			InitButton();		//��ʼ�����button ui.c
			background();		//��������ҳ�� ui.c
			button_page_one();	//button	ui.c
			break;
		}
		case -2:		//game win
		{
			InitButton();	//�����������	ui.c
			EchoInfo();		//��ʾ������ʱ��	ui.c
			win_page();		//��ʾ�ɹ�����	ui.c
			user_save();	//�����û���Ϣ	user.c
			break;
		}
		case -3:		//game lose
		{
			InitButton();	//�����������	ui.c
			EchoInfo();		//��ʾ������ʱ��	ui.c
			lose_page();	//��ʾʧ�ܽ���	ui.c
			break;
		}
		case -4:		//user register
		{

			background();	//���� ui.c
			user_login_button();	//button ui.c
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
			welcome();				//��ʾ��ӭ����	ui.c
			break; 
		}
		case 4:			//ranklist
		{
			background();				//��������ͼ��	ui.c
			ranklist_ui();				//��ʾ���а��ͼ�� ui.c
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
			_background();	//��������ͼ��	ui.c
			InitButton();	//�����������	button.c
			EchoInfo();		//��ʾ������ʱ��	button.c
			create_map_page();
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //ѭ����������
			/*Part ��״�͵�ͼ�Ļ���*/
			Shape* temp = head;
			while (temp) {
				DrawShape(temp);
				temp = temp->next;
			}

				
			break;
		}
		case 7:			//new game
		{
			background();		//����			ui.c
			InitButton();		//����button		ui.c
			select_game_page();
			break;
		}
		case 8:			//game intro ��Ϣ��ʾ����
		{
			InitButton();	//������ť	  ui.c
			background();	//��������ͼ�� ui.c
			echo_intro();	//��ʾ��Ϣ��ʾ ui.c
			break;
		}
		default:
			break;
	}
	//if(current_time == 1)
	//{
	//	linkedlistADT temp_adt = submap_line_link_head->next;
	//	while (temp_adt)
	//	{

	//		SetPenSize(3);
	//		MovePen(((line*)(temp_adt->dataptr))->start.x, ((line*)(temp_adt->dataptr))->start.y);
	//		DrawLine(((line*)(temp_adt->dataptr))->end.x - ((line*)(temp_adt->dataptr))->start.x , ((line*)(temp_adt->dataptr))->end.y - ((line*)(temp_adt->dataptr))->start.y);
	//		/*fprintf(fp, "sx = %lf sy =%lf ", ((line*)(temp_adt->dataptr))->start.x, ((line*)(temp_adt->dataptr))->start.y);

	//		fprintf(fp, "ex = %lf ey =%lf\n", ((line*)(temp_adt->dataptr))->end.x, ((line*)(temp_adt->dataptr))->end.y);*/

	//		temp_adt = temp_adt->next;
	//	}
	//}
}


