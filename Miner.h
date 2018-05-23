#ifndef _Miner_H_
#define _Miner_H_

#include "BaseGameEntity.h"
#include "State.h"
#include "Config.h"
class Miner :public BaseGameEntity{
private:
	//指向一个状态实例的指针
	State<Miner> * m_pCurrentState;
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
	Miner(int id);

	//这是必须被执行的
	void Update();
	//这个方法改变当前的状态到一个新的状态
	void ChangeState();

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