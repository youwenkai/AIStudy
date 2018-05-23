#ifndef _Miner_H_
#define _Miner_H_

#include "BaseGameEntity.h"
#include "State.h"
#include "Config.h"
class Miner :public BaseGameEntity{
private:
	//ָ��һ��״̬ʵ����ָ��
	State<Miner> * m_pCurrentState;
	//�󹤵�ǰ������λ��
	locationType m_Location;
	//�󹤵İ���װ�˶�����Ȼ���
	int m_iGoldCarried;
	//�������д��˶���Ǯ
	int m_iMoneyInBank;
	//��ֵԽ�ߣ���Խ�ڿ�
	int m_iThirst;
	//��ֵԽ�ߣ���Խ��
	int m_iFatigue;

public:
	Miner(int id);

	//���Ǳ��뱻ִ�е�
	void Update();
	//��������ı䵱ǰ��״̬��һ���µ�״̬
	void ChangeState();

public:
	locationType Location()const{ return m_Location; }

	void ChangeLocation(locationType location){ m_Location = location; }
	
	void AddToGoldCarried(int num){ m_iGoldCarried += num; }

	void IncreaseFatigue(){ m_iFatigue++; }

	bool PocketsFull(){
		if (m_iGoldCarried > 10){
			return true;
		}
		return false;
	}
	bool Thirsty(){
		if (m_iThirst > 5){
			return true;
		}
		return false;
	}
};

#endif