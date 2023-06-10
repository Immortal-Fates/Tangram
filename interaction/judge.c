 /*****************************************************************//**
  * \file   judge.c
  * \brief  七巧板问题的判定函数，判断玩家是否完成拼图
  *			主要思路：利用所有七巧板顶点全在map内，全在tangram外
  * \author
  * \date   May 2023
  *********************************************************************/
#include "../Header.h"
#include "judge.h"

bool IsParallel(line* line1, line* line2);				//from mouseevent.c
double DistanceBetweenLines(line* line1, line* line2);	//from mouseevent.c

//todo:判断是否完成拼图(还没debug)
void judge_complishment()
{
    /**
     * \brief判断是否完成拼图,判断所有图形顶点在map内，判断所有顶点都不在其他的图形内
     */
    Shape* current_Map = mapShape;
    Shape* temp = head;

    while (temp)
    {
        int vertexNum = temp->vertexNum;//遍历每一个顶点
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
     * \brief.判断顶点是否全都不在tangram内，全不在则返回TRUE，有一个在则返回FALSE，边界不算在七巧板内，奇数在里面，偶数在外面
     * \debug:顶点在其他七巧板的边上不算在tangram内，函数有问题，一条线上
     * \param point
     * \return
     */
    Shape* temp = head;
    while (temp)
    {
        int intersection = 0;
        int vertexNum = temp->vertexNum;
        int lineNum = temp->vertexNum;//边数=顶点数
        int count = 0;
        for (int i = 0; i < lineNum; i++)//边记录start和end  
        {
            node p1 = temp->edge[i].start;
            node p2 = temp->edge[i].end;
            if ((p1.x == point.x && p1.y == point.y) || (p2.x == point.x && p2.y == point.y) || (point.y == p1.y && point.y == p2.y))  //与顶点重合不算在tangram内，判断下一个tangram;解决一点与一条边水平
            {
                intersection = 0;
                break;
            }
            //和边(or边的延长线)重合
            if (((point.y <= p2.y && point.y >= p1.y) || (point.y <= p1.y && point.y >= p2.y)) && ((point.x <= p2.x && point.x >= p1.x) || (point.x <= p1.x && point.x >= p2.x)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//点在边上
            {
                //进入下一条边的判断
                intersection = 0;
                break;
            }
            if (point.y == p1.y)
            {
                count++;
            }
            if (point.y <= p2.y)
            {//p2在射线之上  
                if (point.y >= p1.y)      //重合intersection不加
                {//p1正好在射线下方,往右边发出射线  
                    if ((point.y - p1.y) * (p2.x - p1.x) > (point.x - p1.x) * (p2.y - p1.y))//斜率判断,在P1和P2之间且在P1P2右侧,在与边有交点的情况下且y相等再+1（满足奇数）；解决一点与两点水平
                    {
                        intersection++;
                        if (point.y == p1.y)  //只与p1进行判断，保证仅+1
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
                    //p2正好在射线下方，p1在射线上  
                    if ((point.y - p2.y) * (p1.x - p2.x) > (point.x - p2.x) * (p1.y - p2.y))//斜率判断,在P1和P2之间且在P1P2右侧  
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
        if (intersection % 2 == 1)  //为奇数，在七巧板内
        {
            if (count != 1)   //解决一点与一点水平
            {
                return FALSE;
            }
        }
        temp = temp->next;
    }
    return TRUE;      //全部通过，返回TRUE
}
//射线法,
bool judge_point_in_map(node point)
{
    /**
     * \brief 判断顶点在map内，在则返回TRUE，不在则返回FALSE，边界算在map内，奇数在里面，偶数在外面
     * \debug:double类型让斜率计算变得复杂，判断有问题，点在边上也判断不在（边上的不是顶点的点判断很有问题）finish;点在边的延长线上
     * \param point
     * \return
     */

    Shape* temp = mapShape;
    int intersection = 0;
    int vertexNum = temp->vertexNum;
    int lineNum = temp->vertexNum;//边数=顶点数
    for (int i = 0; i < lineNum; i++)//边记录start和end  
    {
        node p1 = temp->edge[i].start;
        node p2 = temp->edge[i].end;
        int count = 0;

        if ((point.x == p1.x && point.y == p1.y) || (point.x == p2.x && point.y == p2.y)) //点与点重合
        {
            return TRUE;//算在多边形内
        }

        //点在边上
        if (((point.y <= p2.y && point.y >= p1.y) || (point.y <= p1.y && point.y >= p2.y)) && ((point.x <= p2.x && point.x >= p1.x) || (point.x <= p1.x && point.x >= p2.x)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//点在边上
        {
            return TRUE;
        }
        //点与边延长线上
        if (point.y == p1.y && point.y == p2.y)
        {
            //进入下一条边的判断
            continue;
        }
        if (point.y <= p2.y)
        {//p2在射线之上  
            if (point.y >= p1.y)      //重合intersection不加
            {//p1正好在射线下方,往右边发出射线  
                if ((point.y - p1.y) * (p2.x - p1.x) > (point.x - p1.x) * (p2.y - p1.y))//斜率判断,在P1和P2之间且在P1P2右侧,在与边有交点的情况下且y相等再+1（满足奇数）；解决一点与两点水平
                {
                    intersection++;
                    if (point.y == p1.y)  //只与p1进行判断，保证仅+1
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
                //p2正好在射线下方，p1在射线上  
                if ((point.y - p2.y) * (p1.x - p2.x) > (point.x - p2.x) * (p1.y - p2.y))//斜率判断,在P1和P2之间且在P1P2右侧  
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
    if (intersection % 2 == 1)  //为奇数，在map内
    {
        return TRUE;
    }
    else {
        return FALSE;      //为偶数，在map外
    }
}



void finish_animation() {

    //    if (game_win == TRUE)
    //    {
            //让所有tangram颜色改变
            //todo:动画显示需要延时？
    color_change_all("Green");

    color_change_all("Blue");

    color_change_all("White");

    //显示win!
    MovePen(1, 1);
    DrawTextString("Win!");
    //    }
        //game_status = 1;  //重置game_status
    return;
}
void color_change_all(string color)     //让所有tangram颜色改变
{
    Shape* temp = head;
    while (temp)
    {
        strcpy(temp->color, color);		//选中的时候改变颜色
        temp = temp->next;
    }
    display();
}

////todo:判断是否完成拼图
//MessageBox();
// bool Game_win(void)
//{
//	/**
//	 * \brief 判断玩家是否完成拼图
//	 * \return 1表示完成拼图，0表示未完成拼图
//	 */
//    //注意： 使用指针数组tangramshape[7]来存储七巧板的指针
//    
//	//判断游戏时间是否小于等于0
//	if(current_time < 0)
//		return FALSE;
//
//    //循环计算各个七巧板交错面积
//    for (int i = 0; i < 7; i++) {
//        for (int j = 0; j < 7; j++) {
//            if(i !=j && CalculateArea(tangramshape[i],tangramshape[j]) > 0)
//				return FALSE;
//        }
//    }
//    //计算七巧板和地图的交错面积
//    double maparea = CalculatePolygonArea(mapShape);//地图面积
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
//     * .\brief 计算两个多边形的交错面积
//     * \param shape1    多边形1
//     * \param shape2    多边形2
//     * \return 计算出的交错面积
//     */
//    int vertexCount1 = shape1->vertexNum;
//    int vertexCount2 = shape2->vertexNum;
//    node* vertices1 = shape1->vertex;
//    node* vertices2 = shape2->vertex;
//
//    double intersectionArea = 0.0;
//
//    //todo: 完成计算两个多边形的交错面积的代码
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
////    // 判断两条直线是否平行
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
////    // 判断交点是否在两条线段上
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
//     * .\brief 使用Green公式计算多边形面积,已经验证过正确性
//     * \param 需要计算的多边形
//     * \return 得到的面积
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
//     * .\brief 游戏过程中的提示函数
//     */
//    //todo : 提示函数，还没想好怎么写
//}
