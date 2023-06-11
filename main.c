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
double score;
double current_time = 0.0;
double WindowWidth = 14;
double window_height = 9;
int page;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);


void Main() {

	current_time = TIME_LEFT;//给定60s的游戏时间
	game_status = 0;
	MapNumber_MAX = 6;
	
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
	InitMap();
	
	//Generate_subMap();

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
		case -2: {
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			//输出结束信息
			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			SetPenColor("black");
			SetPenSize(1);
			MovePen(0, 0);
			StartFilledRegion(1);
			DrawLine(14, 0);
			DrawLine(0, 9);
			DrawLine(-14, 0);
			DrawLine(0, -9);
			EndFilledRegion();

			SetPenColor("RED");
			SetPenSize(1);
			SetPointSize(30);
			MovePen(4.6, 5);
			DrawTextString("Game Over");
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor


			if (button(GenUIID(0), 4.6, 4, WindowWidth / 3, 1, "new game")) {
				game_status = 7;
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
			
			if (button(GenUIID(0), 10, 2, WindowWidth / 10, 0.4, "hint")) {
				if (Is_Hint) {
					for (int i = 1; i <= 7; i++) {
						mapShape->graphics[i].isvisible = 0;
					}
					Is_Hint = 0;
				}
				else Is_Hint = 1;
				score = Is_Hint;
			}
			DrawSubmap(current_map);
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

			int pensize = GetPenSize();
			string pencolor = GetPenColor();
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
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
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
			InitButton();
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
		case 7: //new game
			InitButton();
			SetPointSize(80);
			drawBox(7.0, 8, 0, 0, 0, "Select The Map", "0", "blue");
			SetPointSize(30);
			char button_num[20];
			double px[5] = { 2.1,5.1,8.1,11.1 };
			double py[3] = { 5,2 };
			for (int i = page*8; i < page*8+8; i++) {
				sprintf(button_num, "%d", i+1);
				if (button(GenUIID(i), px[i%4], py[i%8/4], WindowWidth / 10, 0.4, button_num)) {
					game_status = 2;
					current_map = i;
				}
			}
			if (button(GenUIID(0), 0, 0, WindowWidth / 10, 0.4, "next")) {
				page++;
				page = min(page,(MapNumber_MAX-1)/8);
			}
			if (button(GenUIID(1), 3, 0, WindowWidth / 10, 0.4, "before")) {
				page--;
				page = max(page, 0);
			}
			if (button(GenUIID(2), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
				game_status = -1;
			}
			if (button(GenUIID(3), 6, 0, WindowWidth / 10, 0.4, "createMap"))
				game_status = 6;
			break;
			
		default:
			break;
	}
}


