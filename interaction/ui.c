/*****************************************************************//**
 * \file   ui.c
 * \brief  用于实现游戏界面的绘制，包括游戏的按钮、游戏信息的显示
 *			使用imgui.h库进行按钮的绘制
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "ui.h"


void InitButton(void) {
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	SetPenColor("Black");
	SetPenSize(1);
	MovePen(0, 9);
	DrawLine(WindowWidth, 0);
	MovePen(0, 8.55);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0);
	DrawLine(WindowWidth, 0);
	MovePen(0, 0.45);
	DrawLine(WindowWidth, 0);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor

}

void EchoInfo(void) {
	//实时显示游戏参数
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	SetPenColor("Black");
	char timeDisplay[100], scoreDisplay[100],cu_map[100];
	sprintf(timeDisplay, "Used Time: %-.4lf", current_time);
	MovePen(4, 8.70);
	DrawTextString(timeDisplay);
	sprintf(scoreDisplay, "current_map: %d", current_map+1);
	MovePen(7, 8.70);
	DrawTextString(scoreDisplay);

	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}

void background(void) {//界面背景
	InitButton();
	DisplayClear();
	int pensize = GetPenSize();
	string pencolor = GetPenColor();

	MovePen(0, 0);
	DefineColor("line", 1, 0.9, 0.6);
	SetPenColor("line");
	StartFilledRegion(1);
	DrawLine(14, 0);
	DrawLine(0, 9);
	DrawLine(-14, 0);
	DrawLine(0, -9);
	EndFilledRegion();
	
	SetPenSize(1);
	MovePen(0, 0);
	SetPointSize(100);
	SetPointSize(1);
	DefineColor("wood", 0.8, 0.6, 0);
	DefineColor("purple", 0.5, 0, 0.5);
	DefineColor("pink", 1, 0.5, 0.5);

	MovePen(6, -1);
	SetPenColor("wood");
	StartFilledRegion(1);
	DrawArc(5, 30, 120);
	EndFilledRegion();

	MovePen(9, -1);
	SetPenColor("wood");
	StartFilledRegion(1);
	DrawArc(5, 30, 120);
	EndFilledRegion();

	MovePen(12, -1);
	SetPenColor("wood");
	StartFilledRegion(1);
	DrawArc(5, 30, 120);
	EndFilledRegion();

	MovePen(14, -1);
	SetPenColor("wood");
	StartFilledRegion(1);
	DrawArc(5, 30, 120);
	EndFilledRegion();

	MovePen(16, -1);
	SetPenColor("wood");
	StartFilledRegion(1);
	DrawArc(5, 30, 120);
	EndFilledRegion();
	

	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}

void menu(void) {//显示菜单

	char* menuListFile[] = { "menu","Change Map","hint" };
	int selection;
	selection = menuList(GenUIID(0), 0, 8.6, WindowWidth / 5, WindowWidth / 10, 0.4, menuListFile,
		sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 1) {
		current_map += 1;
		current_map %= MapNumber_MAX;
		Is_Hint = 0;
		display();
	}
	if (selection == 2) {
		if (Is_Hint) {
			for (int i = 1; i <= 7; i++) {
				mapShape->graphics[i].isvisible = 0;
			}
			Is_Hint = 0;
		}
		else Is_Hint = 1;
	}

	if (button(GenUIID(0), WindowWidth / 10, 8.6, WindowWidth / 10, 0.4, "return")) {
		game_status = -1;
	}
}
void welcome(void){
/**
 * \brief 欢迎界面的生成
 */
	background();
	MovePen(6.0, 5.9);
	SetPenColor("red");
	StartFilledRegion(1);
	DrawLine(1, 0);
	DrawLine(-1, 1);
	DrawLine(0, -1);
	EndFilledRegion();
	MovePen(8.0, 5.9);
	SetPenColor("blue");
	StartFilledRegion(1);
	DrawLine(-0.5, 0.5);
	DrawLine(-1, 0);
	DrawLine(0.5, -0.5);
	EndFilledRegion();
	MovePen(6.0, 6.9);
	SetPenColor("purple");
	StartFilledRegion(1);
	DrawLine(0.5, -0.5);
	DrawLine(0.5, 0.5);
	DrawLine(-0.5, 0.5);
	DrawLine(-0.5, -0.5);
	EndFilledRegion();
	MovePen(6.0, 6.9);
	SetPenColor("green");
	StartFilledRegion(1);
	DrawLine(0.5, 0.5);
	DrawLine(-0.5, 0.5);
	DrawLine(0, -1);
	EndFilledRegion();
	MovePen(6.0, 7.9);
	SetPenColor("pink");
	StartFilledRegion(1);
	DrawLine(2, 0);
	DrawLine(-1, -1);
	DrawLine(-1, 1);
	EndFilledRegion();
	MovePen(8.0, 7.9);
	SetPenColor("orange");
	StartFilledRegion(1);
	DrawLine(0, -2);
	DrawLine(-1, 1);
	DrawLine(1, 1);
	EndFilledRegion();
	MovePen(6.5, 6.4);
	SetPenColor("yellow");
	StartFilledRegion(1);
	DrawLine(1, 0);
	DrawLine(-0.5, 0.5);
	DrawLine(-0.5, -0.5);
	EndFilledRegion();//绘制七巧板
	SetPointSize(100);
	SetPenColor("line");
	drawBox(6.5, 4.5, 1.0, 1.0, 0, "Tangram", "S", "blue");
	SetPointSize(1);
	drawBox(0, 0, 1.0, 1.0, 0, "制作组", "S", "blue");
	if (button(GenUIID(0), 6.3, 1.5, WindowWidth / 10, 0.4, "EXIT"))exit(-1);
	if (button(GenUIID(0), 6.3, 2.0, WindowWidth / 10, 0.4, "INTRODUCTION"))game_status=8;
	if (button(GenUIID(0), 6.3, 2.5, WindowWidth / 10, 0.4, "PLAY"))
		game_status = -1;
}

void echo_intro(void){
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	int size = GetPointSize();
	//1.移动图形：		鼠标左键拖拽
	//2.旋转图形：		右键单击
	//3.提示：			点击HINT按钮，再点击想要移动的七巧板，获取下一步的提示
	//4.重置游戏：		CTRL+R//todo: button
	//5.保存游戏状态：	CTRL+S
	//6.读取游戏状态：	CTRL+N 或者 界面选择CONTINUE选项
	//7.退出游戏：		ESC键 或者 点击退出

	GetStyle(2);
	MovePen(3, 7);
	DrawTextString("1.移动图形：		鼠标左键拖拽");
	MovePen(3, 6.5);
	DrawTextString("2.旋转图形：		右键单击");
	MovePen(3, 6);
	DrawTextString("3.提示：			点击HINT按钮，再点击想要移动的七巧板，获取下一步的提示");
	MovePen(3, 5.5);
	DrawTextString("4.重置游戏：		CTRL+R");
	MovePen(3, 5);
	DrawTextString("5.保存游戏状态：	CTRL+S");
	MovePen(3, 4.5);	
	DrawTextString("6.读取游戏状态：	CTRL+N 或者 界面选择CONTINUE选项");
	MovePen(3, 4);
	DrawTextString("7.退出游戏：		ESC键 或者 点击退出");
	if (button(GenUIID(0), 12.5, 0, WindowWidth / 10, 0.4, "return")) {
		game_status = 3;
	}

	SetPointSize(size);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
	GetStyle(0);
}
void _background(void) {//游戏界面背景
	int pensize = GetPenSize();
	string pencolor = GetPenColor();

	MovePen(0, 0);
	DefineColor("line", 1, 0.9, 0.6);
	SetPenColor("line");
	StartFilledRegion(1);
	DrawLine(14, 0);
	DrawLine(0, 9);
	DrawLine(-14, 0);
	DrawLine(0, -9);
	EndFilledRegion();

	MovePen(0, 0.45);
	DefineColor("deep blue", 0.1, 0.1, 0.4);
	SetPenColor("deep blue");
	StartFilledRegion(1);
	DrawLine(3.6, 0);
	DrawLine(0, 8.1);
	DrawLine(-3.6, 0);
	DrawLine(0, -8.1);
	EndFilledRegion();

	MovePen(10.5, 0.45);
	DefineColor("deep blue", 0.1, 0.1, 0.4);
	SetPenColor("deep blue");
	StartFilledRegion(1);
	DrawLine(3.6, 0);
	DrawLine(0, 8.1);
	DrawLine(-3.6, 0);
	DrawLine(0, -8.1);
	EndFilledRegion();
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}

void lose_page(void){
	//输出结束信息
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	int size = GetPointSize();
	DefineColor("deep blue", 0.1, 0.1, 0.41);
	SetPenColor("deep blue");
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
	SetPointSize(40);
	MovePen(6.4, 5);
	DrawTextString("You lost");
	


	SetPointSize(size);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}

void win_page(void) {
	int pensize = GetPenSize();
	string pencolor = GetPenColor();

	SetPenColor("Tan4");
	SetPenSize(1);

	MovePen(0, 0);
	StartFilledRegion(1);
	DrawLine(14, 0);
	DrawLine(0, 9);
	DrawLine(-14, 0);
	DrawLine(0, -9);
	EndFilledRegion();

	SetPenColor("Red");
	SetPenSize(1);
	SetPointSize(40);
	MovePen(6.4, 5);
	DrawTextString("You Win!!!");

	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}
