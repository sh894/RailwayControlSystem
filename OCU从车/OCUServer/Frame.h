#pragma once


//1	主控机车注册
#define MSG_MST_LOCO_REG 0x01
#define MSG_MST_LOCO_REG_LEN 27
//2	从控机车注册
#define MSG_SLV_LOCO_REG 0x02
#define MSG_SLV_LOCO_REG_LEN 9
//3	注册回复
//注册失败
#define MSG_REG_REPLY 0x81
#define MSG_REG_REPLY_LEN 10
//注册成功
#define MSG_OCU_IP_REPLY 0x76
#define MSG_OCU_IP_REPLY_LEN 29

//4	机车注销
#define MSG_LOG_OFF 0x12
#define MSG_LOG_OFF_LEN 9

//6	注销回复
#define MSG_LOGOFF_REPLY 0x92
#define MSG_LOGOFF_REPLY_LEN 10

//7 同步控制数据
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

