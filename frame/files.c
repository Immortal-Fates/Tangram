/*****************************************************************//**
 * \file   files.c
 * \brief	1.实现游戏状态的读写存取，
 *			2.实现自定义的用户地图的读写存取
 *			3.ranklist的读取与显示
 * \author PhilFan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "file.h"


void Read_File(void) {
	/**
	 * \brief: 读取已经保存的游戏状态 
	 * \param filename 文件名
	 */
	FILE* fp;
	if ((fp = fopen("./file/map_continue.txt", "r")) == NULL) {
		fclose(fp);
		return;
	}
	fscanf(fp, "%d\n", &current_map);

	delete_shape();

	for (int i = 1; i <= 7; i++) {
		Shape* t = (Shape*)malloc(sizeof(Shape)); // 分配内存
		char color[10];
		int shape, angle, Pensize;
		double pX, pY, width, height;
		fscanf(fp, "%d %s %lf %lf %lf %lf %d %d\n",
			&shape,color,&pX, &pY, &width, &height,
			&angle, &Pensize); 
		inventShape(1, shape, color,
			pX, pY, width, height,
			angle+1, Pensize);
	}
	fclose(fp);
}

void Save_File(int MapNumber)
{
	/**
	 * \brief 保存游戏状态,以便下次继续游戏
	 * \param MapNumber : 地图编号
	 */
	FILE *fp;
	if ((fp = fopen("./file/map_continue.txt", "w+")) == NULL)
	{
		fclose(fp);
		return;
	}
	fprintf(fp, "%d\n", MapNumber);//将地图编号写入文件

	//将以head为头结点的链表中七巧板的位置、颜色等数据写入文件
	Shape* t = head;
	while (t != NULL) {
		fprintf(fp, "%d %s %lf %lf %lf %lf %d %d\n",t->shape,t->color,t->pX,t->pY,t->width,t->height,t->angle,t->Pensize);
		t = t->next;
	}
	fclose(fp);
}

void GenerateMap(void){
	/**
	 * \brief 生成地图
	 */
	FILE* fp; 
	if ((fp = fopen("./file/map_info.txt", "r")) == NULL ) {
		printf("Can't open map info\n"); //错误处理，返回错误代码
		fclose(fp);
		return;
	}
	fscanf(fp, "%d\n", &MapNumber_MAX);
	char _;
	for (int i = 0; i < MapNumber_MAX; i++) {
		fscanf(fp, "%c%c\n",&_,&_);
		fscanf(fp, "%d\n", &map[i].vertexNum);

		for(int j = 0;j <= map[i].vertexNum-1;j++){
			char temp[100],tempx[100],tempy[100];
			fscanf(fp, "%[^\n]%*c\n",temp);
			sscanf(temp, "%s %s", tempx, tempy);
			EVIC_Eval(tempx,&map[i].vertex[j][0]);//利用EVIC_Eval函数将表达式计算出来，并且转换为double
			EVIC_Eval(tempy,&map[i].vertex[j][1]);
		}
	}
	fclose(fp);
}


void Generate_subMap(void) {
	FILE* fp;
	if ((fp = fopen("./file/submap_info.txt", "r")) == NULL) {
		fclose(fp);
		return;
	}
	int mapnumber;
	char _;
	
	for (int i = 0; i < MapNumber_MAX; i++) {
		fscanf(fp, "%c", &_);
		fscanf(fp, "%d\n", &mapnumber);
		Shape* temp = Map_head;
		while (temp) {
			if (temp->map_number == mapnumber) {
				for (int j = 1; j <= 7; j++) {
					int index;
					fscanf(fp, "%d\n", &index);
					int vertexcount = 3;
					if (index > 5) vertexcount = 4;
					for (int k = 0; k < vertexcount; k++) {
						fscanf(fp, "%lf %lf\n", &temp->graphics[index].vertex[k].x, &temp->graphics[index].vertex[k].y);

					}
				}
				break;
			}
			temp = temp->next;
		}
	}
	fclose(fp);
}

void save_subMap(int MapNumber)
{
	FILE* fp;
	if ((fp = fopen("./file/aaa.txt", "a+")) == NULL)
	{
		fclose(fp);
		return;
	}
	fprintf(fp, "#%d\n", MapNumber);//将地图编号写入文件
	//将以head为头结点的链表中七巧板的位置、颜色等数据写入文件
	Shape* t = head;
	while (t != NULL) {
		int vertexnum = t->vertexNum;
		fprintf(fp, "%d\n", t->num);
		for (int i = 0; i < vertexnum; i++)
		{
			fprintf(fp, "%lf %lf\n", t->vertex[i].x, t->vertex[i].y);
		}
		t = t->next;
	}
	fclose(fp);
}



void Save_Ranklist() {
	//输出排行榜数据到./file/ranklist.txt
	FILE* fp;
	if ((fp = fopen("./file/ranklist.txt", "w")) == NULL) {
		printf("Can't open map info\n"); //错误处理，返回错误代码
		fclose(fp); // 关闭文件指针
		return;
	}
	for(int j = 0 ; j <MapNumber_MAX; j ++)
	{
		fprintf(fp, "map = %d\n", j);
		rank(j);
		for (int i = 0; i < playerNumber; i++) {
			fprintf(fp, "%s %lf\n", player[i].name, player[i].time[j]);
		}
	}
	
	fclose(fp);
}

void Save_Userinfo(void) {
	//输出用户数据到./file/userinfo.txt
	FILE* fp;
	if ((fp = fopen("./file/userinfo.txt", "w")) == NULL) {
		printf("Can't open userinfo\n"); //错误处理，返回错误代码
		fclose(fp); // 关闭文件指针
		return;
	}
	fprintf(fp, "%d\n", playerNumber);
	for (int i = 0; i < playerNumber; i++) {
		fprintf(fp, "%d %s %s\n", player[i].index, player[i].name, player[i].password);
		for(int j = 0;j < MapNumber_MAX; j ++)
		{
			fprintf(fp, "%lf ", player[i].time[j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
void Read_Userinfo(void) {
	//输出用户数据到./file/userinfo.txt
	FILE* fp;
	if ((fp = fopen("./file/userinfo.txt", "r")) == NULL) {
		fclose(fp); // 关闭文件指针
		return;
	}
	fscanf(fp, "%d\n", &playerNumber);
	for (int i = 0; i < playerNumber; i++) {
		fscanf(fp, "%d %s %s\n", &player[i].index, player[i].name, player[i].password);
		for (int j = 0; j < MapNumber_MAX; j++)
		{
			fscanf(fp, "%lf ", &player[i].time[j]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}

//todo:创建的地图的外轮廓不会存储，记录的vertexnum
//void Save_mapCreate_File(void)
//{
//	/**
//	 * \brief:存储玩家自己创建的map，把每个tangram的信息写到./file/sub_map_info.txt中;把map的顶点信息写到./file/map_info.txt中
//	 *
//	 */
//	int len;
//	len = strlen(MapNumber_MAX);
//	FILE* fp_map;
//	if (fp_map = fopen("./file/map_info.txt", "r+"))    //读写文件
//	{
//		fseek(fp_map, len, SEEK_SET);             //offset的数值感觉有问题
//		Shape* temp = Map_head;
//		MapNumber_MAX = fscanf(fp_map, "%d\n", &MapNumber_MAX);
//		MapNumber_MAX++;
//		fseek(fp_map, len, SEEK_SET);             //offset的数值感觉有问题
//		fprintf(fp_map, "%d", MapNumber_MAX);
//		fseek(fp_map, 1000, SEEK_END);             //offset的数值感觉有问题
//		//todo:fp_map不知道怎么记录
//		//Shape* t =(Shape*) malloc(sizeof(Shape));
//		fprintf(fp_map, "#%d\n", MapNumber_MAX);
//		int vertexNum;
//
//		//		fprintf(fp_map, "%d\n", vertexNum);//记录顶点个数
//
//
//
//
//
//
//
//				//CreateMap();  //会将创建的map传到mymap里面去
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//				//for (int j = 0; j <= map[i].vertexNum - 1; j++) {
//				//	char temp[100], tempx[100], tempy[100];
//				//	fscanf(fp_map, "%[^\n]%*c\n", temp);
//				//	sscanf(temp, "%s %s", tempx, tempy);
//				//	EVIC_Eval(tempx, &map[i].vertex[j][0]);//利用EVIC_Eval函数将表达式计算出来，并且转换为double
//				//	EVIC_Eval(tempy, &map[i].vertex[j][1]);
//				//	//fprintf(pp, "%lf %lf\n", map[i].vertex[j][0], map[i].vertex[j][1]);
//				//}
//
//		fclose(fp_map);
//	}
//	FILE* fp;
//	if (fp = fopen("./file/sub_map_info.txt", "w")) //w从文件起始位置开始，会覆盖原内容
//	{
//		fseek(fp, 1000, SEEK_END);             //offset的数值感觉有问题
//		Shape* temp = head;
//		fprintf(fp, "#%d\n", MapNumber_MAX-1);
//		fprintf(fp, "1\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		temp = temp->next;
//		fprintf(fp, "2\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		temp = temp->next;
//
//		fprintf(fp, "3\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		temp = temp->next;
//
//		fprintf(fp, "4\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		temp = temp->next;
//
//		fprintf(fp, "5\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		temp = temp->next;
//
//		fprintf(fp, "6\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		fprintf(fp, "%f %f\n", temp->vertex[3].x, temp->vertex[3].y);
//		temp = temp->next;
//
//		fprintf(fp, "7\n");
//		fprintf(fp, "%f %f\n", temp->vertex[0].x, temp->vertex[0].y);
//		fprintf(fp, "%f %f\n", temp->vertex[1].x, temp->vertex[1].y);
//		fprintf(fp, "%f %f\n", temp->vertex[2].x, temp->vertex[2].y);
//		fprintf(fp, "%f %f\n", temp->vertex[3].x, temp->vertex[3].y);
//
//	}
//	fclose(fp);
//}



