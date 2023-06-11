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

current_map = 0;	//当前地图编号
mymap map[20];		//地图数据
Shape* Map_head = NULL, * Map_tail = NULL;
Shape* mapShape = NULL;//指向当前地图的指针
int totalVertices;
node allVertices[140];
node contourCoords[140];

Shape* CreateMap(int MapNumber) {
	/**
	 * \brief: 生成地图,记录地图的编号，顶点坐标，边的数据
	 * 
	 * \param MapNumber: 地图的编号
	 * \return : 以shape结构体返回地图的形状
	 */
	Shape* t = (Shape*)malloc(sizeof(Shape));

	//初始化地图的数据
	t->vertexNum = map[MapNumber].vertexNum;
	t->pX = 4.5;
	t->pY = 4;
	t->angle = 1;
	strcpy(t->color, "Black");
	t->isFilled = 0;
	t->isSelected = FALSE;
	t->Pensize = 1;
	t->shape = 3;//地图
	t->map_number = MapNumber;
	t->next = t->last = NULL;

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
void InitMap(int t) {
	for (int i = 0; i <= MapNumber_MAX-1; i++) {
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


void extractVertices(const Shape* head, node* allVertices, int* totalVertices) {
	/**
	 * \brief 从链表中提取所有顶点到新数组中
	 * \param head: 链表的头指针
	 * \param allVertices: 存储所有顶点的数组
	 * \param totalVertices: 存储顶点数量的变量的指针
	 */
	Shape* current = head;
	int vertexIndex = 0;

	while (current) {
		for (int i = 0; i < current->vertexNum; i++) {
			allVertices[vertexIndex] = current->vertex[i];
			vertexIndex++;
		}
		current = current->next;
	}

	*totalVertices = vertexIndex;
}


bool isLeftTurn(const node* p1, const node* p2, const node* p3) {
	/**
	 * \brief 判断三个点是否形成逆时针方向
	 * \param p1, p2, p3: 待判断的三个点
	 * \return true：逆时针方向，false：顺时针方向或共线
	 */
	double crossProduct = (p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x);
	return crossProduct > 0;
}


void getContourCoordinates(const node* allVertices, int totalVertices, node* contourCoords) {
	/**
	 * \brief 生成逆时针方向轮廓上的坐标
	 * \param allVertices: 所有顶点的数组
	 * \param totalVertices: 顶点的总数
	 * \param contourCoords: 存储轮廓上坐标的数组
	 */
	int contourIndex = 0;

	// 找到最左边的顶点作为轮廓的起点
	int startIndex = 0;
	for (int i = 1; i < totalVertices; i++) {
		if (allVertices[i].x < allVertices[startIndex].x) {
			startIndex = i;
		}
	}

	// 按逆时针方向生成轮廓上的坐标
	int currentIndex = startIndex;
	int nextIndex;

	do {
		contourCoords[contourIndex] = allVertices[currentIndex];
		contourIndex++;

		nextIndex = (currentIndex + 1) % totalVertices;

		for (int i = 0; i < totalVertices; i++) {
			if (isLeftTurn(&allVertices[currentIndex], &allVertices[i], &allVertices[nextIndex])) {
				nextIndex = i;
			}
		}

		currentIndex = nextIndex;
	} while (currentIndex != startIndex);

	// 将最后一个顶点加入轮廓坐标
	contourCoords[contourIndex] = allVertices[currentIndex];
}

void DIYMap() {
	/**
	 * \brief 自定义地图
	 */

	// 从链表中提取所有顶点到新数组中
	extractVertices(head, allVertices, &totalVertices);
	// 获得逆时针方向轮廓上的坐标
	getContourCoordinates(allVertices, totalVertices, contourCoords);

	
	// 打印轮廓坐标
	for (int i = 0; i < totalVertices; i++) {
		printf("Coordinate %d: (%lf, %lf)\n", i + 1, contourCoords[i].x, contourCoords[i].y);
	}
	MapNumber_MAX++;


	return 0;
}


