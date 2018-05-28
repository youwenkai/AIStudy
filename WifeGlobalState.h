#ifndef _WifeGlobalState_H_
#define _WifeGlobalState_H_

#include "State.h"
class MinerWife;
class WifeGlobalState : public State<MinerWife>{
private:
	WifeGlobalState(){};
	WifeGlobalState(WifeGlobalState&){};
	WifeGlobalState& operator=(WifeGlobalState&){};
public:
	static WifeGlobalState* Instance();
	virtual void Enter(MinerWife* pMiner);
	virtual void Execute(MinerWife* pMiner);
	virtual void Exit(MinerWife* pMiner);
	virtual bool OnMessage(MinerWife* pMiner, const Telegram& telegram);
};


#endif