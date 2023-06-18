#ifndef _MAIN_H_
#define MAIN_H

#include "./frame/shape.h"

#define TIME_LEFT 80				//剩余时间
#define WindowWidth 14				//窗口宽度
#define WindowHeight 9				//窗口高度
#define TIME_INTERVAL 50			//时间间隔

extern int game_status;				//游戏状态，用于控制游戏流程
extern double current_time;			//当前时间
extern int Is_Hint;					//是否提示
extern int page;					//选择游戏界面的页数
extern int MapNumber_MAX;			//地图数量
extern int colorindex;				//闪烁时颜色下标


void display();						//刷新显示	
void main();						//主函数

extern Shape* head, * tail;			//七巧板链表
extern Shape* mapShape;				//当前地图七巧板的指针
extern Shape* Map_head, * Map_tail; //地图七巧板链表
extern linkedlistADT submap_line_link_head; //作为line链表的头结点
extern linkedlistADT submap_line_link_tail; //作为line链表的尾结点


#endif // !_MAIN_H_
