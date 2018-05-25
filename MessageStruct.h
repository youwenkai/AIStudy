#ifndef _MessageStruct_H_
#define _MessageStruct_H_



struct Telegram
{
	//发送这个telegram的实体
	int		Sender;
	//接收这个telegram的实体
	int		Receiver;
	//信息本身，所在的枚举值都在文件中"MessageTypes.h"
	int		Msg;
	//可以被立即发送或者延迟一个指定数量的时间后发送的消息
	//如果一个延迟是必须，这个域打上时间戳，消息应该在此后时间后被发送
	double	DispatchTime;
	//任何应该伴随消息的额外信息
	void*	ExtraInfo;
};




#endif