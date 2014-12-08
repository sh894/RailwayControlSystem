#pragma once
#include "frame.h"
#include <windows.h>
class RS485
{
	
protected:
	//���ھ��
	HANDLE hCom;
	
	//��ʼ������
	bool initiate();
public:
	
	//���캯��
	RS485(void);
	
	//��������
	~RS485(void);
	
public:
	
	//����
	bool send(frame &frame_send);
	
	//����
	bool receive(frame &frame_receive);
};

