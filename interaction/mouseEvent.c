/*****************************************************************//**
 * \file   mouseEvent.c
 * \brief  鼠标响应处理函数，实现对鼠标事件的响应
 *			实现的功能：
 *				1.选中图形，改变颜色；
 *				2.旋转图形；
 *				3.移动图形
 *				4.移动时根据阈值，自动吸附到最近的边界
 * 
 * \author PhilFan
 * \date   May 2023
 *********************************************************************/
#include "extgraph.h"
#include "../Header.h"
#include "mouseEvent.h"


void MouseEventProcess(int x, int y, int button, int event){
	/**
	 * \brief: 鼠标左键按下 逆时针旋转；鼠标右键按下 顺时针旋转；鼠标中键长按拖动，实现图形移动
	 * 
	 * \param x			鼠标x坐标
	 * \param y			鼠标y坐标
	 * \param button	鼠标按键
	 * \param event		鼠标按键事件
	 */

	static bool MouseisMove = FALSE;//移动
	double dx,dy;//鼠标移动的距离
	double mouseX, mouseY;//鼠标目前的位置
	static double lastX = 0.0, lastY = 0.0;//利用static记录鼠标的位置，用于计算鼠标移动的距离

	mouseX = ScaleXInches(x);//pixel -> inches
	mouseY = ScaleYInches(y);

	uiGetMouse(x, y, button, event);
	
	switch (event)
	{
		
		case BUTTON_DOWN://鼠标按下
			if (button == LEFT_BUTTON) {
				lastX = mouseX;
				lastY = mouseY;
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{
						
						MouseisMove = TRUE;
						temp->isSelected = TRUE;		//选中的时候改变该图形的状态，防止移动的时候影响其他图形
						
						strcpy(temp->fix_color, temp->color);//记录原来的颜色
						strcpy(temp->color, "Green");		//选中的时候改变颜色
						if (Is_Hint) {
							DrawSubmap(&mapShape->graphics[temp->index]);
						}
						break;
					}
					temp = temp->next;
				}
			}

			/* Part 1: 增加图形（用于debug） */
			//if (button == MIDDLE_BUTTON && mouseY >= 0 && mouseY <= 8) {
			//	inventShape(0, 0, "Red", ScaleXInches(x), ScaleYInches(y), 1, 1, rand() % 8, rand() % 10);//随机生成一个三角形
			//}
			
			/* Part2: 旋转图形 */
			if ((button == RIGHT_BUTTON || button == LEFT_BUTTON)
				&& mouseY >= 0 && mouseY <= 9) {
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{
						if (button == RIGHT_BUTTON) //右键顺时针
							temp->angle = (temp->angle + 1) % 8;
						//if(button == LEFT_BUTTON) //左键逆时针
						//	temp->angle = (temp->angle + 7) % 8;
						break;
					}
					temp = temp->next;
				}
			}
			display();
			break;
		
		case BUTTON_UP://鼠标松开,停止移动
			MouseisMove = FALSE;
			Shape* temp = head;
			while (temp)
			{
				if (temp->isSelected == TRUE)
				{
					temp->isSelected = FALSE;//松开鼠标的时候改变该图形的状态，清除所有的状态，恢复原样
					strcpy(temp->color,temp->fix_color);//记录原来的颜色
					SnapToLine(temp, THRESHOLD);
					SnaptoPoint(temp, THRESHOLD);
					judge_complishment();
					break;
				}
				temp = temp->next;
			}
			display();
			break;
		
		case MOUSEMOVE://鼠标移动,移动图形
			if (MouseisMove) {
				dx = mouseX - lastX;
				dy = mouseY - lastY;//计算鼠标移动的距离
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && temp->isSelected == TRUE && !game_status)//选中的时候才能移动
					{
						temp->pX += dx;
						temp->pY += dy;
						break;
					}
					temp = temp->next;
				}
				lastX = mouseX;
				lastY = mouseY;//更新鼠标的位置
			}
			display();
			break;
	}
	//最后更新界面
}



/*对线的吸附*/
int isequal(double a, double b) {
	/**
	 * \brief 判断两个浮点数是否相等
	 * \param a 浮点数1
	 * \param b	浮点数2
	 * \relates ERROR 精确度 设置为0.0001
	 */
	if (fabs(a - b) < ERROR)
		return 1;
	else
		return 0;
}
 void SnapToLine(Shape* shape, double threshold) {
	/**
	 * \brief: 将图形自动吸附到邻近的线条上（包括地图的线条和图形的线条）
	 * \param shape: 要移动的图形
	 * \param threshold: 吸附距离的阈值
	 * \param mapShape: 当前地图的图形指针 Shape*类型
	 */
	
	//FILE *ErrorFile = fopen("./file/Errorsnap.txt", "w+");
	for (int j = 0; j <= shape->vertexNum - 1; j++) {
		
		line* shapeLine = &(shape->edge[j]);
		//fprintf(ErrorFile, "##\n\n %d\n", j);
		//fprintf(ErrorFile, "%lf %lf\n",shapeLine->start.x, shapeLine->start.y);
		//fprintf(ErrorFile, "%lf %lf\n", shapeLine->end.x, shapeLine->end.y);
		for (int i = 0; i <= mapShape->vertexNum - 1; i++) {//遍历所有线条
			line* mapLine = &(mapShape->edge[i]);
			// 判断线条是否平行
			if (IsParallel(mapLine, shapeLine)) {
				// 计算两条平行线之间的距离
				double distance = DistanceBetweenLines(mapLine, shapeLine);
				// 如果距离小于阈值，则将图形移动到平行线重合
				if (distance < threshold) {
					MoveToParallelLines(mapLine, shapeLine, distance, shape);

					/* 用于debug 
					fprintf(ErrorFile, "distance:%lf\n", distance);
					fprintf(ErrorFile, "shapeLine->start.x:%lf ", shapeLine->start.x);
					fprintf(ErrorFile, "shapeLine->start.y:%lf ", shapeLine->start.y);
					fprintf(ErrorFile, "shapeLine->end.x:%lf ", shapeLine->end.x);
					fprintf(ErrorFile, "shapeLine->end.y:%lf\n", shapeLine->end.y);
					fprintf(ErrorFile, "mapLine->start.x:%lf ", mapLine->start.x);
					fprintf(ErrorFile, "mapLine->start.y:%lf ", mapLine->start.y);
					fprintf(ErrorFile, "mapLine->end.x:%lf ", mapLine->end.x);
					fprintf(ErrorFile, "mapLine->end.y:%lf\n", mapLine->end.y);
					fprintf(ErrorFile, "i:%d j:%d\n", i, j);
					*/
				}
			}
		}
		Shape* t = head;
		while (t)
		{
			if (t->isSelected == FALSE)//没有被选中
			{
				for (int i = 0; i < t->vertexNum; i++) {
					line* oshapeLine = &(t->edge[i]);// 判断线条是否平行
					if (IsParallel(oshapeLine, shapeLine)) { // 计算两条平行线之间的距离
						double distance = DistanceBetweenLines(oshapeLine, shapeLine);// 如果距离小于阈值，则将图形移动到平行线重合
						if (distance < threshold) {
							MoveToParallelLines(oshapeLine, shapeLine, distance, shape);
						}
					}
				}				
			}
			t = t->next;
		}
	}
	//fclose(ErrorFile);
 }
 bool IsParallel(line* line1, line* line2) {//done
	/**
	 * \brief: 判断两条线是否平行
	 * \param line1: 第一条线
	 * \param line2: 第二条线
	 * \return : 如果两条线平行，则返回true；否则返回false
	 */
	double dx1 = line1->end.x - line1->start.x;
	double dy1 = line1->end.y - line1->start.y;
	double dx2 = line2->end.x - line2->start.x;
	double dy2 = line2->end.y - line2->start.y;
	if(isequal(dx1 * dy2 , dx2 * dy1)){
		if(Iscrossed(line1,line2))
			return TRUE;
	}
	return FALSE;
 }
 int  Iscrossed(line* line1, line* line2) {
	 /**
	  * .\brief 判断两条线段在水平和垂直方向有无交叉部分
	  * \param line1	第一条线段
	  * \param line2	第二条线段
	  * \return 若没有交叉部分，返回值为0 有交叉部分 返回正实数
	  */
	 double dx1 = line1->end.x - line1->start.x;
	 double dy1 = line1->end.y - line1->start.y;
	 double dx2 = line2->end.x - line2->start.x;
	 double dy2 = line2->end.y - line2->start.y;
	 //计算线段在水平方向上的投影范围
	 double minLine1X = line1->start.x < line1->end.x ? line1->start.x : line1->end.x;
	 double maxLine1X = line1->start.x > line1->end.x ? line1->start.x : line1->end.x;
	 double minLine2X = line2->start.x < line2->end.x ? line2->start.x : line2->end.x;
	 double maxLine2X = line2->start.x > line2->end.x ? line2->start.x : line2->end.x;
	 // 计算线段在垂直方向上的投影范围
	 double minLine1Y = line1->start.y < line1->end.y ? line1->start.y : line1->end.y;
	 double maxLine1Y = line1->start.y > line1->end.y ? line1->start.y : line1->end.y;
	 double minLine2Y = line2->start.y < line2->end.y ? line2->start.y : line2->end.y;
	 double maxLine2Y = line2->start.y > line2->end.y ? line2->start.y : line2->end.y;

	 if (isequal(dx1,0) && isequal(dx2, 0)) {
		 if (maxLine1Y >= minLine2Y && maxLine2Y >= minLine1Y)
			 return 1;
	 }
	 else if (isequal(dy1, 0) && isequal(dy2, 0)) { 
		 if (maxLine1X >= minLine2X && maxLine2X >= minLine1X)
			 return 2;
	 }
	 else if (maxLine1X >= minLine2X && maxLine2X >= minLine1X) {
		 if (maxLine1Y >= minLine2Y && maxLine2Y >= minLine1Y) {
			 return 3;
		 }
	 }
	 return 0;
 }
 double DistanceBetweenLines(line* line1, line* line2) {//done
	/**
	 * \brief: 计算两条平行线之间的距离
	 *
	 * \param line1: 第一条线
	 * \param line2: 第二条线
	 * \return : 两条平行线之间的距离
	 */
	 // 计算线1的方向向量
	 if (IsParallel(line1, line2) == FALSE) {
		 return EOF;
	}
	double dx1 = line1->end.x - line1->start.x;
	double dy1 = line1->end.y - line1->start.y;

	// 计算线1的单位方向向量
	double length1 = sqrt(dx1 * dx1 + dy1 * dy1);
	double ux1 = dx1 / length1;
	double uy1 = dy1 / length1;


	// 计算两条平行线之间的距离
	double distance = fabs((line2->start.x - line1->start.x) * (-1.0) * uy1 + (line2->start.y - line1->start.y) * ux1);
	return distance;

 }
 void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape) {//done
	 /**
	  * \brief: 已知两条平行线之间的距离，将图形移动到平行线重合
	  *
	  * \param line1: 第一条平行线
	  * \param line2: 第二条平行线 shapeline
	  * \param distance: 两条平行线之间的距离
	  * \param shape: 要移动的图形
	  */
	 //*line1->lineColor = "Red";
	 //*line2->lineColor = "Red";
	 double dx2 = line2->end.x - line2->start.x;
	 double dy2 = line2->end.y - line2->start.y;

	 double length2 = sqrt(dx2 * dx2 + dy2 * dy2);
	 double ux2 = dx2 / length2;
	 double uy2 = dy2 / length2;

	 double dx = distance * uy2;  // 平移距离乘以line2的单位方向向量的垂直分量
	 double dy = -distance * ux2; // 平移距离乘以line2的单位方向向量的垂直分量的负值

	 double dx1 = line1->start.x - line2->start.x;
	 double dy1 = line1->start.y - line2->start.y;
	 if(dx*dx1 + dy*dy1 < 0) { // 如果平移距离的方向与line1的方向相反，则取负值
		 dx = -dx;
		 dy = -dy;
	 }
	 // 计算图形平移dx和dy的距离
	 shape->pX += dx;
	 shape->pY += dy;

	 display();
 }

/*对点的吸附*/
 void SnaptoPoint(Shape* shape, double threshold) {
	 /**
	 * \brief: 将图形自动吸附到邻近的点上
	 *
	 * \param shape: 要移动的图形
	 * \param threshold: 吸附距离的阈值
	 */
	 for (int j = 0; j <= shape->vertexNum - 1; j++) {
		 node* shapeNode, * mapNode, * oshapeNode;
		 shapeNode = &shape->vertex[j];
		 for (int i = 0; i <= mapShape->vertexNum - 1; i++) {
			 mapNode = &mapShape->vertex[i];
			 double distance = DistanceBetweenPoints(shapeNode, mapNode);
			 if (distance < threshold) {
				 MoveToNearestPoint(shapeNode, mapNode, shape);
			 }
		 }
		 Shape* t = head;
		 while (t)
		 {
			 if (t->isSelected == FALSE)//没有被选中
			 {

				 for (int i = 0; i < t->vertexNum; i++) {
					 oshapeNode = &t->vertex[i];
					 double distance = DistanceBetweenPoints(shapeNode, oshapeNode);
					 if (distance < threshold) {
						 MoveToNearestPoint(shapeNode, oshapeNode, shape);
					 }
				 }
			 }
			 t = t->next;
		 }
	 }
 }
 double DistanceBetweenPoints(node* shapeNode, node* mapNode) {
	//done
	 /**
	  * \brief: 计算两个点之间的距离
	  *
	  * \param shapeNode: 第一个点
	  * \param mapNode: 第二个点
	  * \return : 两个点之间的距离
	  */
	 double dx = shapeNode->x - mapNode->x;
	 double dy = shapeNode->y - mapNode->y;
	 double distance = sqrt(dx * dx + dy * dy);
	 return distance;
 }
 void MoveToNearestPoint(node* shapeNode, node* mapNode, Shape* shape) {
	/**
	  * \brief: 将图形移动到最近的点
	  *
	  * \param shapeNode: 图形的点
	  * \param mapNode: 地图的点
	  * \param shape: 要移动的图形
	  */
	 double dx = mapNode->x - shapeNode->x;
	 double dy = mapNode->y - shapeNode->y;
	 shape->pX += dx;
	 shape->pY += dy;
	 display();
 }
