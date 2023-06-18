/*****************************************************************//**
 * \file   map.c
 * \brief
 *			生成七巧板的problem map
 *			使用结构体存储地图顶点的坐标，并存储地图的编号
 *			用shape结构体构建地图的形状
 *			记录每一个顶点的坐标和每一条边
 * \author
 * \date   May 2023
 *********************************************************************/
#include "map.h"
#include "../Header.h"

current_map = 0;	//当前地图编号
mymap map[100];		//地图数据

Shape* Map_head , * Map_tail ;
Shape* mapShape ;//指向当前地图的指针
linkedlistADT submap_line_link_head ; //作为line链表的头结点
linkedlistADT submap_line_link_tail ; //作为line链表的尾结点


Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: 生成地图,记录地图的编号，顶点坐标，边的数据
	 * 
	 * \param MapNumber: 地图的编号
	 * \return : 以shape结构体返回地图的形状
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));
	double x_[19] = { 4.3,6.5,6.15,4.9,5.5,4.5,6.5};
	double y_[19] = { 4,4,2.9,4,4.2,4,3};

	//初始化地图的数据
	t->vertexNum = map[MapNumber].vertexNum;
	
	t->pX = map[MapNumber].px;
	t->pY = map[MapNumber].py;

	t->angle = 1;
	strcpy(t->color, "#232946");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 2;
	t->shape = 3;//地图
	t->map_number = MapNumber;
	t->next = t->last = NULL;
	for (int i = 1; i <= 7; i++) {
		t->graphics[i].isvisible = 0;
	}

	//从存储的地图数据中读取顶点坐标，计算出边的数据
	for(int i = 0;i <= t->vertexNum-1;i++){				
		t->vertex[i].x = map[MapNumber].vertex[i][0]+t->pX;//!!!!这里需要把地图的相对坐标转换为绝对坐标，否则会出现吸附错误
		t->vertex[i].y = map[MapNumber].vertex[i][1]+t->pY;
		
	}
	for(int i = 0;i <= t->vertexNum-2;i++){
		t->edge[i].start = t->vertex[i];
		t->edge[i].end = t->vertex[i+1];
	}
	t->edge[t->vertexNum-1].start = t->vertex[t->vertexNum-1];
	t->edge[t->vertexNum-1].end = t->vertex[0];

	//存储进入地图的链表中
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
	 * \brief: 画出地图
	 * \param MapNumber: 地图的编号
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
	 * \brief 画出提示图形
	 * \relates Is_Hint = 1 进入提示模式； Is_Hint = 0 关闭提示模式（mouseevent.c中改变Is_Hint）
	 *
	 *
	 * \param MapNumber
	 */
	//todo：submap的数据结构
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
	 * \brief 自定义地图
	 */
	create_submap_line_link();//done
	create_submap_line();
	create_submap_vertex();

	Save_mapCreate_File();				//保存地图
	save_subMap(MapNumber_MAX - 1);		//保存子地图//将地图编号设为MapNumber_MAX-1,因为编号从0开始计数
	Map_head = NULL, Map_tail = NULL;
	GenerateMap();
	InitMap();
	Generate_subMap();
	game_status = 7;
}
void create_submap_line_link()
{
	/**
	 * \brief:创建所有tangram的边形成的链表.
	 *
	 */
	submap_line_link_head = NewLinkedList();  //创建好了头指针，不为null。头指针中补存放任何数据
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
	 * \brief:利用is_superposition生成最终map具有的边
	 *
	 */
	linkedlistADT temp = submap_line_link_head->next;
	linkedlistADT next_temp = temp->next;  //需要记录下一个结点，避免temp这个node被删去
	//如果改变了则跳出内层循环

	while (temp)
	{
		next_temp = temp->next;
		linkedlistADT temp_in = temp->next;    //记录内层嵌套的循环
		
		while (temp_in)
		{
			if (Is_superposition(temp, temp_in))
			{
				add_line(temp, temp_in);//删除前面两个重合的两个结点
				//if (next_temp == temp_in)      //todo:能直接比较吗?
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
	 * \brief:把所有的边转化为点记录在map[MapNumber_MAX]里面
	 *
	 */
	 //先存入起始的一条边

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
	//开始寻找一条与当前边有公共顶点的任一条边，找到一条边存入vertex中，并将这一条边从vertex中删去
	while (submap_line_link_head->next)
	{
		
		//找到有一个点相同,并将找到的边从链表中删除，每次都用end来判断，所以找到另一边的end相同，要将start和end互换
		temp_line_next = SearchNode(submap_line_link_head, temp->dataptr, (*have_same_point));
		if (temp_line_next == NULL) {
			break;//没找到则跳出
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
		{	//找到另一边的end相同，要将start和end互换
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



