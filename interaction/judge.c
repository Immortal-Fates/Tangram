/*****************************************************************//**
 * \file   judge.c
 * \brief  七巧板问题的判定函数，判断玩家是否完成拼图
 *			主要思路：利用边的重合，
 * \author 
 * \date   May 2023
 *********************************************************************/
#include "../Header.h"
#include "judge.h"

bool IsParallel(line* line1, line* line2);				//from mouseevent.c
double DistanceBetweenLines(line* line1, line* line2);	//from mouseevent.c

//todo:判断是否完成拼图
bool judge_complishment ()
{
	if (1)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

