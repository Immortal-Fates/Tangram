/*****************************************************************//**
 * \file   judge.c
 * \brief  ���ɰ�������ж��������ж�����Ƿ����ƴͼ
 *			��Ҫ˼·��
 *              ���ȣ��ж���Ϸʱ���Ƿ�С�ڵ���0������ǣ��򷵻�0����ʾ��Ϸʧ�ܡ������Ϸʱ�����0��������һ�����жϡ�
 *              ѭ������������ɰ彻�����������н���������򷵻�0����ʾ��Ϸʧ�ܡ�
 *              �������ɰ�͵�ͼ�Ľ������������������֮�͵��ڵ�ͼ������򷵻�1����ʾ��Ϸʤ�������򷵻�0����ʾ��Ϸʧ�ܡ�
 * \author 
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "judge.h"


//todo:�ж��Ƿ����ƴͼ
MessageBox();
 bool Game_win(void)
{
	/**
	 * \brief �ж�����Ƿ����ƴͼ
	 * \return 1��ʾ���ƴͼ��0��ʾδ���ƴͼ
	 */
    //ע�⣺ ʹ��ָ������tangramshape[7]���洢���ɰ��ָ��
    
	//�ж���Ϸʱ���Ƿ�С�ڵ���0
	if(current_time < 0)
		return FALSE;

    //ѭ������������ɰ彻�����
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if(i !=j && CalculateArea(tangramshape[i],tangramshape[j]) > 0)
				return FALSE;
        }
    }
    //�������ɰ�͵�ͼ�Ľ������
    double maparea = CalculatePolygonArea(mapShape);//��ͼ���
    double sum = 0.0;
    for(int i = 0; i < 7; i++)
	{
		double area = CalculateArea(mapShape, tangramshape[i]);
		sum += area;
	}
	if(sum == maparea)
		return TRUE;
	else
		return FALSE;
}

double CalculateArea(Shape* shape1,Shape* shape2) {
    /**
     * .\brief ������������εĽ������
     * \param shape1    �����1
     * \param shape2    �����2
     * \return ������Ľ������
     */
    int vertexCount1 = shape1->vertexNum;
    int vertexCount2 = shape2->vertexNum;
    node* vertices1 = shape1->vertex;
    node* vertices2 = shape2->vertex;

    double intersectionArea = 0.0;

    //todo: ��ɼ�����������εĽ�������Ĵ���
    /*for (int i = 0; i < vertexCount1; i++) {
        const node* p1 = &vertices1[i];
        const node* p2 = &vertices1[(i + 1) % vertexCount1];

        node tmp[20];
        int nb = 0;

        for (int j = 0; j < vertexCount2; j++) {
            const node* q1 = &vertices2[j];
            const node* q2 = &vertices2[(j + 1) % vertexCount2];

            double cross1 = CrossProduct(p1->x, p1->y, p2->x, p2->y, q1->x, q1->y);
            double cross2 = CrossProduct(p1->x, p1->y, p2->x, p2->y, q2->x, q2->y);

            if ((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)) {
                double intersectionX, intersectionY;
                if (FindLineIntersection(p1->x, p1->y, p2->x, p2->y, q1->x, q1->y, q2->x, q2->y, &intersectionX, &intersectionY)) {
                    tmp[nb].x = intersectionX;
                    tmp[nb].y = intersectionY;
                    nb++;
                }
            }
        }

        if (nb > 0) {
            tmp[nb].x = p2->x;
            tmp[nb].y = p2->y;
            nb++;

            for (int k = 0; k < nb; k++) {
                vertices1[k] = tmp[k];
            }
            vertexCount1 = nb;
        }
    }

    if (vertexCount1 <= 2) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < vertexCount1; i++) {
        const node* p1 = &vertices1[i];
        const node* p2 = &vertices1[(i + 1) % vertexCount1];
        sum += (p1->x * p2->y - p2->x * p1->y);
    }

    intersectionArea = 0.5 * fabs(sum);
    return intersectionArea;*/
}


//double CrossProduct(double x1, double y1, double x2, double y2, double x3, double y3) {
//    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
//}
//
//bool FindLineIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double* intersectionX, double* intersectionY) {
//    double denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
//
//    // �ж�����ֱ���Ƿ�ƽ��
//    if (denominator == 0) {
//        return false;
//    }
//
//    double numerator1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
//    double numerator2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
//
//    double t1 = numerator1 / denominator;
//    double t2 = numerator2 / denominator;
//
//    // �жϽ����Ƿ��������߶���
//    if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1) {
//        *intersectionX = x1 + t1 * (x2 - x1);
//        *intersectionY = y1 + t1 * (y2 - y1);
//        return true;
//    }
//
//    return false;
//}
double CalculatePolygonArea(const Shape* shape) {
    /**
     * .\brief ʹ��Green��ʽ�����������,�Ѿ���֤����ȷ��
     * \param ��Ҫ����Ķ����
     * \return �õ������
     */
    int vertexCount = shape->vertexNum;
    const node* vertices = shape->vertex;

    double sum = 0.0;
    for (int i = 0; i < vertexCount; i++) {
        const node* p1 = &vertices[i];
        const node* p2 = &vertices[(i + 1) % vertexCount];
        sum += (p1->x * p2->y - p2->x * p1->y);
    }

    double area = 0.5 * fabs(sum);
    return area;
}

void hint(void){
    /**
     * .\brief ��Ϸ�����е���ʾ����
     */
    //todo : ��ʾ��������û�����ôд
}
