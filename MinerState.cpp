#include "MinerState.h"
#include "Config.h"
#include  "iostream"

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance(){
	static EnterMineAndDigForNugget* insance;
	return insance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner){
	//����󹤻�û�д��ڽ���У�������ı�λ�õ������
	if (pMiner->Location() != goldmine)
	{
		std::cout << "\n" << "" << ":" << "������";
		pMiner->ChangeLocation(goldmine);
	}
}
void EnterMineAndDigForNugget::Execute(Miner* pMiner){
	//���ھ�Ѱ�ҽ���ֱ���õ��Ľ��Ӵﵽ�����Ȼ�����
	//������ھ�ʱ�е��ڿ��ˣ�����ֹͣ�������Ҹı�״̬ȥ�ưɺ�һ����ʿ��

	pMiner->AddToGoldCarried(1);
	//�ھ���һ����ѵĹ���
	pMiner->IncreaseFatigue();

	std::cout << "\n" << "" << ":" << "���һ����";

	if (pMiner->PocketsFull()){
		pMiner->ChangeState();
	}

	if (pMiner->Thirsty()){
		pMiner->ChangeState();
	}
}
void EnterMineAndDigForNugget::Exit(Miner* pMiner){
	std::cout << "\n" << "" << ":"
		<< "���㹻�Ľ�飬�����뿪�ˣ�";
}
