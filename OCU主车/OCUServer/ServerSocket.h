
#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")    //��̬����ws2_32.lib�ļ���ʹ�����е�API

class CServerSocket
{
public:
	post(char *str,char* ip,int len);   //��ָ��IP����ָ�����ȵ���Ϣ���൱��client��
	int wait(char *str);          //���������Ķ˿ڣ�����Ϣ�����򱣴浽ָ��λ�ã�����1�����򷵻�0���൱��server��
};

