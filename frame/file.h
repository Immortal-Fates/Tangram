#ifndef _FILE_H_
#define _FILE_H_

void Read_color(void);
/*Part 1 地图的存取*/
void Read_File(void); 
void Save_File(int MapNumber);
void GenerateMap();

/*Part 2 子地图的存取*/
void Generate_subMap(void);
void save_subMap(void);

/*Part 3 ranklist存取*/
void Save_Ranklist();
void Read_Ranklist(void);
void Save_Userinfo(void);
void Read_Userinfo(void);

/*Part exit 退出时候清除所有链表与数组 防止内存泄露*/
void delete_ALL(void);
void delete_map(int MapNumber);
void delete_shape(void);
void delete_user(void);

/*Part create*/
void Save_mapCreate_File(void);


//注意.h文件最后不要忘记打上分号，不然会大量报错

#endif // !_FILE_H_
