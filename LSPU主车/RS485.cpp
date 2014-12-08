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
	hCom=CreateFile(_T("COM3"),//COM1��
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
	TimeOuts.ReadTotalTimeoutMultiplier=0; //��ʱ��ϵ��
	TimeOuts.ReadTotalTimeoutConstant=500;//��ʱ�䳣��
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
	std::cout<<"���ڳ�ʼ�����"<<std::endl;
	return TRUE;
}

bool RS485::send(frame &frm){
	DWORD dwBytesWrite=frm.getLength();
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,frm.getFrame(),dwBytesWrite,&dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		std::cout<<"д����ʧ��"<<std::endl;
		return false;
	}
	return true;
}

bool RS485::receive(frame *frame_receive){

	int flag = 0;
	//��ȡ���ֽ���
	DWORD wCount;
	//��ȡ״̬
	int bReadStat = 0;
	char *byte_buf = new char[100];
	char frame_type = 0;
	char *pbeg = NULL;

	bReadStat =	ReadFile(hCom,byte_buf,99,&wCount,NULL);
	
	if (!bReadStat)
	{
		return false;
	}

	for (pbeg = byte_buf; pbeg < byte_buf + wCount; ++pbeg)
	{
		if (*pbeg == 0x10)
		{
			break;
		}
	}

	//δ��ȡ��ʼλ
	if (pbeg == byte_buf + wCount)
	{
		return false;
	}

	if (pbeg[1] != 0x02)
	{
		return false;
	}

	frame_receive->set_type(pbeg[4]);
	frame_receive->setFrame(pbeg);
	return true;
}