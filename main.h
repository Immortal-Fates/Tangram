#ifndef _MAIN_H_
#define MAIN_H

#include "./frame/shape.h"

#define TIME_LEFT 80				//ʣ��ʱ��
#define WindowWidth 14				//���ڿ��
#define WindowHeight 9				//���ڸ߶�
#define TIME_INTERVAL 50			//ʱ����

extern int game_status;				//��Ϸ״̬�����ڿ�����Ϸ����
extern double current_time;			//��ǰʱ��
extern int Is_Hint;					//�Ƿ���ʾ
extern int page;					//ѡ����Ϸ�����ҳ��
extern int MapNumber_MAX;			//��ͼ����
extern int colorindex;				//��˸ʱ��ɫ�±�


void display();						//ˢ����ʾ	
void main();						//������

extern Shape* head, * tail;			//���ɰ�����
extern Shape* mapShape;				//��ǰ��ͼ���ɰ��ָ��
extern Shape* Map_head, * Map_tail; //��ͼ���ɰ�����
extern linkedlistADT submap_line_link_head; //��Ϊline�����ͷ���
extern linkedlistADT submap_line_link_tail; //��Ϊline�����β���


#endif // !_MAIN_H_
