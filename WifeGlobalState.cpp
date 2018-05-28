#include "WifeGlobalState.h"
#include "MessageTypes.h"
#include "Config.h"
#include "iostream"
#include "time.h"
using namespace std;

WifeGlobalState* WifeGlobalState::Instance(){
	static WifeGlobalState instance;
	return &instance;
}
void WifeGlobalState::Enter(MinerWife* pMiner){

}
void WifeGlobalState::Execute(MinerWife* pMiner){

}
void WifeGlobalState::Exit(MinerWife* pMiner){

}
bool WifeGlobalState::OnMessage(MinerWife* pMiner, const Telegram& telegram){
	switch (telegram.Msg)
	{
	case Msg_HiHoneyImHome:
		cout << "\nMessage handle by" << GetNameOfEntity(pMiner->GetId())
			<< "at time:" << time(NULL);
	default:
		break;
	}
}