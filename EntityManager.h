#ifndef _EntityManager_H_
#define _EntityManager_H_

#include "map"
#include "BaseGameEntity.h"



#define EntityMgr EntityManager::Instance()
class EntityManager{
private:
	//存储实体
	typedef std::map<int, BaseGameEntity*> EntityMap;

private:
	//促进更快的寻找存储在std::map中的实体，其中指向实体的指针是利用
	//实体的识别数值来交叉参考的
	EntityMap m_EntityMap;
	EntityManager(){}
	//拷贝ctor和分配应该是私有的
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
public:
	static EntityManager* Instance();
	//该方法存储了一个指向实体的指针在std::vertor中
	//m_Entities在索引位置上由实体的ID显示
	void RegisterEntity(BaseGameEntity* NewEntity);
	//给出ID作为一个作为一个参数，返回一个指向实体的指正
	BaseGameEntity* GetEntityFromID(int id)const;
	//改方法从列表中移除实体
	void RemoveEntity(BaseGameEntity* pEntity);
};



#endif