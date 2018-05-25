#ifndef _MessageDispatcher_H_
#define _MessageDispatcher_H_

#include "set"
#include "MessageStruct.h"
#include "BaseGameEntity.h"
class MessageDispatcher{
private:
	//һ��std::set��������Ϊ�ӳٵ���Ϣ��������ӦΪ�����ĺô��ǿ����Զ�������ͱ�������ظ�
	//������Ϣ�ķ���ʱ�����������
	std::set<Telegram> PriorityQ;

	void DisCharge(BaseGameEntity* pReceiver, const Telegram& msg);
	MessageDispatcher(){}
public:
	static MessageDispatcher* Instance();
	//���ͺ���
	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);

	//�����κ��ӳٵ���Ϣ���÷���ÿ��ͨ������Ϸѭ��������
	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance()
#endif