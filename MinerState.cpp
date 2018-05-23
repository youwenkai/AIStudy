#include "MinerState.h"
#include "Config.h"
#include  "iostream"

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance(){
	static EnterMineAndDigForNugget* insance;
	return insance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner){
	//如果矿工还没有处在金矿中，他必须改变位置到金矿中
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << "" << ":" << "走向金矿";
		pMiner->ChangeLocation(goldmine);
	}
}
void EnterMineAndDigForNugget::Execute(Miner* pMiner){
	//矿工挖掘寻找金子直到拿到的金子达到最大天然金块数
	//如果在挖掘时感到口渴了，他会停止工作并且改变状态去酒吧喝一杯威士忌

	pMiner->AddToGoldCarried(1);
	//挖掘是一项艰难的工作
	pMiner->IncreaseFatigue();

	std::cout << "\n" << "" << ":" << "获得一块金块";

	if (pMiner->PocketsFull()){
		pMiner->ChangeState();
	}

	if (pMiner->Thirsty()){
		pMiner->ChangeState();
	}
}
void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	std::cout << "\n" << "" << ":"
		<< "有足够的金块，可以离开了！";
}
