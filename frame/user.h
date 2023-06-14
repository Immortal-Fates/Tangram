#ifndef _USER_H_
#define USER_H

#define PlayerNumber_MAX 20
typedef struct User {
	int index;
	char name[20];
	char password[20];
	double time[100];	//每个地图的时间
}user;
user player[PlayerNumber_MAX];
extern int playerNumber;
extern int current_player;


void user_init(void);
void user_save(void);
void user_login_button();
void user_register(char* name, char* password);

void rank(int temp);//桶排序 or 快速排序
void rank_by_index();
inline void swap(user* a, user* b);
inline int partition(user* arr, int low, int high, int temp);
inline void quickSort(user* arr, int low, int high, int temp);
void echo_ranklist(int temp);
#endif // !_USER_H_
