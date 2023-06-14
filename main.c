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
int page;

void timer(int timerID);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}
void main() {
	current_time = TIME_LEFT;//给定60s的游戏时间
	game_status = 3;
	MapNumber_MAX = 7;

	SetWindowTitle("Tangram");
	SetWindowSize(WindowWidth, WindowHeight);
	InitGraphics();
	InitColor(); //初始化颜色 shape.c
	//timer -> timer.c
	registerTimerEvent(timer);
	startTimer(0, TIME_INTERVAL);

	//keyboard -> keyboardEvent.c
	registerKeyboardEvent(KeyboardEventProcess);
	
	//mouse	-> mouseEvent.c
	registerMouseEvent(MouseEventProcess);

	registerCharEvent(CharEventProcess);
	
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
	/**
	 * \brief 显示游戏界面函数，用于控制不同页面的跳转和图形绘制
	 * 
	 * \param game_status 游戏状态
	 *						-1 : 第二个界面 -2 : 游戏胜利界面 -3 : 游戏失败界面
	 *						0,1: 游戏界面	2 : 重启游戏		 3 : 开始界面
	 *						4  : 排行榜		5 : 自动求解七巧板 6 : 自定义七巧板界面
	 *						7  : 选择地图界面8 : 信息提示界面
	 * \relates 需要注意的是，游戏界面的显示是通过不断的刷新来实现的，因此在每次刷新时都会调用display函数
	 *			在display函数中，会根据game_status的值来判断当前应该显示哪个界面
	 *			
	 *			在更改画笔粗细、画笔颜色、填充颜色、字体大小等时，需要注意的是，这些属性的改变是全局的，所以需要及时还原避免出现问题
	 */
	DisplayClear();
	/*Part 背景音乐的设置*/
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

	/*Part 画出整体界面*/
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
			InitButton();	//画出整体界面	button.c
			EchoInfo();		//显示分数和时间	button.c
			win_page();		//显示成功界面	ui.c
			user_save();	//保存用户信息	user.c
			SetPointSize(20);
			if (button(GenUIID(0), 5.9, 3, WindowWidth / 5, 0.5, "new game")) {
				game_status = 7;
			}
			SetPointSize(1);
			break;
		}
		case -3:		//game lose
		{
			InitButton();	//画出整体界面 button.c
			EchoInfo();		//显示分数和时间	button.c
			lose_page();	//显示失败界面	ui.c
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
			_background();	//画出背景图形	ui.c
			InitButton();	//画出整体界面	button.c
			EchoInfo();		//显示分数和时间	button.c
			menu();			//显示菜单栏	ui.c
			mciSendString("open ./file/game_music.mp3 alias bkmusic", NULL, 0, NULL);
			mciSendString("play bkmusic repeat", NULL, 0, NULL);     //循环播放音乐
			/*Part 形状和地图的绘制*/
			Shape* temp = head;
			while (temp) {
				DrawShape(temp);
				temp = temp->next;
			}
			DrawMap(current_map);
			DrawSubmap(current_map);
			break; 
		}//end of case 1
		case 2:			//restart 重启游戏，重新生成地图和形状，重新开始计时
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
			welcome();				//显示欢迎界面	ui.c
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
			break; 
		}
		case 4:			//ranklist
		{
			background();				//画出背景图形	ui.c
			echo_ranklist(current_map);	//显示排行榜		ranklist.c
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
			background();	//画出背景图形	ui.c
			//solve();		//自动求解		solve.c
			break;
		}
		case 6:			//createMap
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
		case 8:			//game intro 信息提示界面
		{
			InitButton();	//画出按钮	  ui.c
			background();	//画出背景图形 ui.c
			echo_intro();	//显示信息提示 ui.c
		}
		default:
			break;
	}
}


