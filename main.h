#ifndef _MAIN_H_
#define MAIN_H

#include "./frame/shape.h"

#define MAX_GAME_STATUS 8
#define TIME_LEFT 60
extern int game_status;			//游戏状态，用于控制游戏流程
extern double current_time;		//当前时间
extern double score;				//当前分数
extern double WindowWidth;		//窗口宽度
extern double window_height;		//窗口高度
extern int MapNumber_MAX;		//地图数量

extern char colorList[100][100];
extern const int colorNumber;

void display();
void Main();

extern Shape* head, * tail, * mapShape;
extern Shape* Map_head, * Map_tail;
typedef enum {
	gameTimer, boxTimer, buttonTimer, rankTimer, infoTimer, solveTimer，
}Mytimer;

#endif // !_MAIN_H_
