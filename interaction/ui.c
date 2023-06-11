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
	MovePen(4, 8.75);
	DrawTextString(timeDisplay);
	sprintf(scoreDisplay, "SCORE: %lf", score);
	MovePen(7, 8.75);
	DrawTextString(scoreDisplay);
	//sprintf(cu_map, "map_number: %d", current_map);
	//MovePen(10, 8.75);
	//DrawTextString(cu_map);
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

	char* menuListFile[] = { "menu","Change Map","Solution","Exit | Ctrl-E" };
	int selection;
	selection = menuList(GenUIID(0), 0, 8.6, WindowWidth / 5, WindowWidth / 10, 0.4, menuListFile,
		sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 1) {
		current_map += 1;
		current_map %= MapNumber_MAX;
		display();
	}
	if (selection == 2) {}
	if (selection == 3) // choose to the menu of exit
		exit(-1); // act on the selection
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
	if (button(GenUIID(0), 6.3, 2.0, WindowWidth / 10, 0.4, "EXIT"))exit(-1);
	if (button(GenUIID(0), 6.3, 2.5, WindowWidth / 10, 0.4, "PLAY"))
		game_status = -1;
}
