#include "ServerSocket.h"


CServerSocket::post(char *str,char* ip,int len){
	int err;
	//�����׽���
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//Э���İ汾��Ϣ
	if (!err)
	{
 //		printf("Ƕ�����Ѿ���!\n");
	}
	else
	{
		printf("Ƕ���ִ�ʧ��!\n");
		return 1;//����
	}
	SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr=inet_addr(ip);
	clientsock_in.sin_family=AF_INET;
	clientsock_in.sin_port=htons(6000);
	
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//��ʼ����
	send(clientSocket,str,len,0);

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
CServerSocket::wait(char *str){
	//�����׽���
//	printf("��ʼ�ȴ�\n");
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest=MAKEWORD(1,1);
	int err;
	err=WSAStartup(myVersionRequest,&wsaData);
	if (!err)
	{
//		printf("�Ѵ��׽���\n");
	} 
	else
	{
		//��һ�����׽���
		printf("Ƕ����δ��,����ʧ��!\n");
		return 1;
	}
	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���
	//��Ҫ�󶨵Ĳ���
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//ip��ַ
	addr.sin_port=htons(6000);//�󶨶˿�
	
	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//�����
	listen(serSocket,5);//���еڶ������������ܹ����յ�����������
	
	//////////////////////////////////////////////////////////////////////////
	//��ʼ���м���
	//////////////////////////////////////////////////////////////////////////


	SOCKADDR_IN clientsocket;
	int len=sizeof(SOCKADDR);
	while (1)
	{
		SOCKET serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���

		recv(serConn,str,strlen(str)+1,0);
//		printf("%s\n",str);
		closesocket(serConn);//�ر�
		WSACleanup();//�ͷ���Դ�Ĳ���
		return 1;
	}
	return 0;
}

