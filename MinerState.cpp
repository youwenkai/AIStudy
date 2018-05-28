#include "MinerState.h"
#include "Config.h"
#include "Miner.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "iostream"


//======================================挖矿状态=====================================//
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance(){
	static EnterMineAndDigForNugget insance;
	return &insance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner){
	//如果矿工还没有处在金矿中，他必须改变位置到金矿中
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "走向金矿";
		pMiner->ChangeLocation(goldmine);
	}
}
void EnterMineAndDigForNugget::Execute(Miner* pMiner){
	//矿工挖掘寻找金子直到拿到的金子达到最大天然金块数
	//如果在挖掘时感到口渴了，他会停止工作并且改变状态去酒吧喝一杯威士忌

	pMiner->AddToGoldCarried(1);
	//挖掘是一项艰难的工作
	pMiner->IncreaseFatigue();
	pMiner->IncreaseThirsty();

	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "获得一块金块";
	//如果金块数足够了，就去银行存起来
	if (pMiner->PocketsFull()){
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}
	//如果口渴，就去喝一杯
	if (pMiner->Thirsty()){
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}
}
void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "有足够的金块，可以离开了！";
}
bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}
//======================================存钱状态=====================================//
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance(){
	static VisitBankAndDepositGold instance;
	return &instance;
}
void VisitBankAndDepositGold::Enter(Miner* pMiner){
	if (pMiner->Location() != bank){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "走向银行，把金块存起来";
		pMiner->ChangeLocation(bank);
	}
}
void VisitBankAndDepositGold::Execute(Miner* pMiner){
	pMiner->AddToWealth(pMiner->GoldCarried());
	pMiner->setGoldCarried(0);

	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "存储金块，总共数量：" << pMiner->Wealth();

	if (pMiner->ComfortWealth()){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "有足够的金块了，可以回家休息了";

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	else{//继续挖金块
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}
void VisitBankAndDepositGold::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "离开银行!";
}
bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}
//======================================回家状态=====================================//
GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance(){
	static GoHomeAndSleepTilRested instance;
	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner){
	if (pMiner->Location() != shack){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "走回家！";
		pMiner->ChangeLocation(shack);

		//让妻子知道我回家了
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pMiner->GetId(), ent_Elsa, Msg_HiHoneyImHome, NO_ADDITIONAL_INFO);
	}
}
void GoHomeAndSleepTilRested::Execute(Miner* pMiner){
	if (!pMiner->Fatigued()){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": "<< "真是浪费时间，还不挖金块挣钱！";
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		pMiner->DecreaseFatigue();
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "养精蓄锐ZZZZ... ";
	}
}
void GoHomeAndSleepTilRested::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "离开房屋！";
}
bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}

//======================================口渴状态=====================================//
QuenchThirst* QuenchThirst::Instance(){
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner){
	if (pMiner->Location() != saloon){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "来一杯威士忌解解渴！";
		pMiner->ChangeLocation(saloon);
	}
}
void QuenchThirst::Execute(Miner* pMiner){
	if (pMiner->Thirsty()){
		pMiner->BuyAndDrinkAWhiskey();


		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "好喝...";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		std::cout << "\nERROR!\nERROR!\nERROR!";
	}
}
void QuenchThirst::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "离开酒吧...";
}
bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}