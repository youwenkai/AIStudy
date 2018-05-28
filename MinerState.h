#ifndef _MinerState_H_
#define _MinerState_H_

#include "State.h"
class Miner;

class EnterMineAndDigForNugget : public State<Miner>{
private:
	EnterMineAndDigForNugget(){};
	EnterMineAndDigForNugget(EnterMineAndDigForNugget&){};
	EnterMineAndDigForNugget& operator=(EnterMineAndDigForNugget&){};
public:
	static EnterMineAndDigForNugget* Instance();
	virtual void Enter(Miner* pMiner);
	virtual void Execute(Miner* pMiner);
	virtual void Exit(Miner* pMiner);
	virtual bool OnMessage(Miner* pMiner, const Telegram& telegram);
};

class VisitBankAndDepositGold :public State<Miner>{
private:
	VisitBankAndDepositGold(){};
	VisitBankAndDepositGold(VisitBankAndDepositGold&){};
	VisitBankAndDepositGold& operator=(VisitBankAndDepositGold&){};
public:
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Miner* pMiner);
	virtual void Execute(Miner* pMiner);
	virtual void Exit(Miner* pMiner);
	virtual bool OnMessage(Miner* pMiner, const Telegram& telegram);
};


class GoHomeAndSleepTilRested :public State<Miner>{
private:
	GoHomeAndSleepTilRested(){};
	GoHomeAndSleepTilRested(GoHomeAndSleepTilRested&){};
	GoHomeAndSleepTilRested& operator=(GoHomeAndSleepTilRested&){};
public:
	static GoHomeAndSleepTilRested* Instance();

	virtual void Enter(Miner* pMiner);
	virtual void Execute(Miner* pMiner);
	virtual void Exit(Miner* pMiner);
	virtual bool OnMessage(Miner* pMiner, const Telegram& telegram);
};

class QuenchThirst :public State<Miner>{
private:
	QuenchThirst(){};
	QuenchThirst(QuenchThirst&){};
	QuenchThirst& operator=(QuenchThirst&){};
public:
	static QuenchThirst* Instance();

	virtual void Enter(Miner* pMiner);
	virtual void Execute(Miner* pMiner);
	virtual void Exit(Miner* pMiner);
	virtual bool OnMessage(Miner* pMiner, const Telegram& telegram);
};

#endif