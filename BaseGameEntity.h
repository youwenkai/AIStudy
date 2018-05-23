#ifndef _BaseGameEntity_H_
#define _BaseGameEntity_H_

class BaseGameEntity{
private:
	//每一个实体具有一个唯一的识别数字
	int m_id;
	
	static int m_iNextValidId;

	void SetId(int val);

public:

	BaseGameEntity(int id){ SetId(id); }

	virtual ~BaseGameEntity(){}

	//所有的实体必须执行一个更新函数
	virtual void Update() = 0;

	int GetId()const{ return m_id; };
};


#endif