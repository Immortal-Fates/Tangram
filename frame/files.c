/*****************************************************************//**
 * \file   files.c
 * \brief	1.ʵ����Ϸ״̬�Ķ�д��ȡ��
 *			2.ʵ���Զ�����û���ͼ�Ķ�д��ȡ
 *			3.ranklist�Ķ�ȡ����ʾ
 * \author PhilFan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "file.h"


void Read_File(void) {
	/**
	 * \brief: ��ȡ�Ѿ��������Ϸ״̬ 
	 * \param filename �ļ���
	 */
	FILE* fp;
	if ((fp = fopen("./file/map_continue.txt", "r")) == NULL) {
		fclose(fp);
		return;
	}
	fscanf(fp, "%d\n", &current_map);

	delete_shape();

	for (int i = 1; i <= 7; i++) {
		Shape* t = (Shape*)malloc(sizeof(Shape)); // �����ڴ�
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
	 * \brief ������Ϸ״̬,�Ա��´μ�����Ϸ
	 * \param MapNumber : ��ͼ���
	 */
	FILE *fp;
	if ((fp = fopen("./file/map_continue.txt", "w+")) == NULL)
	{
		fclose(fp);
		return;
	}
	fprintf(fp, "%d\n", MapNumber);//����ͼ���д���ļ�

	//����headΪͷ�������������ɰ��λ�á���ɫ������д���ļ�
	Shape* t = head;
	while (t != NULL) {
		fprintf(fp, "%d %s %lf %lf %lf %lf %d %d\n",t->shape,t->color,t->pX,t->pY,t->width,t->height,t->angle,t->Pensize);
		t = t->next;
	}
	fclose(fp);
}

void GenerateMap(void){
	/**
	 * \brief ���ɵ�ͼ
	 */
	FILE* fp; 
	if ((fp = fopen("./file/map_info.txt", "r")) == NULL ) {
		printf("Can't open map info\n"); //���������ش������
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
			EVIC_Eval(tempx,&map[i].vertex[j][0]);//����EVIC_Eval���������ʽ�������������ת��Ϊdouble
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
	fprintf(fp, "#%d\n", MapNumber);//����ͼ���д���ļ�
	//����headΪͷ�������������ɰ��λ�á���ɫ������д���ļ�
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
	//������а����ݵ�./file/ranklist.txt
	FILE* fp;
	if ((fp = fopen("./file/ranklist.txt", "w")) == NULL) {
		printf("Can't open map info\n"); //���������ش������
		fclose(fp); // �ر��ļ�ָ��
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
	//����û����ݵ�./file/userinfo.txt
	FILE* fp;
	if ((fp = fopen("./file/userinfo.txt", "w")) == NULL) {
		printf("Can't open userinfo\n"); //���������ش������
		fclose(fp); // �ر��ļ�ָ��
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
	//����û����ݵ�./file/userinfo.txt
	FILE* fp;
	if ((fp = fopen("./file/userinfo.txt", "r")) == NULL) {
		fclose(fp); // �ر��ļ�ָ��
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

//todo:�����ĵ�ͼ������������洢����¼��vertexnum
//void Save_mapCreate_File(void)
//{
//	/**
//	 * \brief:�洢����Լ�������map����ÿ��tangram����Ϣд��./file/sub_map_info.txt��;��map�Ķ�����Ϣд��./file/map_info.txt��
//	 *
//	 */
//	int len;
//	len = strlen(MapNumber_MAX);
//	FILE* fp_map;
//	if (fp_map = fopen("./file/map_info.txt", "r+"))    //��д�ļ�
//	{
//		fseek(fp_map, len, SEEK_SET);             //offset����ֵ�о�������
//		Shape* temp = Map_head;
//		MapNumber_MAX = fscanf(fp_map, "%d\n", &MapNumber_MAX);
//		MapNumber_MAX++;
//		fseek(fp_map, len, SEEK_SET);             //offset����ֵ�о�������
//		fprintf(fp_map, "%d", MapNumber_MAX);
//		fseek(fp_map, 1000, SEEK_END);             //offset����ֵ�о�������
//		//todo:fp_map��֪����ô��¼
//		//Shape* t =(Shape*) malloc(sizeof(Shape));
//		fprintf(fp_map, "#%d\n", MapNumber_MAX);
//		int vertexNum;
//
//		//		fprintf(fp_map, "%d\n", vertexNum);//��¼�������
//
//
//
//
//
//
//
//				//CreateMap();  //�Ὣ������map����mymap����ȥ
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
//				//	EVIC_Eval(tempx, &map[i].vertex[j][0]);//����EVIC_Eval���������ʽ�������������ת��Ϊdouble
//				//	EVIC_Eval(tempy, &map[i].vertex[j][1]);
//				//	//fprintf(pp, "%lf %lf\n", map[i].vertex[j][0], map[i].vertex[j][1]);
//				//}
//
//		fclose(fp_map);
//	}
//	FILE* fp;
//	if (fp = fopen("./file/sub_map_info.txt", "w")) //w���ļ���ʼλ�ÿ�ʼ���Ḳ��ԭ����
//	{
//		fseek(fp, 1000, SEEK_END);             //offset����ֵ�о�������
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



