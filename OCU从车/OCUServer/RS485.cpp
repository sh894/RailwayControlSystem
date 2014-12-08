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
	//�򿪴���

	hCom=CreateFile(_T("COM4"),//COM1��
		GENERIC_READ|GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,//���ð�ȫ�����Խṹ��ȱʡֵΪNULL
		OPEN_EXISTING, //�򿪶����Ǵ���
		0, //ͬ����ʽ
		NULL);//�Դ��ڶ��Ըò���������ΪNULL

	if(hCom==(HANDLE)-1)
	{
		std::cout<<"�򿪴���ʧ�ܣ�"<<std::endl;

		return FALSE;
	}


	//���ô���
	SetupComm(hCom,// ͨ���豸�ľ�� 
		100,// ���뻺�����Ĵ�С���ֽ�����
		100); // ����������Ĵ�С���ֽ�����

	COMMTIMEOUTS TimeOuts;//��COMMTIMEOUTS�ṹ���Թ涨��д�����ĳ�ʱ��
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout=MAXWORD; //�������ʱ
	TimeOuts.ReadTotalTimeoutMultiplier=1; //��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutConstant=1;//��ʱ�䳣��
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���


	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier=100;// дʱ��ϵ��
	TimeOuts.WriteTotalTimeoutConstant=500;//дʱ�䳣��
	SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ

	DCB dcb;//DCB�ṹ�����˴��ڵĸ����������
	GetCommState(hCom,&dcb);//���COM�ڵ��豸���ƿ飬�Ӷ������ز�������dcb
	dcb.BaudRate=9600; //������Ϊ9600
	dcb.ByteSize=8; //ÿ���ֽ���8λ
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=TWOSTOPBITS; //����ֹͣλ
	SetCommState(hCom,&dcb);//��������COM�ڵ��豸���ƿ�

	//PurgeComm()������ջ�����
	PurgeComm(hCom,//���ھ��
		PURGE_TXCLEAR|PURGE_RXCLEAR);// ��Ҫ��ɵĲ���

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
		std::cout<<"д����ʧ��"<<std::endl;
		return false;
	}
	return true;
}

bool RS485::receive(frame &frame_receive){

//��ȡ���ֽ���
	DWORD wCount;
	//��ȡ״̬
	int bReadStat = 0;
	char byte_buf = 0;
	char *frame_length = new char[2];
	char frame_type = 0;

//	printf("��ʼ��ȡ\n");
	//��ȡ��ʼλ
	ReadFile(hCom,&byte_buf,1,&wCount,NULL);
	if (byte_buf != 0x10)
	{
//		printf("δ��ȡ����ʼλ0x10\n");
		return false;
	}
	ReadFile(hCom,&byte_buf,1,&wCount,NULL);
	if(byte_buf != 0x02){
//		printf("δ��ȡ������ʼλ0x02\n");
		return false;
	}
	//��ȡ֡����
	ReadFile(hCom,frame_length,2,&wCount,NULL);

	//��ȡ֡����
	ReadFile(hCom, &frame_type, 1,&wCount,NULL);
	frame_receive.set_type(frame_type);

	//��ȡ֡
	ReadFile(hCom, frame_receive.getFrame() + 5, frame_receive.getLength() -5,&wCount,NULL);

	return true;
}