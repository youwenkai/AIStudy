#ifndef _StateMachine_H_
#define _StateMachine_H_
#include < assert.h>
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
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr)
	{}
	void SetCurrentState(State<entity_type>* s){ m_pCurrentState = s; }
	void SetGlobalState(State<entity_type>* s){ m_pCurrentState = s; }
	void SetPreviousState(State<entity_type>* s){ m_pCurrentState = s; }
	
	//调用这个来更新FSM
	void Update()const{
		//如果一个全局状态存在，调用他的执行方法
		if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
		//对当前的状态相同
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}
	//改变到一个新状态
	void ChangeState(State<entity_type>* pNewState){
		assert(pNewState && "<StateMachine::ChangeState>:trying to change a null state");
		m_pPreviousState = m_pCurrentState;

		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(m_pOwner);
	}

	//改变状态回到前一个状态
	void ReverToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	State<entity_type>* CurrentState() const{ return m_pCurrentState; }
	State<entity_type>* GlobalState() const{ return m_pGlobalState; }
	State<entity_type>* PreviousState() const{ return m_pPreviousState; }

	//如果当前的状态类型等于作为指正传递的类的类型，返回true
	bool isInState(const State<entity_type>& st)const;

	bool HandleMessage(const Telegram& msg)const{
		//首先看看当前的状态是否是有效的并且可以处理消息
		if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg)){
			return true;
		}
		//如果不是，且如果一个全局状态被执行，发送消息给全局状态
		if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg)){
			return true;
		}
		return false;
	}
};
#endif