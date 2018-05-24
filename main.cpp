#include "Miner.h"
#include "Config.h"

#include<Windows.h>
int main(){
	
	Miner* miner = new Miner(ent_Miner_Bob);


	for (int i = 0; i < 50; i++){
		miner->GetFSM()->Update();
		Sleep(800);
	}

	system("pause");
	return 0;
}