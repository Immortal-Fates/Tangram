/*****************************************************************//**
 * \file   user.c
 * \brief  �����û���ʵ���û��ĵ�¼��ע�Ṧ��
 *			ʵ�����а���
 * 
 * \author Philfan
 * \date   June 2023
 *********************************************************************/
#include "../Header.h"

user player[PlayerNumber_MAX];
int playerNumber;

void user_register(char* name, char* password) {
	/**
	 * \brief ע���û�
	 * \param name		�û���
	 * \param password	����
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
	 * .\brief �û���¼
	 * \param name �û���
	 * \param password	�û�����
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
	 * \brief ���ļ��ж�ȡ�û���Ϣ����ʼ��user����
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
	 * .\brief Ͱ���� or �������� ʵ�ֶ���user���������Ϊ��������а�����׼��
	 * 
	 */
	//Ͱ����
	for (int i = 0; i < playerNumber; i++) {
		for (int j = 0; j < playerNumber; j++) {
			if (player[i].score > player[j].score) {
				//���������ṹ�������
				swap(&player[i], &player[j]);
			}
		}
	}
	//todo:��������

	//�Խṹ�������������
}
inline void swap(user *a, user *b) {
	user temp = *a;
	*a = *b;
	*b = temp;
}
