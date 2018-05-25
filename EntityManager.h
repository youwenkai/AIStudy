#ifndef _EntityManager_H_
#define _EntityManager_H_

#include "map"
#include "BaseGameEntity.h"



#define EntityMgr EntityManager::Instance()
class EntityManager{
private:
	//�洢ʵ��
	typedef std::map<int, BaseGameEntity*> EntityMap;

private:
	//�ٽ������Ѱ�Ҵ洢��std::map�е�ʵ�壬����ָ��ʵ���ָ��������
	//ʵ���ʶ����ֵ������ο���
	EntityMap m_EntityMap;
	EntityManager(){}
	//����ctor�ͷ���Ӧ����˽�е�
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
public:
	static EntityManager* Instance();
	//�÷����洢��һ��ָ��ʵ���ָ����std::vertor��
	//m_Entities������λ������ʵ���ID��ʾ
	void RegisterEntity(BaseGameEntity* NewEntity);
	//����ID��Ϊһ����Ϊһ������������һ��ָ��ʵ���ָ��
	BaseGameEntity* GetEntityFromID(int id)const;
	//�ķ������б����Ƴ�ʵ��
	void RemoveEntity(BaseGameEntity* pEntity);
};



#endif