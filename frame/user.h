#ifndef _USER_H_
#define USER_H
#include <../Header.h>

#define PlayerNumber_MAX 20
typedef struct User {
	char name[20];
	char password[20];
	double score;
	int time;
	int index;
}user;
user player[PlayerNumber_MAX];
extern int playerNumber;
extern int current_player;

void user_register(char* name, char* password);
bool user_login(char* name, char* password);
void user_init(void);
void rank();//Í°ÅÅĞò or ¿ìËÙÅÅĞò
inline void swap(user* a, user* b);
void echo_ranklist(void);
#endif // !_USER_H_
