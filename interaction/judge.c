/*****************************************************************//**
 * \file   judge.c
 * \brief  七巧板问题的判定函数，判断玩家是否完成拼图
 *			主要思路：
 *              首先，判断游戏时间是否小于等于0，如果是，则返回0，表示游戏失败。如果游戏时间大于0，进入下一步的判断。
 *              循环计算各个七巧板交错面积，如果有交错面积，则返回0，表示游戏失败。
 *              计算七巧板和地图的交错面积，如果交错面积之和等于地图面积，则返回1，表示游戏胜利；否则返回0，表示游戏失败。
 * \author 
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "judge.h"


//todo:判断是否完成拼图
MessageBox();
 bool Game_win(void)
{
	/**
	 * \brief 判断玩家是否完成拼图
	 * \return 1表示完成拼图，0表示未完成拼图
	 */
    //注意： 使用指针数组tangramshape[7]来存储七巧板的指针
    
	//判断游戏时间是否小于等于0
	if(current_time < 0)
		return FALSE;

    //循环计算各个七巧板交错面积
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if(i !=j && CalculateArea(tangramshape[i],tangramshape[j]) > 0)
				return FALSE;
        }
    }
    //计算七巧板和地图的交错面积
    double maparea = CalculatePolygonArea(mapShape);//地图面积
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
     * .\brief 计算两个多边形的交错面积
     * \param shape1    多边形1
     * \param shape2    多边形2
     * \return 计算出的交错面积
     */
    int vertexCount1 = shape1->vertexNum;
    int vertexCount2 = shape2->vertexNum;
    node* vertices1 = shape1->vertex;
    node* vertices2 = shape2->vertex;

    double intersectionArea = 0.0;

    //todo: 完成计算两个多边形的交错面积的代码
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
//    // 判断两条直线是否平行
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
//    // 判断交点是否在两条线段上
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
     * .\brief 使用Green公式计算多边形面积,已经验证过正确性
     * \param 需要计算的多边形
     * \return 得到的面积
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
     * .\brief 游戏过程中的提示函数
     */
    //todo : 提示函数，还没想好怎么写
}
