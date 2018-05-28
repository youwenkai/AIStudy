#include "EntityManager.h"

EntityManager* EntityManager::Instance(){
	static EntityManager instance;
	return &instance;
}
void EntityManager::RegisterEntity(BaseGameEntity* NewEntity){

}
BaseGameEntity* EntityManager::GetEntityFromID(int id) const{
	return NULL;
}
void EntityManager::RemoveEntity(BaseGameEntity* pEntity){

}