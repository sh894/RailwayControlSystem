#include "stdafx.h"
#include "RS485.h"
RS485::RS485(void)
{
	this->initiate();
}


RS485::~RS485(void)
{
}

bool RS485::initiate(){
	//打开串口

	hCom=CreateFile(_T("COM4"),//COM1口
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,//引用安全性属性结构，缺省值为NULL
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);//对串口而言该参数必须置为NULL

	if(hCom==(HANDLE)-1)
	{
		std::cout<<"打开串口失败！"<<std::endl;

		return FALSE;
	}


	//配置串口
	SetupComm(hCom,// 通信设备的句柄 
		100,// 输入缓冲区的大小（字节数）
		100); // 输出缓冲区的大小（字节数）

	COMMTIMEOUTS TimeOuts;//用COMMTIMEOUTS结构可以规定读写操作的超时。
	//设定读超时
	TimeOuts.ReadIntervalTimeout=MAXWORD; //读间隔超时
	TimeOuts.ReadTotalTimeoutMultiplier=1; //读时间系数
	TimeOuts.ReadTotalTimeoutConstant=1;//读时间常量
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。


	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier=100;// 写时间系数
	TimeOuts.WriteTotalTimeoutConstant=500;//写时间常量
	SetCommTimeouts(hCom,&TimeOuts); //设置超时

	DCB dcb;//DCB结构包含了串口的各项参数设置
	GetCommState(hCom,&dcb);//获得COM口的设备控制块，从而获得相关参数送入dcb
	dcb.BaudRate=9600; //波特率为9600
	dcb.ByteSize=8; //每个字节有8位
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=TWOSTOPBITS; //两个停止位
	SetCommState(hCom,&dcb);//函数设置COM口的设备控制块

	//PurgeComm()函数清空缓冲区
	PurgeComm(hCom,//串口句柄
		PURGE_TXCLEAR|PURGE_RXCLEAR);// 需要完成的操作

	return TRUE;
}

bool RS485::send(frame &frm){
	DWORD dwBytesWrite=frm.getLength();
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,frm.getFrame(),dwBytesWrite,& dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		std::cout<<"写串口失败"<<std::endl;
		return false;
	}
	return true;
}

bool RS485::receive(frame &frame_receive){

//读取的字节数
	DWORD wCount;
	//读取状态
	int bReadStat = 0;
	char byte_buf = 0;
	char *frame_length = new char[2];
	char frame_type = 0;

//	printf("开始读取\n");
	//读取起始位
	ReadFile(hCom,&byte_buf,1,&wCount,NULL);
	if (byte_buf != 0x10)
	{
//		printf("未读取到起始位0x10\n");
		return false;
	}
	ReadFile(hCom,&byte_buf,1,&wCount,NULL);
	if(byte_buf != 0x02){
//		printf("未读取到到起始位0x02\n");
		return false;
	}
	//读取帧长度
	ReadFile(hCom,frame_length,2,&wCount,NULL);

	//读取帧类型
	ReadFile(hCom, &frame_type, 1,&wCount,NULL);
	frame_receive.set_type(frame_type);

	//读取帧
	ReadFile(hCom, frame_receive.getFrame() + 5, frame_receive.getLength() -5,&wCount,NULL);

	return true;
}