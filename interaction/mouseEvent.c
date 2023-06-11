/*****************************************************************//**
 * \file   mouseEvent.c
 * \brief  �����Ӧ��������ʵ�ֶ�����¼�����Ӧ
 *			ʵ�ֵĹ��ܣ�
 *				1.ѡ��ͼ�Σ��ı���ɫ��
 *				2.��תͼ�Σ�
 *				3.�ƶ�ͼ��
 *				4.�ƶ�ʱ������ֵ���Զ�����������ı߽�
 * 
 * \author PhilFan
 * \date   May 2023
 *********************************************************************/
#include "extgraph.h"
#include "../Header.h"
#include "mouseEvent.h"


void MouseEventProcess(int x, int y, int button, int event){
	/**
	 * \brief: ���������� ��ʱ����ת������Ҽ����� ˳ʱ����ת������м������϶���ʵ��ͼ���ƶ�
	 * 
	 * \param x			���x����
	 * \param y			���y����
	 * \param button	��갴��
	 * \param event		��갴���¼�
	 */

	static bool MouseisMove = FALSE;//�ƶ�
	double dx,dy;//����ƶ��ľ���
	double mouseX, mouseY;//���Ŀǰ��λ��
	static double lastX = 0.0, lastY = 0.0;//����static��¼����λ�ã����ڼ�������ƶ��ľ���

	mouseX = ScaleXInches(x);//pixel -> inches
	mouseY = ScaleYInches(y);

	uiGetMouse(x, y, button, event);
	
	switch (event)
	{
		
		case BUTTON_DOWN://��갴��
			if (button == LEFT_BUTTON) {
				lastX = mouseX;
				lastY = mouseY;
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{
						
						MouseisMove = TRUE;
						temp->isSelected = TRUE;		//ѡ�е�ʱ��ı��ͼ�ε�״̬����ֹ�ƶ���ʱ��Ӱ������ͼ��
						
						strcpy(temp->fix_color, temp->color);//��¼ԭ������ɫ
						strcpy(temp->color, "Green");		//ѡ�е�ʱ��ı���ɫ
						if (Is_Hint) {
							DrawSubmap(&mapShape->graphics[temp->index]);
						}
						break;
					}
					temp = temp->next;
				}
			}

			/* Part 1: ����ͼ�Σ�����debug�� */
			//if (button == MIDDLE_BUTTON && mouseY >= 0 && mouseY <= 8) {
			//	inventShape(0, 0, "Red", ScaleXInches(x), ScaleYInches(y), 1, 1, rand() % 8, rand() % 10);//�������һ��������
			//}
			
			/* Part2: ��תͼ�� */
			if ((button == RIGHT_BUTTON || button == LEFT_BUTTON)
				&& mouseY >= 0 && mouseY <= 9) {
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{
						if (button == RIGHT_BUTTON) //�Ҽ�˳ʱ��
							temp->angle = (temp->angle + 1) % 8;
						//if(button == LEFT_BUTTON) //�����ʱ��
						//	temp->angle = (temp->angle + 7) % 8;
						break;
					}
					temp = temp->next;
				}
			}
			display();
			break;
		
		case BUTTON_UP://����ɿ�,ֹͣ�ƶ�
			MouseisMove = FALSE;
			Shape* temp = head;
			while (temp)
			{
				if (temp->isSelected == TRUE)
				{
					temp->isSelected = FALSE;//�ɿ�����ʱ��ı��ͼ�ε�״̬��������е�״̬���ָ�ԭ��
					strcpy(temp->color,temp->fix_color);//��¼ԭ������ɫ
					SnapToLine(temp, THRESHOLD);
					SnaptoPoint(temp, THRESHOLD);
					judge_complishment();
					break;
				}
				temp = temp->next;
			}
			display();
			break;
		
		case MOUSEMOVE://����ƶ�,�ƶ�ͼ��
			if (MouseisMove) {
				dx = mouseX - lastX;
				dy = mouseY - lastY;//��������ƶ��ľ���
				Shape* temp = head;
				while (temp)
				{
					if (isInShape(temp, mouseX, mouseY) && temp->isSelected == TRUE && !game_status)//ѡ�е�ʱ������ƶ�
					{
						temp->pX += dx;
						temp->pY += dy;
						break;
					}
					temp = temp->next;
				}
				lastX = mouseX;
				lastY = mouseY;//��������λ��
			}
			display();
			break;
	}
	//�����½���
}



/*���ߵ�����*/
int isequal(double a, double b) {
	/**
	 * \brief �ж������������Ƿ����
	 * \param a ������1
	 * \param b	������2
	 * \relates ERROR ��ȷ�� ����Ϊ0.0001
	 */
	if (fabs(a - b) < ERROR)
		return 1;
	else
		return 0;
}
 void SnapToLine(Shape* shape, double threshold) {
	/**
	 * \brief: ��ͼ���Զ��������ڽ��������ϣ�������ͼ��������ͼ�ε�������
	 * \param shape: Ҫ�ƶ���ͼ��
	 * \param threshold: �����������ֵ
	 * \param mapShape: ��ǰ��ͼ��ͼ��ָ�� Shape*����
	 */
	
	//FILE *ErrorFile = fopen("./file/Errorsnap.txt", "w+");
	for (int j = 0; j <= shape->vertexNum - 1; j++) {
		
		line* shapeLine = &(shape->edge[j]);
		//fprintf(ErrorFile, "##\n\n %d\n", j);
		//fprintf(ErrorFile, "%lf %lf\n",shapeLine->start.x, shapeLine->start.y);
		//fprintf(ErrorFile, "%lf %lf\n", shapeLine->end.x, shapeLine->end.y);
		for (int i = 0; i <= mapShape->vertexNum - 1; i++) {//������������
			line* mapLine = &(mapShape->edge[i]);
			// �ж������Ƿ�ƽ��
			if (IsParallel(mapLine, shapeLine)) {
				// ��������ƽ����֮��ľ���
				double distance = DistanceBetweenLines(mapLine, shapeLine);
				// �������С����ֵ����ͼ���ƶ���ƽ�����غ�
				if (distance < threshold) {
					MoveToParallelLines(mapLine, shapeLine, distance, shape);

					/* ����debug 
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
			if (t->isSelected == FALSE)//û�б�ѡ��
			{
				for (int i = 0; i < t->vertexNum; i++) {
					line* oshapeLine = &(t->edge[i]);// �ж������Ƿ�ƽ��
					if (IsParallel(oshapeLine, shapeLine)) { // ��������ƽ����֮��ľ���
						double distance = DistanceBetweenLines(oshapeLine, shapeLine);// �������С����ֵ����ͼ���ƶ���ƽ�����غ�
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
	 * \brief: �ж��������Ƿ�ƽ��
	 * \param line1: ��һ����
	 * \param line2: �ڶ�����
	 * \return : ���������ƽ�У��򷵻�true�����򷵻�false
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
	  * .\brief �ж������߶���ˮƽ�ʹ�ֱ�������޽��沿��
	  * \param line1	��һ���߶�
	  * \param line2	�ڶ����߶�
	  * \return ��û�н��沿�֣�����ֵΪ0 �н��沿�� ������ʵ��
	  */
	 double dx1 = line1->end.x - line1->start.x;
	 double dy1 = line1->end.y - line1->start.y;
	 double dx2 = line2->end.x - line2->start.x;
	 double dy2 = line2->end.y - line2->start.y;
	 //�����߶���ˮƽ�����ϵ�ͶӰ��Χ
	 double minLine1X = line1->start.x < line1->end.x ? line1->start.x : line1->end.x;
	 double maxLine1X = line1->start.x > line1->end.x ? line1->start.x : line1->end.x;
	 double minLine2X = line2->start.x < line2->end.x ? line2->start.x : line2->end.x;
	 double maxLine2X = line2->start.x > line2->end.x ? line2->start.x : line2->end.x;
	 // �����߶��ڴ�ֱ�����ϵ�ͶӰ��Χ
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
	 * \brief: ��������ƽ����֮��ľ���
	 *
	 * \param line1: ��һ����
	 * \param line2: �ڶ�����
	 * \return : ����ƽ����֮��ľ���
	 */
	 // ������1�ķ�������
	 if (IsParallel(line1, line2) == FALSE) {
		 return EOF;
	}
	double dx1 = line1->end.x - line1->start.x;
	double dy1 = line1->end.y - line1->start.y;

	// ������1�ĵ�λ��������
	double length1 = sqrt(dx1 * dx1 + dy1 * dy1);
	double ux1 = dx1 / length1;
	double uy1 = dy1 / length1;


	// ��������ƽ����֮��ľ���
	double distance = fabs((line2->start.x - line1->start.x) * (-1.0) * uy1 + (line2->start.y - line1->start.y) * ux1);
	return distance;

 }
 void MoveToParallelLines(line* line1, line* line2, double distance, Shape* shape) {//done
	 /**
	  * \brief: ��֪����ƽ����֮��ľ��룬��ͼ���ƶ���ƽ�����غ�
	  *
	  * \param line1: ��һ��ƽ����
	  * \param line2: �ڶ���ƽ���� shapeline
	  * \param distance: ����ƽ����֮��ľ���
	  * \param shape: Ҫ�ƶ���ͼ��
	  */
	 //*line1->lineColor = "Red";
	 //*line2->lineColor = "Red";
	 double dx2 = line2->end.x - line2->start.x;
	 double dy2 = line2->end.y - line2->start.y;

	 double length2 = sqrt(dx2 * dx2 + dy2 * dy2);
	 double ux2 = dx2 / length2;
	 double uy2 = dy2 / length2;

	 double dx = distance * uy2;  // ƽ�ƾ������line2�ĵ�λ���������Ĵ�ֱ����
	 double dy = -distance * ux2; // ƽ�ƾ������line2�ĵ�λ���������Ĵ�ֱ�����ĸ�ֵ

	 double dx1 = line1->start.x - line2->start.x;
	 double dy1 = line1->start.y - line2->start.y;
	 if(dx*dx1 + dy*dy1 < 0) { // ���ƽ�ƾ���ķ�����line1�ķ����෴����ȡ��ֵ
		 dx = -dx;
		 dy = -dy;
	 }
	 // ����ͼ��ƽ��dx��dy�ľ���
	 shape->pX += dx;
	 shape->pY += dy;

	 display();
 }

/*�Ե������*/
 void SnaptoPoint(Shape* shape, double threshold) {
	 /**
	 * \brief: ��ͼ���Զ��������ڽ��ĵ���
	 *
	 * \param shape: Ҫ�ƶ���ͼ��
	 * \param threshold: �����������ֵ
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
			 if (t->isSelected == FALSE)//û�б�ѡ��
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
	  * \brief: ����������֮��ľ���
	  *
	  * \param shapeNode: ��һ����
	  * \param mapNode: �ڶ�����
	  * \return : ������֮��ľ���
	  */
	 double dx = shapeNode->x - mapNode->x;
	 double dy = shapeNode->y - mapNode->y;
	 double distance = sqrt(dx * dx + dy * dy);
	 return distance;
 }
 void MoveToNearestPoint(node* shapeNode, node* mapNode, Shape* shape) {
	/**
	  * \brief: ��ͼ���ƶ�������ĵ�
	  *
	  * \param shapeNode: ͼ�εĵ�
	  * \param mapNode: ��ͼ�ĵ�
	  * \param shape: Ҫ�ƶ���ͼ��
	  */
	 double dx = mapNode->x - shapeNode->x;
	 double dy = mapNode->y - shapeNode->y;
	 shape->pX += dx;
	 shape->pY += dy;
	 display();
 }
