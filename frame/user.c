/*****************************************************************//**
 * \file   user.c
 * \brief  创建用户，实现用户的登录和注册功能
 *			实现排行榜功能
 * 
 * \author Philfan
 * \date   June 2023
 *********************************************************************/
#include "../Header.h"

user player[PlayerNumber_MAX];
int playerNumber;

void user_register(char* name, char* password) {
	/**
	 * \brief 注册用户
	 * \param name		用户名
	 * \param password	密码
	 */
	player[playerNumber].index = playerNumber;
	strcpy(player[playerNumber].name, name);
	player[playerNumber].score = 0;
	player[playerNumber].time = 0;
	strcpy(player[playerNumber].password, password);
	playerNumber += 1;
}
bool user_login(char* name, char* password) {
	/**
	 * .\brief 用户登录
	 * \param name 用户名
	 * \param password	用户密码
	 * \return 
	 */
	for (int i = 0; i < playerNumber; i++) {
		if(strcmp(name,player[i].name) == 0){
			if (strcmp(password, player[i].password) == 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
void user_init(void) {
	/**
	 * \brief 从文件中读取用户信息，初始化user数组
	 * 
	 */
	Read_Ranklist();
	user_register("admin", "admin");
	rank();
	Save_Ranklist();
	Save_Userinfo();
	
}
void rank(){
	/**
	 * .\brief 桶排序 or 快速排序 实现对于user数组的排序，为了输出排行榜功能做准备
	 * 
	 */
	//桶排序
	for (int i = 0; i < playerNumber; i++) {
		for (int j = 0; j < playerNumber; j++) {
			if (player[i].score > player[j].score) {
				//交换两个结构体的数据
				swap(&player[i], &player[j]);
			}
		}
	}
	//todo:快速排序

	//对结构体数组进行排序
}
inline void swap(user *a, user *b) {
	user temp = *a;
	*a = *b;
	*b = temp;
}
