#include "ServerSocket.h"
#include "RS485.h"
#include "Frame.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID p);
void run1();
DWORD WINAPI fun1(LPVOID p);
DWORD WINAPI fun2(LPVOID p);

frame *reg = new frame;
RS485 com;
CServerSocket s; 

char *CarIP = "172.31.44.17"; //�ӳ�IP
char *RsIP  = "172.31.3.188"; //ע�������IP

void main(){
	printf("***********************����OCUϵͳ*********************\n");
	printf("\n");
	run1();
}
void run1(){   //�߳�
	HANDLE hThrd,hThrd1;
	DWORD threadID;
	hThrd = CreateThread(NULL,0,fun1,(LPVOID)1,0,&threadID);
	if(hThrd) {
		printf("***********************�����Ѿ�����********************\n");
		printf("\n");
	}
	hThrd1 = CreateThread(NULL,0,fun2,(LPVOID)1,0,&threadID);
	if(hThrd)  {
		printf("***********************TCP�Ѿ�����*********************\n");
		printf("\n");
	}
	Sleep(2000000);
}

DWORD WINAPI fun1(LPVOID p){   //��������

	while(1){
		if(com.receive(*reg)){
			printf("**************************************************\n");
			printf("�����յ���Ϣ�� %d ��Ϣ����Ϊ: %d\n",reg->getFrame,reg->getLength());
			for(int i = 0;i < reg->getFrame()[2];i ++){
				printf("%0x  ,",reg->getFrame()[i]);
			}
			printf("\n");
			printf("***************************************************\n");
			printf("\n");
			switch(reg->frame_type){
			case MSG_CTL:{   //ȥ�ӳ�OCU
				int len = reg->getLength();
				s.post(reg->getFrame(),CarIP,len);
				printf("*****************���͸��ӳ���Ϣ�ɹ�****************\n");
				printf("\n");
				break; 
				} 
			default:{    //ȥRS
				int len = reg->getLength();
				s.post(reg->getFrame(),RsIP,len);
				printf("******************���͸�RS��Ϣ�ɹ�*****************\n");
				printf("\n");
				break;
				}
			}
		}
	}
	return 1;
}
DWORD WINAPI fun2(LPVOID p){ //����TCP 
	

	while(1){
		char *str = new char[100];
		if(s.wait(str)){
	
			frame *receive = new frame(str[4]);
			memcpy(receive->getFrame(),str,str[2]);
			printf("***************************************************\n");
			printf("TCP�յ���Ϣ��%d ��Ϣ����Ϊ: %d\n",receive->getFrame(),receive->getLength());
			for(int i = 0;i < receive->getLength();i ++){
				printf("%0x  ,",receive->getFrame()[i]);
			}
			printf("\n");
			printf("***************************************************\n");
			printf("\n");
			com.send(*receive);
			printf("***************************************************\n");
			printf("***************���͸�����LSPU��Ϣ�ɹ�**************\n");
			printf("***************************************************\n");
			printf("\n");
		}
	}
	return 1;
}