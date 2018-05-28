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
	//����һ��telegram
	Telegram telegram(delay, sender, receiver, msg, ExtraInfo);
	//����������ӳ٣���������telegram
	if (delay <= 0.0){
		//����telegram��������
		DisCharge(pReceiver, telegram);
	}
	else{
		//��ȡ��ǰʱ���
		double CurrentTime = (double)(time(NULL));
		telegram.DispatchTime = CurrentTime + delay;
		PriorityQ.insert(telegram);
	}
}
void MessageDispatcher::DispatchDelayedMessages(){
	//���ȵõ���ǰ��ʱ��
	double CurrentTime = (double)(time(NULL));
	//�鿴�������Ƿ���telegram��Ҫ���ͣ��Ӷ��е�ǰ���Ƴ����е��Ѿ���ȥ��telegram
	while ((PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(PriorityQ.begin()->DispatchTime > 0))
	{
		//�Ӷ��е�ǰ���telegram
		Telegram telegram = *PriorityQ.begin();
		//�ҵ�������
		BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(telegram.Receiver);
		//����telegram��������
		DisCharge(pReceiver, telegram);
		//���ҴӶ������Ƴ���
		PriorityQ.erase(PriorityQ.begin());
	}
}

