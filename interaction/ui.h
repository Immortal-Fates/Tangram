#ifndef _BUTTON_H_
#define _BUTTON_H_

/*Part 文字*/

void EchoInfo(void);		//游玩界面的分数和时间
void echo_intro(void);		//游戏介绍
void ranklist_ui(void);		//排行榜


/*Part 按钮*/

void InitButton(void);			//初始化按钮
void menu(void);				//菜单栏
void welcome(void);				//欢迎界面
void button_page_one(void);		//初始界面的button
void select_game_page(void);	//选择游戏界面的button
void create_map_page(void);		//创建地图界面的button

/*Part 背景*/

void background(void);			//其他界面的背景
void _background(void);			//开始游戏界面的背景
void lose_page(void);			//失败界面
void win_page(void);			//成功界面

#endif // !_BUTTON_H_
