 /*****************************************************************//**
  * \file   judge.c
  * \brief  ���ɰ�������ж��������ж�����Ƿ����ƴͼ
  *			��Ҫ˼·�������������ɰ嶥��ȫ��map�ڣ�ȫ��tangram��
  * \author
  * \date   May 2023
  *********************************************************************/
#include "../Header.h"
#include "judge.h"

bool IsParallel(line* line1, line* line2);				//from mouseevent.c
double DistanceBetweenLines(line* line1, line* line2);	//from mouseevent.c

//todo:�ж��Ƿ����ƴͼ(��ûdebug)
void judge_complishment()
{
    /**
     * \brief�ж��Ƿ����ƴͼ,�ж�����ͼ�ζ�����map�ڣ��ж����ж��㶼����������ͼ����
     */
    Shape* current_Map = mapShape;
    Shape* temp = head;

    while (temp)
    {
        int vertexNum = temp->vertexNum;//����ÿһ������
        for (int i = 0; i < vertexNum; i++)
        {
            if (judge_point_in_tangram(temp->vertex[i]) == FALSE)
            {
                return;
            }
            if (judge_point_in_map(temp->vertex[i]) == FALSE)
            {
                return;
            }
        }
        temp = temp->next;
    }
    game_status= -2;
    return;
}


bool judge_point_in_tangram(node point)
{
    /**
     * \brief.�ж϶����Ƿ�ȫ������tangram�ڣ�ȫ�����򷵻�TRUE����һ�����򷵻�FALSE���߽粻�������ɰ��ڣ����������棬ż��������
     * \debug:�������������ɰ�ı��ϲ�����tangram�ڣ����������⣬һ������
     * \param point
     * \return
     */
    Shape* temp = head;
    while (temp)
    {
        int intersection = 0;
        int vertexNum = temp->vertexNum;
        int lineNum = temp->vertexNum;//����=������
        int count = 0;
        for (int i = 0; i < lineNum; i++)//�߼�¼start��end  
        {
            node p1 = temp->edge[i].start;
            node p2 = temp->edge[i].end;
            if ((p1.x == point.x && p1.y == point.y) || (p2.x == point.x && p2.y == point.y) || (point.y == p1.y && point.y == p2.y))  //�붥���غϲ�����tangram�ڣ��ж���һ��tangram;���һ����һ����ˮƽ
            {
                intersection = 0;
                break;
            }
            //�ͱ�(or�ߵ��ӳ���)�غ�
            if (((point.y <= p2.y && point.y >= p1.y) || (point.y <= p1.y && point.y >= p2.y)) && ((point.x <= p2.x && point.x >= p1.x) || (point.x <= p1.x && point.x >= p2.x)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//���ڱ���
            {
                //������һ���ߵ��ж�
                intersection = 0;
                break;
            }
            if (point.y == p1.y)
            {
                count++;
            }
            if (point.y <= p2.y)
            {//p2������֮��  
                if (point.y >= p1.y)      //�غ�intersection����
                {//p1�����������·�,���ұ߷�������  
                    if ((point.y - p1.y) * (p2.x - p1.x) > (point.x - p1.x) * (p2.y - p1.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�,������н�����������y�����+1�����������������һ��������ˮƽ
                    {
                        intersection++;
                        if (point.y == p1.y)  //ֻ��p1�����жϣ���֤��+1
                        {
                            intersection++;

                        }
                    }
                }
            }
            if (point.y >= p2.y)
            {
                if (point.y <= p1.y)
                {
                    //p2�����������·���p1��������  
                    if ((point.y - p2.y) * (p1.x - p2.x) > (point.x - p2.x) * (p1.y - p2.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�  
                    {
                        intersection++;
                        if (point.y == p1.y)
                        {
                            intersection++;
                        }
                    }
                }
            }
        }
        if (intersection % 2 == 1)  //Ϊ�����������ɰ���
        {
            if (count != 1)   //���һ����һ��ˮƽ
            {
                return FALSE;
            }
        }
        temp = temp->next;
    }
    return TRUE;      //ȫ��ͨ��������TRUE
}
//���߷�,
bool judge_point_in_map(node point)
{
    /**
     * \brief �ж϶�����map�ڣ����򷵻�TRUE�������򷵻�FALSE���߽�����map�ڣ����������棬ż��������
     * \debug:double������б�ʼ����ø��ӣ��ж������⣬���ڱ���Ҳ�жϲ��ڣ����ϵĲ��Ƕ���ĵ��жϺ������⣩finish;���ڱߵ��ӳ�����
     * \param point
     * \return
     */

    Shape* temp = mapShape;
    int intersection = 0;
    int vertexNum = temp->vertexNum;
    int lineNum = temp->vertexNum;//����=������
    for (int i = 0; i < lineNum; i++)//�߼�¼start��end  
    {
        node p1 = temp->edge[i].start;
        node p2 = temp->edge[i].end;
        int count = 0;

        if ((point.x == p1.x && point.y == p1.y) || (point.x == p2.x && point.y == p2.y)) //������غ�
        {
            return TRUE;//���ڶ������
        }

        //���ڱ���
        if (((point.y <= p2.y && point.y >= p1.y) || (point.y <= p1.y && point.y >= p2.y)) && ((point.x <= p2.x && point.x >= p1.x) || (point.x <= p1.x && point.x >= p2.x)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//���ڱ���
        {
            return TRUE;
        }
        //������ӳ�����
        if (point.y == p1.y && point.y == p2.y)
        {
            //������һ���ߵ��ж�
            continue;
        }
        if (point.y <= p2.y)
        {//p2������֮��  
            if (point.y >= p1.y)      //�غ�intersection����
            {//p1�����������·�,���ұ߷�������  
                if ((point.y - p1.y) * (p2.x - p1.x) > (point.x - p1.x) * (p2.y - p1.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�,������н�����������y�����+1�����������������һ��������ˮƽ
                {
                    intersection++;
                    if (point.y == p1.y)  //ֻ��p1�����жϣ���֤��+1
                    {
                        intersection++;

                    }
                }
            }
        }
        if (point.y >= p2.y)
        {
            if (point.y <= p1.y)
            {
                //p2�����������·���p1��������  
                if ((point.y - p2.y) * (p1.x - p2.x) > (point.x - p2.x) * (p1.y - p2.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�  
                {
                    intersection++;
                    if (point.y == p1.y)
                    {
                        intersection++;
                    }
                }
            }
        }
    }
    if (intersection % 2 == 1)  //Ϊ��������map��
    {
        return TRUE;
    }
    else {
        return FALSE;      //Ϊż������map��
    }
}



void finish_animation() {

    //    if (game_win == TRUE)
    //    {
            //������tangram��ɫ�ı�
            //todo:������ʾ��Ҫ��ʱ��
    color_change_all("Green");

    color_change_all("Blue");

    color_change_all("White");

    //��ʾwin!
    MovePen(1, 1);
    DrawTextString("Win!");
    //    }
        //game_status = 1;  //����game_status
    return;
}
void color_change_all(string color)     //������tangram��ɫ�ı�
{
    Shape* temp = head;
    while (temp)
    {
        strcpy(temp->color, color);		//ѡ�е�ʱ��ı���ɫ
        temp = temp->next;
    }
    display();
}

////todo:�ж��Ƿ����ƴͼ
//MessageBox();
// bool Game_win(void)
//{
//	/**
//	 * \brief �ж�����Ƿ����ƴͼ
//	 * \return 1��ʾ���ƴͼ��0��ʾδ���ƴͼ
//	 */
//    //ע�⣺ ʹ��ָ������tangramshape[7]���洢���ɰ��ָ��
//    
//	//�ж���Ϸʱ���Ƿ�С�ڵ���0
//	if(current_time < 0)
//		return FALSE;
//
//    //ѭ������������ɰ彻�����
//    for (int i = 0; i < 7; i++) {
//        for (int j = 0; j < 7; j++) {
//            if(i !=j && CalculateArea(tangramshape[i],tangramshape[j]) > 0)
//				return FALSE;
//        }
//    }
//    //�������ɰ�͵�ͼ�Ľ������
//    double maparea = CalculatePolygonArea(mapShape);//��ͼ���
//    double sum = 0.0;
//    for(int i = 0; i < 7; i++)
//	{
//		double area = CalculateArea(mapShape, tangramshape[i]);
//		sum += area;
//	}
//	if(sum == maparea)
//		return TRUE;
//	else
//		return FALSE;
//}
//
//double CalculateArea(Shape* shape1,Shape* shape2) {
//    /**
//     * .\brief ������������εĽ������
//     * \param shape1    �����1
//     * \param shape2    �����2
//     * \return ������Ľ������
//     */
//    int vertexCount1 = shape1->vertexNum;
//    int vertexCount2 = shape2->vertexNum;
//    node* vertices1 = shape1->vertex;
//    node* vertices2 = shape2->vertex;
//
//    double intersectionArea = 0.0;
//
//    //todo: ��ɼ�����������εĽ�������Ĵ���
//    /*for (int i = 0; i < vertexCount1; i++) {
//        const node* p1 = &vertices1[i];
//        const node* p2 = &vertices1[(i + 1) % vertexCount1];
//
//        node tmp[20];
//        int nb = 0;
//
//        for (int j = 0; j < vertexCount2; j++) {
//            const node* q1 = &vertices2[j];
//            const node* q2 = &vertices2[(j + 1) % vertexCount2];
//
//            double cross1 = CrossProduct(p1->x, p1->y, p2->x, p2->y, q1->x, q1->y);
//            double cross2 = CrossProduct(p1->x, p1->y, p2->x, p2->y, q2->x, q2->y);
//
//            if ((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)) {
//                double intersectionX, intersectionY;
//                if (FindLineIntersection(p1->x, p1->y, p2->x, p2->y, q1->x, q1->y, q2->x, q2->y, &intersectionX, &intersectionY)) {
//                    tmp[nb].x = intersectionX;
//                    tmp[nb].y = intersectionY;
//                    nb++;
//                }
//            }
//        }
//
//        if (nb > 0) {
//            tmp[nb].x = p2->x;
//            tmp[nb].y = p2->y;
//            nb++;
//
//            for (int k = 0; k < nb; k++) {
//                vertices1[k] = tmp[k];
//            }
//            vertexCount1 = nb;
//        }
//    }
//
//    if (vertexCount1 <= 2) {
//        return 0.0;
//    }
//
//    double sum = 0.0;
//    for (int i = 0; i < vertexCount1; i++) {
//        const node* p1 = &vertices1[i];
//        const node* p2 = &vertices1[(i + 1) % vertexCount1];
//        sum += (p1->x * p2->y - p2->x * p1->y);
//    }
//
//    intersectionArea = 0.5 * fabs(sum);
//    return intersectionArea;*/
//}
//
//
////double CrossProduct(double x1, double y1, double x2, double y2, double x3, double y3) {
////    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
////}
////
////bool FindLineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double* intersectionX, double* intersectionY) {
////    double denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
////
////    // �ж�����ֱ���Ƿ�ƽ��
////    if (denominator == 0) {
////        return false;
////    }
////
////    double numerator1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
////    double numerator2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
////
////    double t1 = numerator1 / denominator;
////    double t2 = numerator2 / denominator;
////
////    // �жϽ����Ƿ��������߶���
////    if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1) {
////        *intersectionX = x1 + t1 * (x2 - x1);
////        *intersectionY = y1 + t1 * (y2 - y1);
////        return true;
////    }
////
////    return false;
////}
//double CalculatePolygonArea(const Shape* shape) {
//    /**
//     * .\brief ʹ��Green��ʽ�����������,�Ѿ���֤����ȷ��
//     * \param ��Ҫ����Ķ����
//     * \return �õ������
//     */
//    int vertexCount = shape->vertexNum;
//    const node* vertices = shape->vertex;
//
//    double sum = 0.0;
//    for (int i = 0; i < vertexCount; i++) {
//        const node* p1 = &vertices[i];
//        const node* p2 = &vertices[(i + 1) % vertexCount];
//        sum += (p1->x * p2->y - p2->x * p1->y);
//    }
//
//    double area = 0.5 * fabs(sum);
//    return area;
//}
//
//void hint(void){
//    /**
//     * .\brief ��Ϸ�����е���ʾ����
//     */
//    //todo : ��ʾ��������û�����ôд
//}
