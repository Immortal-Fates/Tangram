/*****************************************************************//**
 * \file   keyboardEvent.c
 * \brief  键盘回调函数，实现键盘事件的响应
 *			已经实现的功能：
 *				1.按下ESC键退出程序；
 *				2.按下q,e键改变七巧板的方向；
 *				3.按下Ctrl+P		暂停/继续游戏；
 *				4.按下Ctrl+R		重置游戏；
 *				5.按下Ctrl+S		保存游戏；
 *				6.按下Ctrl+N		载入已经保存的游戏
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"

bool isCtrl = FALSE;
bool isP = FALSE, isR = FALSE, isS = FALSE,isN = FALSE;
void KeyboardEventProcess(int key, int event){
	/**
	 * \brief: 处理键盘的函数	
	 *
	 * \param key:		按键
	 * \param event：	按键事件
	 */
	double mouseX = GetCurrentX();//pixel -> inches
	double mouseY = GetCurrentY();
	
	switch (key)
	{
		case VK_ESCAPE: //按下ESC键退出程序；
			game_status = 2;
			exit(0);
			break;
		case 'P':		//ctrl+P 暂停/继续游戏
			isP = !event;
			if (isP && isCtrl)
				if (game_status == 0)		game_status = 1;
				else if (game_status == 1)	game_status = 0;
			break;
		case 'R':		//ctrl+R 重置游戏
			isR = !event;
			if (isR && isCtrl)
				if (game_status == 0)		game_status = 2;
				else if (game_status == 1)	game_status = 2;
				
			break;
		//todo: QE没有写好
		case 'Q':		//按Q，判断鼠标是否在图形内，如果是就逆时针旋转七巧板
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
		case 'E':		//按E，判断鼠标是否在图形内，如果是就顺时针旋转七巧板
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
		case 'S':		//按Ctrl+S 保存游戏
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
		case VK_LCONTROL: case VK_RCONTROL: case VK_CONTROL: //按下Ctrl键
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

