#ifndef _FILE_H_
#define _FILE_H_
#include <../Header.h>
#include <extgraph.h>

void Read_File(string ); 
void Save_File(int MapNumber);
void GenerateMap();

void Save_Ranklist(void);
void Read_Ranklist(void);
void Save_Userinfo(void);

//ע��.h�ļ����Ҫ���Ǵ��Ϸֺţ���Ȼ���������


/*Part exit �˳�ʱ������������������� ��ֹ�ڴ�й¶*/
void delete_ALL(void);
void delete_map(int MapNumber);
void delete_shape(void);
void delete_user(void);

#endif // !_FILE_H_
