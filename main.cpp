#include "Miner.h"
#include "Config.h"
#include "EntityManager.h"

#include<Windows.h>
int main(){
	
	Miner* Bob = new Miner(ent_Miner_Bob);
	EntityMgr->RegisterEntity(Bob);


	for (int i = 0; i < 50; i++){
		Bob->GetFSM()->Update();
		Sleep(800);
	}

	system("pause");
	return 0;
}