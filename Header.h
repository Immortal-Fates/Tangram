/*****************************************************************//**
 * \file   Header.h
 * \brief  用于包含所有的头文件，防止重复引用，减少重复代码
 * 
 * \author Philfan
 * \date   May 2023
 *********************************************************************/
#ifndef _Header_H_
#define _Header_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#include "./frame/file.h"
#include "./frame/map.h"
#include "./frame/shape.h"
#include "./frame/user.h"
#include "./interaction/judge.h"
#include "./interaction/solve.h"
#include "./interaction/ui.h"
#include "./interaction/mouseEvent.h"

#include "main.h"

#include <graphics.h>
#include <simpio.h>
#include <strlib.h>
#include <boolean.h>
#include <exception.h>
#include <extgraph.h>
#include <gcalloc.h>
#include <genlib.h>
#include <imgui.h>
#include <random.h>
#include <eval.h>

#endif // !_Header_H_
