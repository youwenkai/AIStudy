#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "time.h"

void MessageDispatcher::DisCharge(BaseGameEntity* pReceiver, const Telegram& msg){
}
MessageDispatcher* MessageDispatcher::Instance(){
	static MessageDispatcher instance;
	return &instance;
}
void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo){
	BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(receiver);
	//创建一个telegram
	Telegram telegram(delay, sender, receiver, msg, ExtraInfo);
	//如果不存在延迟，立即发送telegram
	if (delay <= 0.0){
		//发送telegram到接收器
		DisCharge(pReceiver, telegram);
	}
	else{
		//获取当前时间戳
		double CurrentTime = (double)(time(NULL));
		telegram.DispatchTime = CurrentTime + delay;
		PriorityQ.insert(telegram);
	}
}
void MessageDispatcher::DispatchDelayedMessages(){
	//首先得到当前的时间
	double CurrentTime = (double)(time(NULL));
	//查看队列中是否有telegram需要发送，从队列的前端移除所有的已经过去的telegram
	while ((PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(PriorityQ.begin()->DispatchTime > 0))
	{
		//从队列的前面读telegram
		Telegram telegram = *PriorityQ.begin();
		//找到接受者
		BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(telegram.Receiver);
		//发送telegram到接收者
		DisCharge(pReceiver, telegram);
		//并且从队列中移除它
		PriorityQ.erase(PriorityQ.begin());
	}
}

