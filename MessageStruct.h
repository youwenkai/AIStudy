#ifndef _MessageStruct_H_
#define _MessageStruct_H_

#include <iostream>
#include <math.h>

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

	Telegram() :DispatchTime(-1),
		Sender(-1),
		Receiver(-1),
		Msg(-1)
	{}
	Telegram(double time,
		int sender,
		int receiver,
		int msg,
		void* info = NULL) :DispatchTime(time),
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		ExtraInfo(info)
	{}

};
const double SmallestDelay = 0.25;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay) &&
		(t1.Sender == t2.Sender) &&
		(t1.Receiver == t2.Receiver) &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
		<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

	return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram 
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}




#endif