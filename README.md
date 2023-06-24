# C程序设计专题项目——Tangram

[TOC]



## 一、快速学会使用

**（所有操作都放在了演示视频当中）**

1.打开tangram.exe文件，请不要修改./file下的任何文件

2.**阅读introduction界面**

3.点击play界面

![image-20230624104446038](https://gitee.com/philfan/my-images/raw/master/image-20230624104446038.png)

4.输入用户名及密码登陆

![image-20230624104526298](https://gitee.com/philfan/my-images/raw/master/image-20230624104526298.png)

5.选择new game 任意打开想要的地图

![image-20230624104643569](https://gitee.com/philfan/my-images/raw/master/image-20230624104643569.png)

![image-20230624104656773](https://gitee.com/philfan/my-images/raw/master/image-20230624104656773.png)

**右键单击旋转**

点击menu中的“HINT”会有提示

6.点击创建地图

![img](https://gitee.com/philfan/my-images/raw/master/clip_image002.gif)

注意这里函数有一些问题，请尽量不要旋转太多次，非常感谢



7.排行榜



## 二、题目要求及实现详解

### 基本功能要求：（全部实现）

（一）实现基础的图形界面：

- 选择要挑战的七巧板

- 旋转按钮(使用鼠标右键进行旋转)

- 鼠标拖拽图块（实现吸附功能）

- 游戏说明

- 游戏状态的文件保存载入。（ctrl+s保存 ctrl+n 打开） 

（二）提供至少 5 个七巧板游戏。保存在文件中，程序启动时自动载入，供用户选择挑战。 

（三） 为每一个七巧板游戏，提供提示，用户可以按照提示完成游戏。 

（四）有计时功能，让用户在规定时间内完成全部七巧板的放置。超出时间，停止游戏，并弹出游戏失败的信息。

 

### 较高功能要求 ：（基本实现）

（一）创建七巧板游戏模式，让用户通过应用程序创建游戏，然后开始挑战。

（二）自动判定游戏是否成功的状态。每次用户操作之后，自动检测是否成功完成拼图。（根据多边形是否相交、是否位于终图多边形内部，以及面积关系，判定是否拼图成功）

### 附加功能

- 用户登录系统
- 排行榜、天梯系统
- 优秀的UI设计
- 较多的代码注释

## 三、代码结构

![Tangram](https://gitee.com/philfan/my-images/raw/master/Tangram.png)
