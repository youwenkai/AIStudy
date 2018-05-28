#ifndef _State_H_
#define _State_H_

#include "MessageStruct.h"

template<class entity_type>
class State{
public:
	virtual ~State(){}

	virtual void Enter(entity_type*) = 0;
	virtual void Execute(entity_type*) = 0;
	virtual void Exit(entity_type*) = 0;

	//如果智能体从消息发送器中接收了一条消息执行这个
	virtual bool OnMessage(entity_type*, const Telegram&) = 0;
};

#endif