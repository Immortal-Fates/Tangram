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

//注意.h文件最后不要忘记打上分号，不然会大量报错


/*Part exit 退出时候清除所有链表与数组 防止内存泄露*/
void delete_ALL(void);
void delete_map(int MapNumber);
void delete_shape(void);
void delete_user(void);

#endif // !_FILE_H_
