#ifndef _SHAPE_H_
#define _SHAPE_H_


#define M_PI       3.14159265358979323846   // pi

#include <stdbool.h>

typedef struct Node {
	double x, y;
}node;
typedef struct Line {
	node start, end;
	char lineColor[200];	//线的颜色
}line;
typedef struct tangram {
	bool isvisible;
	int vertex_number;
	node vertex[200];
	line edge[200];
	char color[200];
}sub_tangram;


typedef struct Tangram {
	int num;			//图形编号
	bool isFilled;		// 0-not filled 1-filled
	int shape;			// 0-triangle  1-box  2-parallelogram 3-map
	char color[200];		// 图形的颜色
	char fix_color[200];	// 固定的颜色
	double pX, pY, width, height;
	/*
		pX, pY is the left bottom point(triangle,parallelogram),middle point(box)
		width, height is the width and height of the shape
		在正方形中，width是对角线
	*/
	int Pensize;					//画笔粗细
	int angle;						//旋转角度 0,45,90,135,180,225,270,315
	node vertex[200];				//图形的顶点坐标
	line edge[200];					//图形的边
	bool isSelected;				//是否被选中
	struct Tangram* next, * last;	//指向下一个和上一个图形的指针
	int vertexNum;					//顶点数
	int map_number;					//地图编号
	sub_tangram graphics[10];		
}Shape;//存储图形的结构体
extern Shape* tangramshape[7];



void DrawShape(Shape* t);//画图形
Shape *inventShape(bool fill, int shapetype, char * _color,
	double px, double py, double w, double h,int angle,int Pensize, ... );//创建图形
void Initshape(void);							//初始化七个七巧板图形
void delete_shape(void);						//删除图形
bool isInShape(Shape* t, double x, double y);	//判断点是否在图形内

void movelinklist(Shape* temp);	//将图形指针shape移到链表末尾，实现最后画出的是最近修改的图形			
#endif // !_SHAPE_H_
