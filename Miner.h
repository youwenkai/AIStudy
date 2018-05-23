#ifndef _Miner_H_
#define _Miner_H_

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "MinerState.h"
#include "Config.h"
class Miner :public BaseGameEntity{
private:
	//ָ��һ��stateMachineʵ����ָ��
	StateMachine<Miner> * m_pStateMachine;
	//�󹤵�ǰ������λ��
	locationType m_Location;
	//�󹤵İ���װ�˶�����Ȼ���
	int m_iGoldCarried;
	//�������д��˶���Ǯ
	int m_iMoneyInBank;
	//��ֵԽ�ߣ���Խ�ڿ�
	int m_iThirst;
	//��ֵԽ�ߣ���Խ��
	int m_iFatigue;

public:
	Miner(int id) :m_Location(shock),
		m_iGoldCarried(0),
		m_iMoneyInBank(0),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)
	{
		//����stateMachine
		m_pStateMachine = new StateMachine<Miner>(this);
		m_pStateMachine->SetCurrentState(EnterMineAndDigForNugget::Instance());
		m_pStateMachine->SetGlobalState(EnterMineAndDigForNugget::Instance());
	}
	~Miner(){
		delete m_pStateMachine;
		m_pStateMachine = nullptr;
	}
	//���Ǳ��뱻ִ�е�
	void Update(){
		++m_iThirst;
		m_pStateMachine->Update();
	}

	StateMachine<Miner>* GetFSM()const{ return m_pStateMachine; }
public:
	locationType Location()const{ return m_Location; }

	void ChangeLocation(locationType location){ m_Location = location; }
	
	void AddToGoldCarried(int num){ m_iGoldCarried += num; }

	void IncreaseFatigue(){ m_iFatigue++; }

	bool PocketsFull(){
		if (m_iGoldCarried > 10){
			return true;
		}
		return false;
	}
	bool Thirsty(){
		if (m_iThirst > 5){
			return true;
		}
		return false;
	}
};

#endif