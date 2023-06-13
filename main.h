#ifndef _MAIN_H_
#define MAIN_H

#include "./frame/shape.h"

#define MAX_GAME_STATUS 8
#define TIME_LEFT 80
#define WindowWidth 14
#define WindowHeight 9

extern int game_status;				//��Ϸ״̬�����ڿ�����Ϸ����
extern double current_time;			//��ǰʱ��
extern int Is_Hint;
extern int page;
extern int MapNumber_MAX;			//��ͼ����

extern char colorList[100][100];
extern const int colorNumber;

void display();
void main();

extern Shape* head, * tail, * mapShape;
extern Shape* Map_head, * Map_tail;
typedef enum {
	gameTimer, boxTimer, buttonTimer, rankTimer, infoTimer, solveTimer��
}Mytimer;


#endif // !_MAIN_H_
