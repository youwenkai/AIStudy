#include "MinerState.h"
#include "Config.h"
#include "Miner.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "iostream"


//======================================�ڿ�״̬=====================================//
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance(){
	static EnterMineAndDigForNugget insance;
	return &insance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner){
	//����󹤻�û�д��ڽ���У�������ı�λ�õ������
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "������";
		pMiner->ChangeLocation(goldmine);
	}
}
void EnterMineAndDigForNugget::Execute(Miner* pMiner){
	//���ھ�Ѱ�ҽ���ֱ���õ��Ľ��Ӵﵽ�����Ȼ�����
	//������ھ�ʱ�е��ڿ��ˣ�����ֹͣ�������Ҹı�״̬ȥ�ưɺ�һ����ʿ��

	pMiner->AddToGoldCarried(1);
	//�ھ���һ����ѵĹ���
	pMiner->IncreaseFatigue();
	pMiner->IncreaseThirsty();

	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "���һ����";
	//���������㹻�ˣ���ȥ���д�����
	if (pMiner->PocketsFull()){
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}
	//����ڿʣ���ȥ��һ��
	if (pMiner->Thirsty()){
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
	}
}
void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "���㹻�Ľ�飬�����뿪�ˣ�";
}
bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}
//======================================��Ǯ״̬=====================================//
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance(){
	static VisitBankAndDepositGold instance;
	return &instance;
}
void VisitBankAndDepositGold::Enter(Miner* pMiner){
	if (pMiner->Location() != bank){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "�������У��ѽ�������";
		pMiner->ChangeLocation(bank);
	}
}
void VisitBankAndDepositGold::Execute(Miner* pMiner){
	pMiner->AddToWealth(pMiner->GoldCarried());
	pMiner->setGoldCarried(0);

	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "�洢��飬�ܹ�������" << pMiner->Wealth();

	if (pMiner->ComfortWealth()){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "���㹻�Ľ���ˣ����Իؼ���Ϣ��";

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	else{//�����ڽ��
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}
void VisitBankAndDepositGold::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "�뿪����!";
}
bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}
//======================================�ؼ�״̬=====================================//
GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance(){
	static GoHomeAndSleepTilRested instance;
	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner){
	if (pMiner->Location() != shack){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "�߻ؼң�";
		pMiner->ChangeLocation(shack);

		//������֪���һؼ���
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pMiner->GetId(), ent_Elsa, Msg_HiHoneyImHome, NO_ADDITIONAL_INFO);
	}
}
void GoHomeAndSleepTilRested::Execute(Miner* pMiner){
	if (!pMiner->Fatigued()){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": "<< "�����˷�ʱ�䣬�����ڽ����Ǯ��";
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		pMiner->DecreaseFatigue();
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "��������ZZZZ... ";
	}
}
void GoHomeAndSleepTilRested::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "�뿪���ݣ�";
}
bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}

//======================================�ڿ�״̬=====================================//
QuenchThirst* QuenchThirst::Instance(){
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner){
	if (pMiner->Location() != saloon){
		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ":" << "��һ����ʿ�ɽ��ʣ�";
		pMiner->ChangeLocation(saloon);
	}
}
void QuenchThirst::Execute(Miner* pMiner){
	if (pMiner->Thirsty()){
		pMiner->BuyAndDrinkAWhiskey();


		std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "�ú�...";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else{
		std::cout << "\nERROR!\nERROR!\nERROR!";
	}
}
void QuenchThirst::Exit(Miner* pMiner){
	std::cout << "\n" << GetNameOfEntity(pMiner->GetId()) << ": " << "�뿪�ư�...";
}
bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& telegram){
	return false;
}