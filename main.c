/*****************************************************************//**
 * \file   main.c
 * \brief  主函数程序，实现整体界面的初始化
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/

#include "Header.h"

int game_status = 3;
double score = 0;
double current_time = 0.0;
double WindowWidth = 14;
double window_height = 9;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);


void Main() {
	//message box 函数
	//MessageBox("Hello, world!");

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

	display();
}

void display() {
	//game_status: 0->running 1->pause 2->exit 3->info/help 4->ranklist 5->solve 6->createMap
	DisplayClear();

	switch (game_status)
	{
		case 0: case 1:	//running //pause
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
			if (button(GenUIID(0), 6.3, 1, WindowWidth / 10, 0.4, "tuck")){
				current_map += 1;
				current_map %= MapNumber_MAX;
				display();
			}
				
			break;
		case 2: //restart
			current_time = 0;
			score = 0;
			delete_shape();
			Initshape();
			DrawMap(current_map);
			game_status = 0;
			break;
		case 3: //info/help
            DisplayClear();
            MovePen(0, 0);
            SetPenColor("black");
            StartFilledRegion(1);
            DrawLine(14, 0);
            DrawLine(0, 9);
            DrawLine(-14, 0);
            DrawLine(0, -9);
            EndFilledRegion();

            SetPenSize(1);
            MovePen(0, 0);
            drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "blue");
            drawBox(0, 0, 1.0, 1.0, 0, "制作组", "S", "blue");
            if (button(GenUIID(0), 6.3, 3.0, WindowWidth / 10, 0.4, "退出"))exit(-1);
            if (button(GenUIID(0), 6.3, 3.5, WindowWidth / 10, 0.4, "PLAY"))
                game_status = 0;
			break;
		case 4: //ranklist

			break;
		case 5: //solve

			break;
		case 6: //createMap

			break;
		default:
			break;
	}
}

