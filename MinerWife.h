#ifndef _MinerWife_H_
#define _MinerWife_H_

#include "BaseGameEntity.h"

class MinerWife :public BaseGameEntity{
private:
	MinerWife(int id) :BaseGameEntity(id){};

	bool HandleMessage(const Telegram& msg);
};
#endif