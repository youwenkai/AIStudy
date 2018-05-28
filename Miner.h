#ifndef _Miner_H_
#define _Miner_H_

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "MinerState.h"
#include "Config.h"
#include "MessageStruct.h"
//the amount of gold a miner must have before he feels comfortable
const int ComfortLevel = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets = 3;
//above this value a miner is thirsty
const int ThirstLevel = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;

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
	Miner(int id) :m_Location(shack),
		m_iGoldCarried(0),
		m_iMoneyInBank(0),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)
	{
		//建立stateMachine
		m_pStateMachine = new StateMachine<Miner>(this);
		m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
		//m_pStateMachine->SetGlobalState(EnterMineAndDigForNugget::Instance());
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

	bool PocketsFull()const{
		if (m_iGoldCarried > MaxNuggets){
			return true;
		}
		return false;
	}
	bool Thirsty()const{
		if (m_iThirst > TirednessThreshold){
			return true;
		}
		return false;
	}
	void IncreaseThirsty(){ m_iThirst++; }
	void AddToWealth(int num){ m_iMoneyInBank += num; }
	int Wealth()const{ return m_iMoneyInBank; }

	int GoldCarried() const{ return m_iGoldCarried; }
	void setGoldCarried(int num){ m_iGoldCarried = num; }

	bool ComfortWealth() const{
		if (m_iMoneyInBank >= ComfortLevel){
			return true;
		}
		return false;
	}

	bool Fatigued()const
	{
		if (m_iFatigue > TirednessThreshold)
		{
			return true;
		}

		return false;
	}
	void DecreaseFatigue(){ m_iFatigue--; }

	void BuyAndDrinkAWhiskey(){ m_iThirst = 0; m_iMoneyInBank -= 2; }

	bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif