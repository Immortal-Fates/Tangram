/*****************************************************************//**
 * \file   main.c
 * \brief  主函数程序，实现整体界面的初始化
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/

#include "Header.h"

int game_status = 3;
int MapNumber_MAX;
int Is_Hint = 0;
double current_time = 0.0;
double WindowWidth = 14;
double window_height = 9;
int page;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);


void Main() {

	current_time = TIME_LEFT;//给定60s的游戏时间
	game_status = 3;
	MapNumber_MAX = 7;
	SetWindowTitle("Tangram");
	SetWindowSize(WindowWidth, window_height);
	InitGraphics();
	InitColor();
	//timer -> timer.c
	registerTimerEvent(timer);
	startTimer(0, 100);

	//keyboard -> keyboardEvent.c
	registerKeyboardEvent(KeyboardEventProcess);
	
	//mouse	-> mouseEvent.c
	registerMouseEvent(MouseEventProcess);
	
	//初始化七巧板 shape.c
	Initshape();

	//初始化地图 map.c
	GenerateMap();
	InitMap();
	
	Generate_subMap();

	//初始化用户
	user_init();
	display();
}
void display() {
	//game_status: 0->running 1->pause 2->exit 3->info/help 4->ranklist 5->solve 6->createMap
	DisplayClear();
	if (game_status != 0 && game_status != 1 && game_status != 6)
	{
		mciSendString("close bkmusic", NULL, 0, NULL);		//停止播放BGM
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
	switch (game_status)
	{
		case -1: //page one
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
		case -2: //game win
		{
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			//输出结束信息
			win_page();
			SetPointSize(20);
			if (button(GenUIID(0), 5.9, 3, WindowWidth / 5, 0.5, "new game")) {
				game_status = 7;
			}
			SetPointSize(1);
			break;
		}
		case -3: //game lose
		{
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			lose_page();
			SetPointSize(20);
			if (button(GenUIID(0), 5.9, 3, WindowWidth / 5, 0.5, "new game")) {
				game_status = 7;
			}
			SetPointSize(1);
			break;
		}
		case 0: case 1: //running //pause
		{	
			_background();
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //循环播放音乐
			menu();
			Shape* temp = head;
			while (temp) {
				DrawShape(temp);
				temp = temp->next;
			}
			DrawMap(current_map);
			//todo:hint 的bug
			/*if (button(GenUIID(0), 10, 0, WindowWidth / 10, 0.4, "hint")) {
				if (Is_Hint) {
					for (int i = 1; i <= 7; i++) {
						mapShape->graphics[i].isvisible = 0;
					}
					Is_Hint = 0;
				}
				else Is_Hint = 1;
				score = Is_Hint;
			}*/
			DrawSubmap(current_map);
			/*if (button(GenUIID(0), 14, 0, WindowWidth / 10, 0.4, "返回")) {
				game_status = 3;
			}
			if (button(GenUIID(0), 6.3, 0, WindowWidth / 10, 0.4, "change map")) {
				current_map += 1;
				current_map %= MapNumber_MAX;
				display();
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = 7;
			}*/
			break; 
		}//end of case 1
		case 2: //restart
		{
			current_time = TIME_LEFT;
			delete_shape();
			Initshape();
			DrawMap(current_map);
			game_status = 0;
			break;
		}
		case 3: //page zero
		{
			DisplayClear();

			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			welcome();
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
			break; 
		}
		case 4: //ranklist
		{
			background();
			echo_ranklist();
			
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}
			break; 
		}
		case 5: //solve
		{
			background();
			break;
		}
		case 6: //createMap
		{
			background();
			InitButton();
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //循环播放音乐
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
		case 7: //new game
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
		case 8:	//game introduction
		{
			InitButton();	//画出整体界面 button.c
			background();
			echo_intro();
		}
		default:
			break;
	}
}


