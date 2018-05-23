#ifndef _StateMachine_H_
#define _StateMachine_H_

#include "State.h"
template<class entity_type>
class StateMachine{
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	//智能体处于的上一个状态的记录
	State<entity_type>* m_pPreviousState;
	//每次FSM被更新时，这个状态逻辑被调用
	State<entity_type>* m_pGlobalState;

public:
	StateMachine(entity_type* owner) :m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}
	void SetCurrentState(State<entity_type>* s){ m_pCurrentState = s; }
	void SetGlobalState(State<entity_type>* s){ m_pCurrentState = s; }
	void SetPreviousState(State<entity_type>* s){ m_pCurrentState = s; }
};
#endif