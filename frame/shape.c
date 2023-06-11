/*****************************************************************//**
 * \file   shape.c
 * \brief  用于图形的定义，包括图形的初始化，图形的移动，图形的旋转，图形的缩放，图形的绘制
 * \author Philfan
 * \date   June 2023
 *********************************************************************/
#include "../Header.h"
#include "shape.h"
Shape *head = NULL, * tail = NULL;
char colorList[100][100] = {
	"Green","Orange","Blue", "Violet", "Cyan","Yellow", "Red",
	"Black", "Dark Gray", "Gray", "Brown",
	 "Light Gray","White", "Magenta" };
const int colorNumber = 14;

Shape* tangramshape[7];
void InitColor() {
	/**
	 * \brief: 初始化颜色
	 */
	DefineColor("Black", 0, 0, 0);
	DefineColor("Dark Gray", .35, .35, .35);
	DefineColor("Gray", .6, .6, .6);
	DefineColor("Light Gray", .75, .75, .75);
	DefineColor("White", 1, 1, 1);
	DefineColor("Brown", .35, .20, .05);
	DefineColor("Red", 1, 0, 0);
	DefineColor("Orange", 1, .40, .1);
	DefineColor("Yellow", 1, 1, 0);
	DefineColor("Green", 0, 1, 0);
	DefineColor("Blue", 0, 0, 1);
	DefineColor("Violet", .93, .5, .93);
	//todo: define color
	DefineColor("Magenta", 1, 0, 1); //洋红色
	DefineColor("Cyan", 0, 1, 1); //青色
	DefineColor("Tan", 0.2,0.2,0.2); //#3b4383
	DefineColor("Tan2", 230.0 / 250.0, 76.0 / 250.0, 50.0 / 250.0); //#e64c32
	DefineColor("Tan3", 251.0 / 250.0, 243.0 / 250.0, 20.0 / 250.0); //#fbf314
	DefineColor("Tan4", 4.0 / 250.0, 156.0 / 250.0, 212.0 / 250.0); //#049cd4
	DefineColor("Tan5", 148.0 / 250.0, 44.0 / 250.0, 124.0 / 250.0); //#942c7c
	DefineColor("Tan6", 140.0 / 250.0, 187.0 / 250.0, 59.0 / 250.0); //#8cbb3b
	DefineColor("Tan6", 203.0 / 250.0, 67.0 / 250.0, 72.0 / 250.0); //#cb4348
}
Shape *inventShape(bool fill, int shapetype, string _color,
	double px, double py, double w, double h,int angle,int Pensize, ... ) {
	/**
	 * .
	 * \brief: 根据给出的参数，创建一个图形，并加入到链表中
	 * 
	 * \param fill				是否填充
	 * \param shapetype			图形类型
	 * \param _color			颜色
	 * \param px				参考点x坐标值
	 * \param py				参考点y坐标值
	 * \param w					图形的宽度
	 * \param h					图形的高度
	 * \param angle				旋转角度
	 * \param Pensize			画笔粗细
	 * \param vertexNum			顶点数（可变参数）
	 * \return					返回一个指向图形的结构体指针 
	 */
	
	//处理可变参数Pensize和index



	va_list arg_ptr; 
	va_start(arg_ptr, Pensize);
	int index = va_arg(arg_ptr, int);
	va_end(arg_ptr);
	
	//创建图形，把数据初始化到结构体中
	Shape *t = (Shape *)malloc(sizeof(Shape));
	t->isFilled = fill;
	t->shape = shapetype;
	strcpy(t->color, _color);
	t->pX = px;
	t->pY = py;
	t->width = w;
	t->height = h;
	t->angle = angle-1;
	t->isSelected = FALSE;
	t->Pensize = Pensize;
	t->index = index;
	t->next = t->last = NULL;
	

	if (t->shape != 3) { //非地图，加到链表中
		if (!head) head = tail = t;
		else {
			tail->next = t;
			t->last = tail;
			tail = t;
		}
	}
	return t;
}

void DrawShape(Shape* t) {

	/**
	 * \brief:		绘出给定的图形，其中图形的数据均存储在指针t指向的结构体中
	 *				其中记录点的数组下标从0开始，记录边的数组下标从1开始
	 * \param t:	存储图形的数据的结构体指针
	 */
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	SetPenSize(t->Pensize);
	SetPenColor(t->color);

	if(t->isFilled)   //if filled, then fill the shape with full color 
		StartFilledRegion(1);
	switch (t->shape) {
		case 0: //triangle
		{
			t->vertexNum = 3;
			// 将旋转角度转换为弧度
			double radian = t->angle * 45 * (M_PI / 180.0);

			// 计算顶点坐标
			double x1 = t->pX;
			double y1 = t->pY;
			double x2 = t->pX + t->width * cos(radian);
			double y2 = t->pY + t->width * sin(radian);
			double x3 = t->pX - t->width * sin(radian);
			double y3 = t->pY + t->width * cos(radian);
			//记录顶点坐标
			t->vertex[0].x = x1;
			t->vertex[0].y = y1;
			t->vertex[1].x = x2;
			t->vertex[1].y = y2;
			t->vertex[2].x = x3;
			t->vertex[2].y = y3;
			//记录边的数据
			t->edge[0].start.x = x1;
			t->edge[0].start.y = y1;
			t->edge[0].end.x = x2;
			t->edge[0].end.y = y2;
			t->edge[1].start.x = x2;
			t->edge[1].start.y = y2;
			t->edge[1].end.x = x3;
			t->edge[1].end.y = y3;
			t->edge[2].start.x = x3;
			t->edge[2].start.y = y3;
			t->edge[2].end.x = x1;
			t->edge[2].end.y = y1;
			

			break;
		}//end of case 0
		case 1: //box
		{
			t->vertexNum = 4;
			// 将旋转角度转换为弧度
			double radian = (t->angle*45) * (M_PI / 180.0);

			// 计算旋转后的顶点坐标 //奇变偶不变，符号看象限（不要看错顺序）
			double x1 = t->pX + 0.5 * t->width * cos(radian);
			double y1 = t->pY + 0.5 * t->width * sin(radian);
			double x2 = t->pX - 0.5 * t->width * sin(radian);
			double y2 = t->pY + 0.5 * t->width * cos(radian);
			double x3 = t->pX - 0.5 * t->width * cos(radian);
			double y3 = t->pY - 0.5 * t->width * sin(radian);
			double x4 = t->pX + 0.5 * t->width * sin(radian);
			double y4 = t->pY - 0.5 * t->width * cos(radian);

			
			//记录顶点坐标
			t->vertex[0].x = x1;
			t->vertex[0].y = y1;
			t->vertex[1].x = x2;
			t->vertex[1].y = y2;
			t->vertex[2].x = x3;
			t->vertex[2].y = y3;
			t->vertex[3].x = x4;
			t->vertex[3].y = y4;
			//记录边的数据
			t->edge[0].start.x = x1;
			t->edge[0].start.y = y1;
			t->edge[0].end.x = x2;
			t->edge[0].end.y = y2;
			t->edge[1].start.x = x2;
			t->edge[1].start.y = y2;
			t->edge[1].end.x = x3;
			t->edge[1].end.y = y3;
			t->edge[2].start.x = x3;
			t->edge[2].start.y = y3;
			t->edge[2].end.x = x4;
			t->edge[2].end.y = y4;
			t->edge[3].start.x = x4;
			t->edge[3].start.y = y4;
			t->edge[3].end.x = x1;
			t->edge[3].end.y = y1;
			break;
		}//end of case 1
		case 2: //parallelogram
		{
			t->vertexNum = 4;
			double radian = t->angle * 45 * (M_PI / 180.0);

			// 计算旋转后的顶点坐标
			// 巧妙利用平移不变性质，从而不用计算复杂的旋转后坐标，节约时间
			double x1 = t->pX;
			double y1 = t->pY;
			double x2 = t->pX + t->width * cos(radian);
			double y2 = t->pY + t->width * sin(radian);
			
			double x4 = t->pX + t->height * cos((t->angle * 45 +45.0) * (M_PI / 180.0));
			double y4 = t->pY + t->height * sin((t->angle * 45 + 45.0) * (M_PI / 180.0));


			//记录顶点坐标
			double x3 = x2+x4-x1;
			double y3 = y2+y4-y1;
			t->vertex[0].x = x1;
			t->vertex[0].y = y1;
			t->vertex[1].x = x2;
			t->vertex[1].y = y2;
			t->vertex[2].x = x3;
			t->vertex[2].y = y3;
			t->vertex[3].x = x4;
			t->vertex[3].y = y4;
			//记录边的数据
			t->edge[0].start.x = x1;
			t->edge[0].start.y = y1;
			t->edge[0].end.x = x2;
			t->edge[0].end.y = y2;
			t->edge[1].start.x = x2;
			t->edge[1].start.y = y2;
			t->edge[1].end.x = x3;
			t->edge[1].end.y = y3;
			t->edge[2].start.x = x3;
			t->edge[2].start.y = y3;
			t->edge[2].end.x = x4;
			t->edge[2].end.y = y4;
			t->edge[3].start.x = x4;
			t->edge[3].start.y = y4;
			t->edge[3].end.x = x1;
			t->edge[3].end.y = y1;
			break;
		}//end of case 2
		case -1: {
			// 记录顶点坐标
			t->vertex[0].x = t->pX;
			t->vertex[0].y = t->pY;
			t->vertex[1].x = t->pX + t->width;
			t->vertex[1].y = t->pY;

			// 记录边的数据
			t->edge[0].start.x = t->pX;
			t->edge[0].start.y = t->pY;
			t->edge[0].end.x = t->pX + t->width;
			t->edge[0].end.y = t->pY;
			MovePen(t->pX,t->pY);
			DrawLine(t->width, 0);
			break;
		}
		
	}//end of switch(t->shape)
	if (t->shape != -1) {
		MovePen(t->vertex[0].x, t->vertex[0].y);
		for (int i = 0; i <= t->vertexNum - 1; i++) {
			//pencolor = t->edge[i].lineColor;
			//SetPenColor(pencolor);
			DrawLine(t->edge[i].end.x - t->edge[i].start.x, t->edge[i].end.y - t->edge[i].start.y);
		}
	}
	
	if (t->isFilled) EndFilledRegion();//结束填充
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor
}

bool isInShape(Shape* t, double x, double y) {
	/**
	 * \brief 判断点P是否在图形内
	 *			三角形利用向量叉乘法判断，四边形利用射线法进行判断
	 * \param t: 图形指针，指向待判断的图形
	 * \param x: P点的x坐标
	 * \param y: P点的y坐标
	 * \return : TURE of FALSE
	 */
	if (!t) return FALSE;
	switch (t->shape) {
		case 0: //triangle
		{
			// 获取三角形的顶点坐标
			double x1 = t->vertex[0].x;
			double y1 = t->vertex[0].y;
			double x2 = t->vertex[1].x;
			double y2 = t->vertex[1].y;
			double x3 = t->vertex[2].x;
			double y3 = t->vertex[2].y;

			// 利用叉乘法判断点是否在三角形内部
			double cross1 = (x2 - x1) * (y - y1) - (x - x1) * (y2 - y1);
			double cross2 = (x3 - x2) * (y - y2) - (x - x2) * (y3 - y2);
			double cross3 = (x1 - x3) * (y - y3) - (x - x3) * (y1 - y3);

			if ((cross1 >= 0 && cross2 >= 0 && cross3 >= 0) ||
				(cross1 <= 0 && cross2 <= 0 && cross3 <= 0)) {
				return TRUE;
			}
			else {
				return FALSE;
			}
			break;
		}
		case 1: case 2://box
		{
			// 获取四边形的边界点坐标
			double x1 = t->vertex[0].x;
			double y1 = t->vertex[0].y;
			double x2 = t->vertex[1].x;
			double y2 = t->vertex[1].y;
			double x3 = t->vertex[2].x;
			double y3 = t->vertex[2].y;
			double x4 = t->vertex[3].x;
			double y4 = t->vertex[3].y;

			// 使用射线法判断点是否在四边形内部
			bool inside = FALSE;

			// 射线与四边形的边界线段的交点个数
			int intersectionCount = 0;

			// 通过射线与四边形的每条边求交点
			if ((y >= y1 && y < y2) || (y >= y2 && y < y1)) {
				double xIntersection = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
				if (x <= xIntersection) {
					intersectionCount++;
				}
			}
			if ((y >= y2 && y < y3) || (y >= y3 && y < y2)) {
				double xIntersection = (y - y2) * (x3 - x2) / (y3 - y2) + x2;
				if (x <= xIntersection) {
					intersectionCount++;
				}
			}
			if ((y >= y3 && y < y4) || (y >= y4 && y < y3)) {
				double xIntersection = (y - y3) * (x4 - x3) / (y4 - y3) + x3;
				if (x <= xIntersection) {
					intersectionCount++;
				}
			}
			if ((y >= y4 && y < y1) || (y >= y1 && y < y4)) {
				double xIntersection = (y - y4) * (x1 - x4) / (y1 - y4) + x4;
				if (x <= xIntersection) {
					intersectionCount++;
				}
			}

			// 判断点是否在四边形内部
			if (intersectionCount % 2 == 1) {
				inside = TRUE;
			}
			return inside;
			break;
		}//end of case1 and case 2
		default:
		{
			return FALSE;
			break;
		}
	}
}
void Initshape(void) {
	/**
	 * \brief 初始化七巧板图形
	 */
	
	int penwidth = 1;
	tangramshape[0] = inventShape(1, 0, "Brown", 1, 6.5, 2, 2, 1, penwidth,1);
	tangramshape[1] = inventShape(1, 0, "Orange", 1, 4, 2, 2, 1, penwidth,2);					//最大三角形
	tangramshape[2] = inventShape(1, 0, "Blue", 11, 6, sqrt(2), sqrt(2), 1, penwidth,3);		//2nd 三角形
	tangramshape[3] = inventShape(1, 0, "Red", 1, 2.5, 1, 1, 1, penwidth,4);					//3rd 三角形
	tangramshape[4] = inventShape(1, 0, "Black", 1, 1, 1, 1, 1, penwidth,5);					//3rd 三角形
	tangramshape[5] = inventShape(1, 1, "Yellow", 12, 4, sqrt(2), 1, 1, penwidth,6);			//box
	tangramshape[6] = inventShape(1, 2, "Gray", 11, 2, sqrt(2), 1, 1, penwidth,7);			//平行四边形
}


void delete_shape(void){
	/**
	 * \brief 删除图形
	*/
	while (head) {
		Shape* temp = head;
		head = head->next;
		free(temp);
	}
}
