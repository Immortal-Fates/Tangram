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

Shape* Map_head = NULL, * Map_tail = NULL;
Shape* mapShape = NULL;//指向当前地图的指针


Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: 生成地图,记录地图的编号，顶点坐标，边的数据
	 * 
	 * \param MapNumber: 地图的编号
	 * \return : 以shape结构体返回地图的形状
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));
	double x_[9] = { 4.3,6.5,6.15,4.9,5.5,4.5,6.5,5.5 };
	double y_[9] = { 4,4,2.9,4,4.2,4,3,3 };

	//初始化地图的数据
	t->vertexNum = map[MapNumber].vertexNum;
	t->pX = x_[MapNumber];
	t->pY = y_[MapNumber];

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
	if (Is_Hint == 0) return;

	Shape* ttemp = Map_head;
	while (ttemp) {
		if (ttemp->map_number == MapNumber) {
			mapShape = ttemp;
			//FILE* fp;
			//fp = fopen("./file/
			//
			// .txt", "w");
			//fprintf(fp, "%d\n", mapShape->vertexNum);

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

void DIYMap() {
	/**
	 * \brief 自定义地图
	 */

	//从head为头的链表当中提取出所有形状的line，并添加到DIY_head为头的链表当中

	//


	return;
}

