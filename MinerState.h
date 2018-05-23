#ifndef _MinerState_H_
#define _MinerState_H_

#include "State.h"
#include "Miner.h"

class EnterMineAndDigForNugget : public State<Miner>{
private:
	EnterMineAndDigForNugget(){};
public:
	static EnterMineAndDigForNugget* Instance();
	virtual void Enter(Miner* pMiner);
	virtual void Execute(Miner* pMiner);
	virtual void Exit(Miner* pMiner);
}
#endif