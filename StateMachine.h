#ifndef _StateMachine_H_
#define _StateMachine_H_
#include < assert.h>
#include "State.h"
 
template<class entity_type>
class StateMachine{
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	//�����崦�ڵ���һ��״̬�ļ�¼
	State<entity_type>* m_pPreviousState;
	//ÿ��FSM������ʱ�����״̬�߼�������
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
	
	//�������������FSM
	void Update()const{
		//���һ��ȫ��״̬���ڣ���������ִ�з���
		if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
		//�Ե�ǰ��״̬��ͬ
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}
	//�ı䵽һ����״̬
	void ChangeState(State<entity_type>* pNewState){
		assert(pNewState && "<StateMachine::ChangeState>:trying to change a null state");
		m_pPreviousState = m_pCurrentState;

		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(m_pOwner);
	}

	//�ı�״̬�ص�ǰһ��״̬
	void ReverToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	State<entity_type>* CurrentState() const{ return m_pCurrentState; }
	State<entity_type>* GlobalState() const{ return m_pGlobalState; }
	State<entity_type>* PreviousState() const{ return m_pPreviousState; }

	//�����ǰ��״̬���͵�����Ϊָ�����ݵ�������ͣ�����true
	bool isInState(const State<entity_type>& st)const;

	bool HandleMessage(const Telegram& msg)const{
		//���ȿ�����ǰ��״̬�Ƿ�����Ч�Ĳ��ҿ��Դ�����Ϣ
		if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg)){
			return true;
		}
		//������ǣ������һ��ȫ��״̬��ִ�У�������Ϣ��ȫ��״̬
		if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg)){
			return true;
		}
		return false;
	}
};
#endif