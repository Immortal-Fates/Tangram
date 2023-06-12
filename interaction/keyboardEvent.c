/*****************************************************************//**
 * \file   keyboardEvent.c
 * \brief  ���̻ص�������ʵ�ּ����¼�����Ӧ
 *			�Ѿ�ʵ�ֵĹ��ܣ�
 *				1.����ESC���˳�����
 *				2.����q,e���ı����ɰ�ķ���
 *				3.����Ctrl+P		��ͣ/������Ϸ��
 *				4.����Ctrl+R		������Ϸ��
 *				5.����Ctrl+S		������Ϸ��
 *				6.����Ctrl+N		�����Ѿ��������Ϸ
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"

bool isCtrl = FALSE;
bool isP = FALSE, isR = FALSE, isS = FALSE,isN = FALSE;
void KeyboardEventProcess(int key, int event){
	/**
	 * \brief: ������̵ĺ���	
	 *
	 * \param key:		����
	 * \param event��	�����¼�
	 */
	double mouseX = GetCurrentX();//pixel -> inches
	double mouseY = GetCurrentY();
	
	switch (key)
	{
		case VK_ESCAPE: //����ESC���˳�����
			game_status = 2;
			exit(0);
			break;
		case 'P':		//ctrl+P ��ͣ/������Ϸ
			isP = !event;
			if (isP && isCtrl)
				if (game_status == 0)		game_status = 1;
				else if (game_status == 1)	game_status = 0;
			break;
		case 'R':		//ctrl+R ������Ϸ
			isR = !event;
			if (isR && isCtrl)
				if (game_status == 0)		game_status = 2;
				else if (game_status == 1)	game_status = 2;
				
			break;
		//todo: QEû��д��
		case 'Q':		//��Q���ж�����Ƿ���ͼ���ڣ�����Ǿ���ʱ����ת���ɰ�
			if (event) {
				Shape* temp = head;
				while (temp) {
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{
						temp->angle = (temp->angle + 1) % 8;
						break;
					}
					temp = temp->next;
				}
			}
			break;
		case 'E':		//��E���ж�����Ƿ���ͼ���ڣ�����Ǿ�˳ʱ����ת���ɰ�
			if (event) {

				Shape* temp = head;
				while (temp) {
					if (isInShape(temp, mouseX, mouseY) && !game_status)
					{

						temp->angle = (temp->angle + 7) % 8;
						break;
					}
					temp = temp->next;
				}
			}
			break;
		case 'S':		//��Ctrl+S ������Ϸ
			isS = !event;
			if (isS && isCtrl)
				Save_File(current_map);
			break;
		case 'N':
			isN = !event;
			if (isN && isCtrl) {

				current_time = TIME_LEFT;
				Read_File();
			}
			break;
		case VK_LCONTROL: case VK_RCONTROL: case VK_CONTROL: //����Ctrl��
			isCtrl = !event;
			if (isP && isCtrl)
				if (game_status == 0)		game_status = 1;
				else if (game_status == 1)	game_status = 0;
			if (isR && isCtrl)
				if (game_status == 0)		game_status = 2;
				else if (game_status == 1)	game_status = 2;
			if (isS && isCtrl)
				Save_File(current_map);

			if (isN && isCtrl) {
				current_time = TIME_LEFT;
				Read_File();
				game_status = 0;
			}				
			break;

	}
	display();
}

