#pragma once
#include "frame.h"
#include <windows.h>
class RS485
{
	
protected:
	//串口句柄
	HANDLE hCom;
	
	//初始化串口
	bool initiate();
public:
	
	//构造函数
	RS485(void);
	
	//析构函数
	~RS485(void);
	
public:
	
	//发送
	bool send(frame &frame_send);
	
	//接收
	bool receive(frame &frame_receive);
};

