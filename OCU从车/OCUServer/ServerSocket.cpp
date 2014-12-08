#include "ServerSocket.h"


CServerSocket::post(char *str,char* ip,int len){
	int err;
	//创建套接字
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息
	if (!err)
	{
 //		printf("嵌套字已经打开!\n");
	}
	else
	{
		printf("嵌套字打开失败!\n");
		return 1;//结束
	}
	SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr=inet_addr(ip);
	clientsock_in.sin_family=AF_INET;
	clientsock_in.sin_port=htons(6000);
	
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接
	send(clientSocket,str,len,0);

	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
CServerSocket::wait(char *str){
	//创建套接字
//	printf("开始等待\n");
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest=MAKEWORD(1,1);
	int err;
	err=WSAStartup(myVersionRequest,&wsaData);
	if (!err)
	{
//		printf("已打开套接字\n");
	} 
	else
	{
		//进一步绑定套接字
		printf("嵌套字未打开,启动失败!\n");
		return 1;
	}
	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//创建了可识别套接字
	//需要绑定的参数
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//ip地址
	addr.sin_port=htons(6000);//绑定端口
	
	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//绑定完成
	listen(serSocket,5);//其中第二个参数代表能够接收的最多的连接数
	
	//////////////////////////////////////////////////////////////////////////
	//开始进行监听
	//////////////////////////////////////////////////////////////////////////


	SOCKADDR_IN clientsocket;
	int len=sizeof(SOCKADDR);
	while (1)
	{
		SOCKET serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//如果这里不是accept而是conection的话。。就会不断的监听

		recv(serConn,str,strlen(str)+1,0);
//		printf("%s\n",str);
		closesocket(serConn);//关闭
		WSACleanup();//释放资源的操作
		return 1;
	}
	return 0;
}

