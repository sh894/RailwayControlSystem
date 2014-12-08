
#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")    //静态加入ws2_32.lib文件，使用其中的API

class CServerSocket
{
public:
	post(char *str,char* ip,int len);   //向指定IP发送指定长度的信息，相当于client端
	int wait(char *str);          //监听本机的端口，有信息输入则保存到指定位置，返回1，否则返回0，相当于server端
};

