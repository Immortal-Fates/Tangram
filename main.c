/*****************************************************************//**
 * \file   main.c
 * \brief  主函数程序，实现整体界面的初始化
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/

#include "Header.h"

int game_status = 3;
double score;
double current_time = 0.0;
double WindowWidth = 14;
double window_height = 9;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);


void Main() {
	//message box 函数
	//MessageBox("Hello, world!");
	current_time = TIME_LEFT;//给定60s的游戏时间
	game_status = 0;
	SetWindowTitle("Tangram");
	SetWindowSize(WindowWidth, window_height);
	InitGraphics();

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
	InitMap(6);

	//初始化用户
	user_init();

	display();
}

void display() {
	//game_status: 0->running 1->pause 2->exit 3->info/help 4->ranklist 5->solve 6->createMap
	DisplayClear();

	switch (game_status)
	{
		case -1: //change
		{
			InitButton();
			SetPointSize(30);
			if (button(GenUIID(0), 4.6, 5, WindowWidth / 3, 1, "continue")) {
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
		case 0: case 1: //running //pause
		{	
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			Shape* temp = head;
			while (temp) {
				DrawShape(temp);
				temp = temp->next;
			}
			DrawMap(current_map);
			if (button(GenUIID(0), 14, 2, WindowWidth / 10, 0.4, "返回")) {
				game_status = 3;
			}
			if (button(GenUIID(0), 6.3, 1, WindowWidth / 10, 0.4, "change map")) {
				current_map += 1;
				current_map %= MapNumber_MAX;
				display();
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = 7;
			}
			break; 
		}//end of case 1
		case 2: //restart
			current_time = TIME_LEFT;
			score = 0;
			delete_shape();
			Initshape();
			DrawMap(current_map);
			game_status = 0;
			break;
		case 3: //welcome
			DisplayClear();
			MovePen(0, 0);
			SetPenColor("white");
			StartFilledRegion(1);
			DrawLine(14, 0);
			DrawLine(0, 9);
			DrawLine(-14, 0);
			DrawLine(0, -9);
			EndFilledRegion();
			SetPenSize(1);
			MovePen(0, 0);
			SetPointSize(100);
			drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "blue");
			/*icurrent_time = ((int)current_time) % 5;

			switch (icurrent_time) {
			case 0: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "blue"); break;
			case 1: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "yellow"); break;
			case 2: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "green"); break;
			case 3: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "black"); break;
			case 4: drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "read"); break;
			}*/
			SetPointSize(1);
			drawBox(0, 0, 1.0, 1.0, 0, "制作组", "S", "blue");

			if (button(GenUIID(0), 6.3, 3.0, WindowWidth / 10, 0.4, "EXIT"))exit(-1);
			if (button(GenUIID(0), 6.3, 3.5, WindowWidth / 10, 0.4, "PLAY"))
				game_status = -1;
			break;
		case 4: //ranklist
			echo_ranklist();
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}
			break;
		case 5: //solve

			break;
		case 6: //createMap

			break;
		case 7: //new game
			InitButton();
			SetPointSize(80);
			drawBox(7.0, 8, 0, 0, 0, "Select The Map", "0", "blue");
			SetPointSize(30);
			if (button(GenUIID(0), 2.1, 5, WindowWidth / 10, 0.4, "1")) {
				game_status = 2;
				current_map = 0;
			}
				
			if (button(GenUIID(0), 5.1, 5, WindowWidth / 10, 0.4, "2")) {
				game_status = 2;
				current_map = 1;
			}
			if (button(GenUIID(0), 8.1, 5, WindowWidth / 10, 0.4, "3")) {
				game_status = 2;
				current_map = 2;
			}
			if (button(GenUIID(0), 11.1, 5, WindowWidth / 10, 0.4, "4")) {
				game_status = 2;
				current_map = 3;
			}
			if (button(GenUIID(0), 2.1, 2, WindowWidth / 10, 0.4, "5")) {
				game_status = 2;
				current_map = 4;
			}
			if (button(GenUIID(0), 5.1, 2, WindowWidth / 10, 0.4, "6")) {
				game_status = 2;
				current_map = 5;
			}
			if (button(GenUIID(0), 8.1, 2, WindowWidth / 10, 0.4, "7")) {
				game_status = 2;
				current_map = 0;
			}
			if (button(GenUIID(0), 11.1, 2, WindowWidth / 10, 0.4, "8")) {
				game_status = 2;
				current_map = 0;
			}
			if (button(GenUIID(0), 0, 0, WindowWidth / 10, 0.4, "next")) {
				game_status = 16;
			}
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}

			break;
		case 16://next page
			InitButton();
			SetPointSize(80);
			drawBox(7.0, 8, 0, 0, 0, "Create The Map", "0", "blue");
			SetPointSize(30);
			if (button(GenUIID(0), 2.1, 5, WindowWidth / 10, 0.4, "createMap"))
				game_status = 6;
			if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = 7;
			}
		default:
			break;
	}
}
