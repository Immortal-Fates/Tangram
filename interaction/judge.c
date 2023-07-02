 /*****************************************************************//**
  * \file   judge.c
  * \brief  ���ɰ�������ж��������ж�����Ƿ����ƴͼ
  *			��Ҫ˼·�������������ɰ嶥��ȫ��map�ڣ�ȫ��tangram��
  * \author
  * \date   May 2023
  **********************************************************5**********/
#include "../Header.h"
#include "judge.h"
double eps = 1e-4;
bool IsParallel(line* line1, line* line2);				//from mouseevent.c
double DistanceBetweenLines(line* line1, line* line2);	//from mouseevent.c


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

    //save_subMap(current_map);
    game_status= -2;
    player[current_player].time[current_map] = TIME_LEFT - current_time;
    mciSendString("open ./file/game_win.mp3 alias game_win", NULL, 0, NULL);
    mciSendString("play game_win", NULL, 0, NULL);     //���ųɹ�������

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
        // score = 3;
        for (int i = 0; i < lineNum; i++)//�߼�¼start��end  
        {
            node p1 = temp->edge[i].start;
            node p2 = temp->edge[i].end;

            if ((dcmp(point.x - p1.x) && dcmp(point.y - p1.y)) || (dcmp(point.x - p2.x) && dcmp(point.y - p2.y)) || (dcmp(point.y - p1.y) && dcmp(point.y - p2.y)))  //�붥���غϲ�����tangram�ڣ��ж���һ��tangram;���һ����һ����ˮƽ
            {
                intersection = 0;
                break;
            }
            //�ͱ��غ�
            if (((point.y <= p2.y + eps && point.y >= p1.y - eps) || (point.y <= p1.y + eps && point.y >= p2.y - eps)) && ((point.x <= p2.x + eps && point.x >= p1.x - eps) || (point.x <= p1.x + eps && point.x >= p2.x - eps)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//���ڱ���
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
    int count = 0;   //��¼��pointˮƽ�ĵ�ĸ�������������ƽ�У�
    for (int i = 0; i < lineNum; i++)//�߼�¼start��end  
    {
        node p1 = temp->edge[i].start;
        node p2 = temp->edge[i].end;
        node p3;
        node p4;
        //score = ((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y));

        if ((dcmp(point.x - p1.x) && dcmp(point.y - p1.y)) || (dcmp(point.x - p2.x) && dcmp(point.y - p2.y)))   //������غ�
        {
            // score = 4;
            return TRUE;//���ڶ������
        }

        //���ڱ���
        //score = (point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y);
        if (((point.y <= p2.y + eps && point.y >= p1.y - eps) || (point.y <= p1.y + eps && point.y >= p2.y - eps)) && ((point.x <= p2.x + eps && point.x >= p1.x - eps) || (point.x <= p1.x && point.x >= p2.x)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//���ڱ���
        {
            //  score = 3;
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
                if ((point.y - p1.y) * (p2.x - p1.x) > (point.x - p1.x) * (p2.y - p1.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�,������н�����������y�����+1������������(��Ҫ���������)�����һ��������ˮƽ
                {
                    if (point.y == p2.y)  //ֻ��p2�ж�
                    {
                        int k = i;
                        k++;
                        p3 = temp->edge[k % lineNum].start;
                        p4 = temp->edge[k % lineNum].end;
                        while (p3.y == p4.y)   //ˮƽ�ı�ֱ�Ӳ�����
                        {
                            k++;
                            p3 = temp->edge[k % lineNum].start;
                            p4 = temp->edge[k % lineNum].end;
                        }
                        //ֻ��p1,p4��p2������Ż�ʹintersection++;������ͬ�಻��
                        if ((p1.y - p2.y) * (p4.y - p2.y) > 0)
                        {
                            intersection++;
                        }
                    }
                    else {
                        intersection++;  //��������������ж�
                    }

                }
            }
        }
        if (point.y > p2.y)
        {
            if (point.y <= p1.y)
            {
                //p2�����������·���p1��������  
                if ((point.y - p2.y) * (p1.x - p2.x) > (point.x - p2.x) * (p1.y - p2.y))//б���ж�,��P1��P2֮������P1P2�Ҳ�  
                {
                    if (point.y == p2.y)
                    {
                        int k = i;
                        k++;
                        p3 = temp->edge[k % lineNum].start;
                        p4 = temp->edge[k % lineNum].end;
                        while (p3.y == p4.y)   //ˮƽ�ı�ֱ�Ӳ�����
                        {
                            k++;
                            p3 = temp->edge[k % lineNum].start;
                            p4 = temp->edge[k % lineNum].end;
                        }
                        //ֻ��p1,p4��p2������Ż�ʹintersection++;������ͬ�಻��
                        if ((p1.y - p2.y) * (p4.y - p2.y) > 0)
                        {

                            intersection++;
                        }
                    }
                    else {
                        intersection++;  //��������������ж�
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


bool dcmp(double x)
{
    /**
     * \brief//��̬�������ж�����double��eps�����µĴ�С��ϵ.
     *
     * \param x
     * \return
     */
    if (fabs(x) < eps) return TRUE;
    else
        return FALSE;
}

bool Is_superposition(linkedlistADT node1, linkedlistADT node2) {
    line* line1 = (line*)(node1->dataptr);
    line* line2 = (line*)(node2->dataptr);

    if (!IsParallel(line1, line2))   //���߲�ƽ����һ�����غϡ�
    {
        return FALSE;
    }
    if (!(DistanceBetweenLines(line1, line2) <= eps))          //j����������֮��ľ��롶=eps��ƽ��
    {
        return FALSE;
    }
    return TRUE;
}

void add_line(linkedlistADT node1, linkedlistADT node2)
{
    /**
     * \brief:��������.�ж��Ƿ��غϣ�һ���غϲ����غϣ��غϺ��Ƿ�ᴴ���µıߣ��������ڸú����н������µ�node������ɾ��ԭ����node
     * \param:���������е�������㣬��Ϊ�������жϺ�Ҫ����������޸�,�޸���᷵��true
     */
    line* line1 = (line*)(node1->dataptr);
    line* line2 = (line*)(node2->dataptr);
    
   
    //�����������Ѿ����غ���

    //������ֱ�����
    if (dcmp(line1->start.x - line1->end.x) || dcmp(line2->start.x - line2->end.x))      //������ֱ���
    {
        //��4��������
        node point[4] = { line1->start,line1->end,line2->start,line2->end };
        //��С����
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (point[j].y < point[i].y)
                {
                    node temp;
                    temp = point[i];
                    point[i] = point[j];
                    point[j] = temp;
                }
            }
        }
        if (dcmp(point[1].y - point[2].y))              //��������Ҫ�ϲ�
        {
            line* temp;
            temp = (line*)malloc(sizeof(line));

            temp->start.x = point[0].x;
            temp->start.y = point[0].y;

            temp->end.x = point[3].x;
            temp->end.y = point[3].y;

            InsertNode(submap_line_link_head, NULL, temp);
        }
        else {
            if (!dcmp(point[0].y - point[1].y))
            {
                line* temp;
                temp = (line*)malloc(sizeof(line));

                temp->start.x = point[0].x;
                temp->start.y = point[0].y;

                temp->end.x = point[1].x;
                temp->end.y = point[1].y;


                InsertNode(submap_line_link_head, NULL, temp);
            }
            if (!dcmp(point[2].y - point[3].y))
            {
                line* temp;
                temp = (line*)malloc(sizeof(line));

                temp->start.x = point[2].x;
                temp->start.y = point[2].y;

                temp->end.x = point[3].x;
                temp->end.y = point[3].y;

                InsertNode(submap_line_link_head, NULL, temp);
            }
        }

    }
    else {
        //�߲���ֱ�����(����ˮƽ)
        //��4��������
        node point[4] = { line1->start,line1->end,line2->start,line2->end };
        //��С����
        for (int i = 0; i <4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (point[j].x < point[i].x)
                {
                    node temp;
                    temp = point[i];
                    point[i] = point[j];
                    point[j] = temp;
                }
            }
        }

        if (dcmp(point[1].x - point[2].x))
        {
            line* temp;
            temp = (line*)malloc(sizeof(line));

            temp->start.x = point[0].x;
            temp->start.y = point[0].y;

            temp->end.x = point[3].x;
            temp->end.y = point[3].y;
            InsertNode(submap_line_link_head, NULL, temp);
        }
        else
        {
            if (!dcmp(point[0].x - point[1].x))
            {
                line* temp;
                temp = (line*)malloc(sizeof(line));

                temp->start.x = point[0].x;
                temp->start.y = point[0].y;

                temp->end.x = point[1].x;
                temp->end.y = point[1].y;

                InsertNode(submap_line_link_head, NULL, temp);
            }
            if (!dcmp(point[2].x - point[3].x))
            {
                line* temp;
                temp = (line*)malloc(sizeof(line));

                temp->start.x = point[2].x;
                temp->start.y = point[2].y;

                temp->end.x = point[3].x;
                temp->end.y = point[3].y;

                InsertNode(submap_line_link_head, NULL, temp);
            }
        }

    }
    DeleteNode(submap_line_link_head, node1->dataptr, (*Is_same_line));
    DeleteNode(submap_line_link_head, node2->dataptr, (*Is_same_line));
    return;
}
bool Is_same_line(void* obj1, void* obj2)
{
    /**
     * \brief:�ж�����ֱ���Ƿ���ͬһ��ֱ��.
     *
     * \param obj1
     * \param obj2
     * \return
     */
    line* line1 = (line*)obj1;
    line* line2 = (line*)obj2;
    if (dcmp(line1->start.x - line2->start.x) && dcmp(line1->start.y - line2->start.y) && dcmp(line1->end.x - line2->end.x) && dcmp(line1->end.y - line2->end.y))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
bool Is_psame_line(void* obj1, void* obj2)
{
    /**
     * \brief:�ж�����ֱ���Ƿ���ͬһ��ֱ��.
     *
     * \param obj1
     * \param obj2
     * \return
     */
    line* line1 = (line*)obj1;
    line* line2 = (line*)obj2;    //line2��������Ҫ�Ƚϵ�ֵ
    if (dcmp(line1->start.x - line2->start.x) && dcmp(line1->start.y - line2->start.y) && dcmp(line1->end.x - line2->end.x) && dcmp(line1->end.y - line2->end.y))
    {
        return TRUE;
    }
    else if (dcmp(line1->end.x - line2->start.x) && dcmp(line1->end.y - line2->start.y) && dcmp(line1->start.x - line2->end.x) && dcmp(line1->start.y - line2->end.y))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool have_same_point(void* obj1, void* obj2)
{
    /**
     * \brief:�ж�һ���Ƿ���ǰһ���ߵ�end��ͬ��������ͬ����.
     *
     * \param obj1
     * \param obj2
     * \return
     */
    line* line1 = (line*)obj1;
    line* line2 = (line*)obj2;      //ԭ���ı�

    if ((dcmp(line2->end.x - line1->start.x) && dcmp(line2->end.y - line1->start.y)) || 
        (dcmp(line2->end.x - line1->end.x) && dcmp(line2->end.y - line1->end.y)))
    {
        return TRUE;
    }

    return FALSE;

}
bool judge_createmap_complishment()
{
    /**
     * \brief:�ж�DIYmap�Ƿ�ɹ�.������˼·��ÿ��tangram�������ٵ�������tangram�ı��ϣ���û�е�������tangram���ڲ���
     *
     *
     * \return
     */
    Shape* temp = head;

    //map[MapNumber_MAX - 1];
    while (temp)
    {
        int vertexnum = temp->vertexNum;
        int count = 0;
        for (int i = 0; i < vertexnum; i++)
        {
            if (judge_point_in_tangram(temp->vertex[i]) == FALSE)       //��һ����������tangram���ڲ��򷵻�false
            {
                return FALSE;
            }
            if (judge_point_on_line(temp->vertex[i], temp) == TRUE)
            {
                count++;
            }
        }
        if (count == 0)        //û�е�������tangram��������������
        {
            return FALSE;
        }
        temp = temp->next;
    }
    return TRUE;
}
bool judge_point_on_line(node point, Shape* ttemp)
{
    /**
     * \brief:�жϵ��Ƿ���tangram�ı��ϣ����򷵻�true,�����򷵻�false,����ų����Լ����Ƚϣ�
     * .
     *
     * \param point
     * \return
     */
    Shape* temp = head;
    while (temp)
    {
        if (temp == ttemp)        //������Լ����Ƚ�
        {
            temp = temp->next;
            continue;
        }
        int vertexNum = temp->vertexNum;
        int lineNum = temp->vertexNum;//����=������
        for (int i = 0; i < lineNum; i++)//�߼�¼start��end  
        {
            node p1 = temp->edge[i].start;
            node p2 = temp->edge[i].end;

            if ((dcmp(point.x - p1.x) && dcmp(point.y - p1.y)) || (dcmp(point.x - p2.x) && dcmp(point.y - p2.y)) || (dcmp(point.y - p1.y) && dcmp(point.y - p2.y)))  //�붥���غϲ�����tangram�ڣ��ж���һ��tangram;���һ����һ����ˮƽ
            {
                return TRUE;
            }
            //�ͱ��غ�
            if (((point.y <= p2.y + eps && point.y >= p1.y - eps) || (point.y <= p1.y + eps && point.y >= p2.y - eps)) && ((point.x <= p2.x + eps && point.x >= p1.x - eps) || (point.x <= p1.x + eps && point.x >= p2.x - eps)) && ((((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) < 0.1) && (((point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y)) > -0.1)))//���ڱ���
            {
                return TRUE;
            }
        }
        temp = temp->next;
    }
    return FALSE;
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

