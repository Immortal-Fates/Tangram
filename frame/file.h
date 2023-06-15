#ifndef _FILE_H_
#define _FILE_H_

void Read_color(void);
/*Part 1 ��ͼ�Ĵ�ȡ*/
void Read_File(void); 
void Save_File(int MapNumber);
void GenerateMap();

/*Part 2 �ӵ�ͼ�Ĵ�ȡ*/
void Generate_subMap(void);
void save_subMap(void);

/*Part 3 ranklist��ȡ*/
void Save_Ranklist();
void Read_Ranklist(void);
void Save_Userinfo(void);
void Read_Userinfo(void);

/*Part exit �˳�ʱ������������������� ��ֹ�ڴ�й¶*/
void delete_ALL(void);
void delete_map(int MapNumber);
void delete_shape(void);
void delete_user(void);

/*Part create*/
void Save_mapCreate_File(void);


//ע��.h�ļ����Ҫ���Ǵ��Ϸֺţ���Ȼ���������

#endif // !_FILE_H_
