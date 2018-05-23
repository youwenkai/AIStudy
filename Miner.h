#ifndef _Miner_H_
#define _Miner_H_

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "MinerState.h"
#include "Config.h"
class Miner :public BaseGameEntity{
private:
	//指向一个stateMachine实例的指针
	StateMachine<Miner> * m_pStateMachine;
	//矿工当前所处的位置
	locationType m_Location;
	//矿工的包中装了多少天然金块
	int m_iGoldCarried;
	//矿工在银行存了多少钱
	int m_iMoneyInBank;
	//价值越高，矿工越口渴
	int m_iThirst;
	//价值越高，矿工越累
	int m_iFatigue;

public:
	Miner(int id) :m_Location(shock),
		m_iGoldCarried(0),
		m_iMoneyInBank(0),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)
	{
		//建立stateMachine
		m_pStateMachine = new StateMachine<Miner>(this);
		m_pStateMachine->SetCurrentState(EnterMineAndDigForNugget::Instance());
		m_pStateMachine->SetGlobalState(EnterMineAndDigForNugget::Instance());
	}
	~Miner(){
		delete m_pStateMachine;
		m_pStateMachine = nullptr;
	}
	//这是必须被执行的
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