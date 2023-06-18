/*****************************************************************//**
 * \file   map.c
 * \brief
 *			�������ɰ��problem map
 *			ʹ�ýṹ��洢��ͼ��������꣬���洢��ͼ�ı��
 *			��shape�ṹ�幹����ͼ����״
 *			��¼ÿһ������������ÿһ����
 * \author
 * \date   May 2023
 *********************************************************************/
#include "map.h"
#include "../Header.h"

current_map = 0;	//��ǰ��ͼ���
mymap map[100];		//��ͼ����

Shape* Map_head , * Map_tail ;
Shape* mapShape ;//ָ��ǰ��ͼ��ָ��
linkedlistADT submap_line_link_head ; //��Ϊline�����ͷ���
linkedlistADT submap_line_link_tail ; //��Ϊline�����β���


Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: ���ɵ�ͼ,��¼��ͼ�ı�ţ��������꣬�ߵ�����
	 * 
	 * \param MapNumber: ��ͼ�ı��
	 * \return : ��shape�ṹ�巵�ص�ͼ����״
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));
	double x_[19] = { 4.3,6.5,6.15,4.9,5.5,4.5,6.5};
	double y_[19] = { 4,4,2.9,4,4.2,4,3};

	//��ʼ����ͼ������
	t->vertexNum = map[MapNumber].vertexNum;
	
	t->pX = map[MapNumber].px;
	t->pY = map[MapNumber].py;

	t->angle = 1;
	strcpy(t->color, "#232946");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 2;
	t->shape = 3;//��ͼ
	t->map_number = MapNumber;
	t->next = t->last = NULL;
	for (int i = 1; i <= 7; i++) {
		t->graphics[i].isvisible = 0;
	}

	//�Ӵ洢�ĵ�ͼ�����ж�ȡ�������꣬������ߵ�����
	for(int i = 0;i <= t->vertexNum-1;i++){				
		t->vertex[i].x = map[MapNumber].vertex[i][0]+t->pX;//!!!!������Ҫ�ѵ�ͼ���������ת��Ϊ�������꣬����������������
		t->vertex[i].y = map[MapNumber].vertex[i][1]+t->pY;
		
	}
	for(int i = 0;i <= t->vertexNum-2;i++){
		t->edge[i].start = t->vertex[i];
		t->edge[i].end = t->vertex[i+1];
	}
	t->edge[t->vertexNum-1].start = t->vertex[t->vertexNum-1];
	t->edge[t->vertexNum-1].end = t->vertex[0];

	//�洢�����ͼ��������
	if (!Map_head) 
		Map_head = Map_tail = t;
	else {
		Map_tail->next = t;
		t->last = Map_tail;
		Map_tail = t;
	}
	return t;

}
void InitMap() {
	for (int i = 0; i < MapNumber_MAX; i++) {
		CreateMap(i);
	}
}

void DrawMap(int MapNumber) {
	/**
	 * \brief: ������ͼ
	 * \param MapNumber: ��ͼ�ı��
	 */
	Shape* temp = Map_head;
	while (temp) {
		if (temp->map_number == MapNumber) { 
			mapShape = temp;
			//StartFilledRegion(1);
			int pensize = GetPenSize();
			string pencolor = GetPenColor();
			SetPenColor(temp->color);
			SetPenSize(temp->Pensize);
			MovePen(temp->pX, temp->pY);
			for (int i = 0; i <= temp->vertexNum-1; i++) {
				DrawLine(temp->edge[i].end.x - temp->edge[i].start.x, temp->edge[i].end.y - temp->edge[i].start.y);
			}
			//EndFilledRegion();
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor
			break;
		}
		temp = temp->next;
	}
}

void DrawSubmap(int MapNumber) {
	/**
	 * \brief ������ʾͼ��
	 * \relates Is_Hint = 1 ������ʾģʽ�� Is_Hint = 0 �ر���ʾģʽ��mouseevent.c�иı�Is_Hint��
	 *
	 *
	 * \param MapNumber
	 */
	//todo��submap�����ݽṹ
	if (Is_Hint == 0) return;

	Shape* ttemp = Map_head;
	while (ttemp) {
		if (ttemp->map_number == MapNumber) {
			mapShape = ttemp;

			int pensize = GetPenSize();
			string pencolor = GetPenColor();

			SetPenColor("Red");
			SetPenSize(3);
			//StartFilledRegion(1);
			for (int i = 1; i <= 7; i++) {
				if (mapShape->graphics[i].isvisible == 0) continue;
				sub_tangram* temp = &mapShape->graphics[i];
				int vertexcount = 3;
				if (i > 5) vertexcount = 4;
				MovePen(temp->vertex[0].x, temp->vertex[0].y);
				for (int i = 0; i < vertexcount - 1; i++) {
					//fprintf(fp, "%lf %lf\n", temp->vertex[i].x, temp->vertex[i].y);
					DrawLine(temp->vertex[i + 1].x - temp->vertex[i].x, temp->vertex[i + 1].y - temp->vertex[i].y);
				}
				DrawLine(temp->vertex[0].x - temp->vertex[vertexcount - 1].x, temp->vertex[0].y - temp->vertex[vertexcount - 1].y);
			}
			//EndFilledRegion();
			SetPenSize(pensize);	//back to system pensize
			SetPenColor(pencolor);	//back to system pencolor

			//fclose(fp);
		}
		ttemp = ttemp->next;
	}

}

void DIY_map() {
	/**
	 * \brief �Զ����ͼ
	 */
	create_submap_line_link();//done
	create_submap_line();
	create_submap_vertex();

	Save_mapCreate_File();				//�����ͼ
	save_subMap(MapNumber_MAX - 1);		//�����ӵ�ͼ//����ͼ�����ΪMapNumber_MAX-1,��Ϊ��Ŵ�0��ʼ����
	Map_head = NULL, Map_tail = NULL;
	GenerateMap();
	InitMap();
	Generate_subMap();
	game_status = 7;
}
void create_submap_line_link()
{
	/**
	 * \brief:��������tangram�ı��γɵ�����.
	 *
	 */
	submap_line_link_head = NewLinkedList();  //��������ͷָ�룬��Ϊnull��ͷָ���в�����κ�����
	submap_line_link_tail = submap_line_link_head->next;
	Shape* temp = head;
	while (temp)
	{
		int linenum = temp->vertexNum;
		for (int i = 0; i < linenum; i++)
		{
			InsertNode(submap_line_link_head, NULL, &(temp->edge[i]));
		}
		temp = temp->next;
	}
	return;
}
void create_submap_line(void)
{
	/**
	 * \brief:����is_superposition��������map���еı�
	 *
	 */
	linkedlistADT temp = submap_line_link_head->next;
	linkedlistADT next_temp = temp->next;  //��Ҫ��¼��һ����㣬����temp���node��ɾȥ
	//����ı����������ڲ�ѭ��

	while (temp)
	{
		next_temp = temp->next;
		linkedlistADT temp_in = temp->next;    //��¼�ڲ�Ƕ�׵�ѭ��
		
		while (temp_in)
		{
			if (Is_superposition(temp, temp_in))
			{
				add_line(temp, temp_in);//ɾ��ǰ�������غϵ��������
				//if (next_temp == temp_in)      //todo:��ֱ�ӱȽ���?
				//{
				//	next_temp = temp_in->next;
				//}
				
				/*DeleteNode(submap_line_link_head, temp->dataptr, (*Is_same_line));
				DeleteNode(submap_line_link_head, temp_in->dataptr, (*Is_same_line));*/
				break;
			}
			temp_in = temp_in->next;
		}
		temp = next_temp;
		
	}

	/*FILE* fp;

	if ((fp = fopen("./file/error.txt", "a+")) != NULL) {
		linkedlistADT temp_adt = submap_line_link_head->next;
		while (temp_adt)
		{

			fprintf(fp, "sx = %lf sy =%lf ", ((line*)(temp_adt->dataptr))->start.x, ((line*)(temp_adt->dataptr))->start.y);

			fprintf(fp, "ex = %lf ey =%lf\n", ((line*)(temp_adt->dataptr))->end.x, ((line*)(temp_adt->dataptr))->end.y);

			temp_adt = temp_adt->next;
		}
	fclose(fp);
	}*/
	
	return;
}
void create_submap_vertex(void)
{
	/**
	 * \brief:�����еı�ת��Ϊ���¼��map[MapNumber_MAX]����
	 *
	 */
	 //�ȴ�����ʼ��һ����

	/*FILE* fp;
	if ((fp = fopen("./file/Errorsnap.txt", "w")) == NULL) {

		fclose(fp);
	}*/

	linkedlistADT temp = submap_line_link_head->next;
	linkedlistADT temp_line_next;
	int vertexnum = 0;

	map[MapNumber_MAX].vertex[vertexnum][0] = ((line*)(temp->dataptr))->start.x;
	map[MapNumber_MAX].vertex[vertexnum][1] = ((line*)(temp->dataptr))->start.y;
	map[MapNumber_MAX].px = map[MapNumber_MAX].vertex[vertexnum][0];
	map[MapNumber_MAX].py = map[MapNumber_MAX].vertex[vertexnum][1];
	vertexnum++;
	map[MapNumber_MAX].vertex[vertexnum][0] = ((line*)(temp->dataptr))->end.x;
	map[MapNumber_MAX].vertex[vertexnum][1] = ((line*)(temp->dataptr))->end.y;
	vertexnum++;
	DeleteNode(submap_line_link_head, temp->dataptr, (*Is_same_line));
	//��ʼѰ��һ���뵱ǰ���й����������һ���ߣ��ҵ�һ���ߴ���vertex�У�������һ���ߴ�vertex��ɾȥ
	while (submap_line_link_head->next)
	{
		
		//�ҵ���һ������ͬ,�����ҵ��ıߴ�������ɾ����ÿ�ζ���end���жϣ������ҵ���һ�ߵ�end��ͬ��Ҫ��start��end����
		temp_line_next = SearchNode(submap_line_link_head, temp->dataptr, (*have_same_point));
		if (temp_line_next == NULL) {
			break;//û�ҵ�������
		}
		else {
			DeleteNode(submap_line_link_head, temp_line_next->dataptr, (*Is_same_line));
		}
		line* line1 = (line*)temp->dataptr;
		line* line2 = (line*)temp_line_next->dataptr;

		if ((dcmp(line1->end.x - line2->start.x) && dcmp(line1->end.y - line2->start.y)))//line2start == line1.end
		{
			map[MapNumber_MAX].vertex[vertexnum][0] = line2->end.x;
			map[MapNumber_MAX].vertex[vertexnum][1] = line2->end.y;
			vertexnum++;
			temp = temp_line_next;

		}
		else 
		{	//�ҵ���һ�ߵ�end��ͬ��Ҫ��start��end����
			if (dcmp(line1->end.x - line2->end.x) && dcmp(line1->end.y - line2->end.y))
			{
				map[MapNumber_MAX].vertex[vertexnum][0] = line2->start.x;
				map[MapNumber_MAX].vertex[vertexnum][1] = line2->start.y;
				vertexnum++;
				line* change_line;
				//fprintf(fp, "beforestart = %lf %lf %lf %lf\n", ((line*)(temp->dataptr))->start.x, ((line*)(temp->dataptr))->start.y, ((line*)(temp->dataptr))->end.x, ((line*)(temp->dataptr))->end.y);
				change_line = (line*)malloc(sizeof(line));
				change_line->start.x = ((line*)(temp_line_next->dataptr))->end.x;
				change_line->start.y = ((line*)(temp_line_next->dataptr))->end.y;
				change_line->end.x = ((line*)(temp_line_next->dataptr))->start.x;
				change_line->end.y = ((line*)(temp_line_next->dataptr))->start.y;
				temp->dataptr = change_line;
				
				//fprintf(fp, "after start = %lf %lf %lf %lf\n", ((line*)(temp->dataptr))->start.x, ((line*)(temp->dataptr))->start.y, ((line*)(temp->dataptr))->end.x, ((line*)(temp->dataptr))->end.y);
				
			}
		}
	}
	map[MapNumber_MAX].vertexNum = vertexnum-1;
	MapNumber_MAX++;
	
	/*for (int i = 0; i < map[MapNumber_MAX].vertexNum; i++) {
		fprintf(fp, "%lf %lf \n ",map[MapNumber_MAX].vertex[i][0], map[MapNumber_MAX].vertex[i][1]);
	}
	fclose(fp);*/
	
	return;
}



