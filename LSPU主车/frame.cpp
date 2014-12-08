#include "StdAfx.h"
#include "frame.h"

frame::frame(void){
	this->frame_type = 0;
	this->frame_content = NULL;
	this->length = 0;
}
frame::~frame(void){}

frame::frame(char frame_type){
	this->frame_content = ini_frame(frame_type);
}

bool frame::set_type(char frame_type){
	this->frame_content = ini_frame(frame_type);
	return true;
}

char* frame::ini_frame(char frame_type){
	char *frame_buf = NULL;
	length = 0;
	this->frame_type = frame_type;
	switch(frame_type){
	case MSG_MST_LOCO_REG://
		frame_buf = new char[MSG_MST_LOCO_REG_LEN];
		memset(frame_buf,0,MSG_MST_LOCO_REG_LEN);
		length = MSG_MST_LOCO_REG_LEN;
		break;
	case MSG_SLV_LOCO_REG:
		frame_buf = new char[MSG_SLV_LOCO_REG_LEN];
		memset(frame_buf,0,MSG_SLV_LOCO_REG_LEN);
		length = MSG_SLV_LOCO_REG_LEN;
		break;
	case MSG_REG_REPLY:
		frame_buf = new char[MSG_REG_REPLY_LEN];
		memset(frame_buf,0,MSG_REG_REPLY_LEN);
		length = MSG_REG_REPLY_LEN;
	case MSG_LOG_OFF:
		frame_buf = new char[MSG_LOG_OFF_LEN];
		memset(frame_buf,0,MSG_LOG_OFF_LEN);
		length = MSG_LOG_OFF_LEN;
		break;
	case MSG_LOGOFF_REPLY:
		frame_buf = new char[MSG_LOGOFF_REPLY_LEN];
		memset(frame_buf,0,MSG_LOGOFF_REPLY_LEN);
		length = MSG_LOGOFF_REPLY_LEN;
		break;
	case MSG_CTL:
		frame_buf =new char[MSG_CTL_LEN];
		memset(frame_buf,0,MSG_CTL_LEN);
		length = MSG_CTL_LEN;
		break;
	case MSG_OCU_IP_REPLY:
		frame_buf = new char[MSG_OCU_IP_REPLY];
		memset(frame_buf,0,MSG_OCU_IP_REPLY_LEN);
		length = MSG_OCU_IP_REPLY_LEN;
	default:
		break;
	}

	if (frame_buf != NULL)
	{
		frame_buf[0] = 0x10;
		frame_buf[1] = 0x02;
		memcpy(frame_buf + 2,&length ,sizeof(short));
		frame_buf[4] = frame_type;
	}
	return frame_buf;
}


char *frame::getFrame(){
	return this->frame_content;
}

short frame::getLength(){
	if (frame_content != NULL)
	{
		memcpy(&length, frame_content + 2, sizeof(short));
		return this->length;
	}
	else{
		return 0;
	}

}

char frame::getFrameType(){
	if (this->frame_content!=NULL)
	{
		return this->frame_type;
	}
	else 
		return NULL;
}

void frame::setFrame(char *fr){
	if (fr == NULL)
	{
		return;
	}

	if (fr[4] != this->frame_type)
	{
		return;
	}
	memcpy(this->frame_content,fr,this->getLength());
}

void frame::printFrame(){

	for (int i = 0; i < length; i++)
	{
		printf("%d",this->getFrame()[i]);
	}

	printf("/n");
}