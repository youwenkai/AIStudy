#ifndef _MessageDispatcher_H_
#define _MessageDispatcher_H_

#include "set"
#include "MessageStruct.h"
#include "BaseGameEntity.h"



const double SEND_MSG_IMMEDIATELY = 0.0f;
const int   NO_ADDITIONAL_INFO = 0;


class MessageDispatcher{
private:
	//一个std::set被用于作为延迟的消息的容器，应为这样的好处是可以自动的排序和避免产生重复
	//按照消息的发送时间给他们排序
	std::set<Telegram> PriorityQ;
	//该方法被DispatchMessage或者DispatchDelayedMessages利用。该方法最新创建的
	//telegram调用接收实体的消息处理成员函数pReceiver
	void DisCharge(BaseGameEntity* pReceiver, const Telegram& msg);
	MessageDispatcher(){}
public:
	static MessageDispatcher* Instance();
	//发送函数
	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);

	//发送任何延迟的消息，该方法每次通过主游戏循环被调用
	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance()
#endif