#ifndef _Config_H_
#define _Config_H_

#include <string>
enum locationType
{
	shack,
	goldmine,
	bank,
	saloon
};
enum{
	ent_Miner_Bob,

	ent_Elsa
};

inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Miner_Bob:

		return "Miner Bob";

	case ent_Elsa:

		return "Elsa";

	default:

		return "UNKNOWN!";
	}
};

#endif