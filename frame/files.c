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



void Read_File(string filename) {
	/**
	 * \brief: 读取已经保存的游戏状态 
	 * \param filename 文件名
	 */
	FILE* fp;
	if ((fp = fopen("./file/map1.txt", "r")) == NULL) {
		printf("Can't open file %s\n", filename); //错误处理，返回错误代码
		return;
	}
	fscanf(fp, "%d\n", &MapNumber_MAX);

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
	char filename[20];
	sprintf(filename, "./file/map%d.txt", MapNumber);
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("Can't open file %s\n", filename);
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
	FILE* fp,* pp; 
	pp = fopen("./file/error.txt", "w");
	if ((fp = fopen("./file/map_info.txt", "r")) == NULL ) {
		printf("Can't open map info\n"); //错误处理，返回错误代码
		fclose(pp); // 关闭文件指针
		return;
	}
	fscanf(fp, "%d\n", &MapNumber_MAX);
	char _;
	for (int i = 0; i <= MapNumber_MAX-1; i++) {
		fscanf(fp, "%c%c\n",&_,&_);
		fscanf(fp, "%d\n", &map[i].vertexNum);
		fprintf(pp, "num = %d\n", map[i].vertexNum);

		for(int j = 0;j <= map[i].vertexNum-1;j++){
			char temp[100],tempx[100],tempy[100];
			fscanf(fp, "%[^\n]%*c\n",temp);
			sscanf(temp, "%s %s", tempx, tempy);
			EVIC_Eval(tempx,&map[i].vertex[j][0]);//利用EVIC_Eval函数将表达式计算出来，并且转换为double
			EVIC_Eval(tempy,&map[i].vertex[j][1]);
			fprintf(pp,"%lf %lf\n",map[i].vertex[j][0],map[i].vertex[j][1]);
			//fprintf(pp, "%%%\n");
		}
	}
	//fscanf(fp, "%c%c\n", &_, &_);
	fprintf(pp, "##");
	fclose(fp);
	fclose(pp);
}


void Generate_subMap(void) {
	FILE* fp;
	if ((fp = fopen("./file/submap_info.txt", "r")) == NULL) {
		fclose(fp);
	}
	int mapnumber;
	char _;
	
	for (int i = 0; i < 1; i++) {
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

void SaveMap(void) {
	/**
	 * .\brief 自定义地图的存储
	 * 
	 */

}



void Save_Ranklist(void) {
	//输出排行榜数据到./file/ranklist.txt
	FILE* fp;
	if ((fp = fopen("./file/ranklist.txt", "w")) == NULL) {
		printf("Can't open map info\n"); //错误处理，返回错误代码
		fclose(fp); // 关闭文件指针
		return;
	}
	fprintf(fp, "%d\n", playerNumber);
	for (int i = 0; i < playerNumber; i++) {
		fprintf(fp, "%d %s %lf %d\n",player[i].index, player[i].name, player[i].score, player[i].time);
	}
	fclose(fp);
}
void Read_Ranklist(void) {
	FILE* fp;
	if ((fp = fopen("./file/ranklist.txt", "r")) == NULL) {
		printf("Can't open file\n"); //错误处理，返回错误代码
		fclose(fp); // 关闭文件指针
		return;
	}
	fscanf(fp, "%d\n", &playerNumber);
	for (int i = 0; i < playerNumber; i++) {
		fscanf(fp, "%d %s %lf %d\n", &player[i].index, player[i].name, &player[i].score, &player[i].time);
	}
	fclose(fp);
}

void Save_Userinfo(void) {
	//输出用户数据到./file/userinfo.txt
	FILE* fp;
	if ((fp = fopen("./file/userinfo.txt", "w")) == NULL) {
		printf("Can't open map info\n"); //错误处理，返回错误代码
		fclose(fp); // 关闭文件指针
		return;
	}
	fprintf(fp, "%d\n", playerNumber);
	for (int i = 0; i < playerNumber; i++) {
		fprintf(fp, "%d %s %s\n", i, player[i].name,player[i].password);
	}
	fclose(fp);
}



