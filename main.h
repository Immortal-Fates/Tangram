#ifndef _MAIN_H_
#define MAIN_H

#include "./frame/shape.h"

#define MAX_GAME_STATUS 8
#define TIME_LEFT 80
#define WindowWidth 14
#define WindowHeight 9
#define TIME_INTERVAL 50
extern int game_status;				//游戏状态，用于控制游戏流程
extern double current_time;			//当前时间
extern int Is_Hint;
extern int page;
extern int MapNumber_MAX;			//地图数量

extern char colorList[100][100];
extern const int colorNumber;
extern linkedlistADT submap_line_link_head; //作为line链表的头结点
extern linkedlistADT submap_line_link_tail; //作为line链表的尾结点
void display();
void main();

extern Shape* head, * tail, * mapShape;
extern Shape* Map_head, * Map_tail;
typedef enum {
	gameTimer, boxTimer, buttonTimer, rankTimer, infoTimer, solveTimer，
}Mytimer;


#endif // !_MAIN_H_
