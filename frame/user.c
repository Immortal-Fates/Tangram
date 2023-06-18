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
int current_player;
void user_login_button()
{
	static char userName[80] = "";
	static char userPasswd[80] = "";
	static char results[200] = "";
	double fH = GetFontHeight();
	double h = fH * 2; // 控件高度
	double w = WindowWidth / 4; // 控件宽度
	double x = WindowWidth / 2.5;
	double y = WindowHeight / 1.5 - h;
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	int size = GetPointSize();
	SetPenColor("#001e1d");
	SetPointSize(30);
	MovePen(3, 7);
	DrawTextString("请输入用户名和密码，未在用户库当中会新建用户");
	SetPenColor("Brown");
	drawLabel(x - fH / 2 - TextStringWidth("用户名"), (y -= h * 1.2) + fH * 0.7, "用户名");
	textbox(GenUIID(0), x, y, w, h, userName, sizeof(userName));

	SetPenColor("Brown");
	drawLabel(x - fH / 2 - TextStringWidth("密码"), (y -= h * 1.2) + fH * 0.7, "密码");
	textbox(GenUIID(0), x, y, w, h, userPasswd, sizeof(userPasswd));
	if (button(GenUIID(0), 6.3, 1.5, WindowWidth / 10, 0.4, "Login")) {
		for (int i = 0; i <= playerNumber; i++)
		{
			if (strcmp(userName, player[i].name) == 0) {
				if (strcmp(userPasswd, player[i].password) == 0) {
					game_status = -1;
					current_player = i;
					return;
				}
				else {
					SetPenColor("Gray");
					drawLabel(x, y -= fH * 1.2, "密码错误");
					return;
				}
			}
		}
		if (strlen(userName) != 0)
		{
			user_register(userName, userPasswd);
		}
		game_status = -1;
	}
	SetPointSize(size);
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor	
}
void user_register(char* name, char* password) {
	/**
	 * \brief 注册用户
	 * \param name		用户名
	 * \param password	密码
	 */
	player[playerNumber].index = playerNumber;
	strcpy(player[playerNumber].name, name);
	for(int i = 0; i < MapNumber_MAX;i++)
	{
		player[playerNumber].time[i] = TIME_LEFT;
	}
	strcpy(player[playerNumber].password, password);
	current_player = playerNumber;
	playerNumber += 1;
}
void user_init(void) {
	/**
	 * \brief 从文件中读取用户信息，初始化user数组
	 * 
	 */
	Read_Userinfo();
}
void user_save(void) {
	/**
	 * \brief 将user数组中的用户信息保存到文件中
	 * 
	 */
	Save_Ranklist();
	rank_by_index();
	Save_Userinfo();
}
void rank_by_index(void)
{
	//根据用户的index对user数组进行排序
	for (int i = 0; i < playerNumber; i++) {
		for (int j = 0; j < playerNumber; j++) {
			if (player[i].index < player[j].index) {
				//交换两个结构体的数据
				swap(&player[i], &player[j]);
			}
		}
	}
}
void rank(int temp){
	/**
	 * .\brief 桶排序 or 快速排序 实现对于user数组的排序，为了输出排行榜功能做准备
	 * 
	 */
	//桶排序
	//for (int i = 0; i < playerNumber; i++) {
	//	for (int j = 0; j < playerNumber; j++) {
	//		if (player[i].time[temp] < player[j].time[temp]) {
	//			//交换两个结构体的数据
	//			swap(&player[i], &player[j]);
	//		}
	//	}
	//}
	//快速排序，对结构体数组进行排序
	quickSort(player, 0, playerNumber - 1, temp);
}
inline void swap(user *a, user *b) {
	user temp = *a;
	*a = *b;
	*b = temp;
}
inline void quickSort(user* arr, int low, int high, int temp) {
	if (low < high) {
		int pivot = partition(arr, low, high, temp);
		quickSort(arr, low, pivot - 1, temp);
		quickSort(arr, pivot + 1, high, temp);
	}
}
inline int partition(user* arr, int low, int high, int temp) {
	user pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (arr[j].time[temp] < pivot.time[temp]) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}



void echo_ranklist(int temp) {
	/**
	 * .\brief 输出指定地图的排行榜
	 */
	int pensize = GetPenSize();
	string pencolor = GetPenColor();
	int size = GetPointSize();
	SetPenColor("Black");
	SetPointSize(30);
	double fH = GetFontHeight();
	char ranklist_content[200];
	rank(temp);

	for (int i = 0; i < min(8, playerNumber); i++) {
		if (player[i].time[temp] == 0 || player[i].time[temp] == TIME_LEFT) continue;
		sprintf(ranklist_content, "User Name: %s TimeUsed:%.1lf\n", player[i].name, player[i].time[temp]);
		MovePen(4, 8 - 2 * fH * i);
		DrawTextString(ranklist_content);
	}
	SetPointSize(size);		//back to system pointsize
	SetPenSize(pensize);	//back to system pensize
	SetPenColor(pencolor);	//back to system pencolor	
}



