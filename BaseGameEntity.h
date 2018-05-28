#ifndef _BaseGameEntity_H_
#define _BaseGameEntity_H_
#include "MessageStruct.h"

class BaseGameEntity{
private:
	//ÿһ��ʵ�����һ��Ψһ��ʶ������
	int m_id;
	
	static int m_iNextValidId;

	void SetId(int id){m_id = id;};

public:

	BaseGameEntity(int id){ SetId(id); }

	virtual ~BaseGameEntity(){}

	//���е�ʵ�����ִ��һ�����º���
	virtual void Update() = 0;

	int GetId()const{ return m_id; };

	//���е��������ʹ����Ϣ����
	virtual bool HandleMessage(const Telegram& msg) = 0;
};


#endif