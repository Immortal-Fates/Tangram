/*****************************************************************//**
 * \file   files.c
 * \brief  ʵ����Ϸ״̬�Ķ�д��ȡ��ranklist�Ķ�ȡ����ʾ
 * 
 * \author PhilFan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "file.h"

void Read_File(string filename) {
	/**
	 * \brief: ��ȡ�Ѿ��������Ϸ״̬ 
	 * \param filename �ļ���
	 */
	FILE* fp;
	if ((fp = fopen("./file/map1.txt", "r")) == NULL) {
		printf("Can't open file %s\n", filename); //���������ش������
		return;
	}
	fscanf(fp, "%d\n", &MapNumber_MAX);

	delete_shape();


	for (int i = 1; i <= 7; i++) {
		Shape* t = (Shape*)malloc(sizeof(Shape)); // �����ڴ�
		bool isfilled;
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
	//todo: �Ż���ȡ�߼�
	FILE *fp;
	char filename[20];
	sprintf(filename, "./file/map%d.txt", MapNumber);
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("Can't open file %s\n", filename);
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
	FILE* fp,* pp; 
	pp = fopen("./file/error.txt", "w");
	if ((fp = fopen("./file/map_info.txt", "r")) == NULL ) {
		printf("Can't open map info\n"); //���������ش������
		fclose(pp); // �ر��ļ�ָ��
		return;
	}
	fscanf(fp, "%d\n", &MapNumber_MAX);
	char _;
	for (int i = 0; i <= MapNumber_MAX-1; i++) {
		fscanf(fp, "%c%c\n",&_,&_);
		fscanf(fp, "%d\n", &map[i].vertexNum);
		fprintf(pp, "%d\n", map[i].vertexNum);
		for(int j = 0;j <= map[i].vertexNum-1;j++){
			char temp[100],tempx[100],tempy[100];
			fscanf(fp, "%[^\n]%*c\n",temp);
			sscanf(temp, "%s %s", tempx, tempy);
			EVIC_Eval(tempx,&map[i].vertex[j][0]);//����EVIC_Eval���������ʽ�������������ת��Ϊdouble
			EVIC_Eval(tempy,&map[i].vertex[j][1]);
			fprintf(pp,"%lf %lf\n",map[i].vertex[j][0],map[i].vertex[j][1]);
		}
	}
	fscanf(fp, "%c%c\n", &_, &_);
	fprintf(pp, "##");
	fclose(fp);
	fclose(pp);
}
void Save_Ranklist(void) {

}
void Read_Ranklist(void) {

}
