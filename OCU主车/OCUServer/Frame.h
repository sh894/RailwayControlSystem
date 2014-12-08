#pragma once


//1	���ػ���ע��
#define MSG_MST_LOCO_REG 0x01
#define MSG_MST_LOCO_REG_LEN 27
//2	�ӿػ���ע��
#define MSG_SLV_LOCO_REG 0x02
#define MSG_SLV_LOCO_REG_LEN 9
//3	ע��ظ�
//ע��ʧ��
#define MSG_REG_REPLY 0x81
#define MSG_REG_REPLY_LEN 10
//ע��ɹ�
#define MSG_OCU_IP_REPLY 0x76
#define MSG_OCU_IP_REPLY_LEN 29

//4	����ע��
#define MSG_LOG_OFF 0x12
#define MSG_LOG_OFF_LEN 9

//6	ע���ظ�
#define MSG_LOGOFF_REPLY 0x92
#define MSG_LOGOFF_REPLY_LEN 10

//7 ͬ����������
#define MSG_CTL 0x06
#define MSG_CTL_LEN 32
class frame
{
public:
	char frame_type;
	char* frame_content;

	frame(void);
	frame(char frame_type);
	~frame(void);
	
	char* getFrame();
	void setFram(char *str);
	
	short getLength();
	bool set_type(char frame_type);
	char getFrameType();
	
protected:
	short length;
	char* ini_frame(char frame_type);
	
};

