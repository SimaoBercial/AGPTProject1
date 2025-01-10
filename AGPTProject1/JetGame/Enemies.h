#ifndef ENEMIES_H
#define ENEMIES_H
 
#include "GameObject.h"

class Enemies : public GameObject{
public:
	virtual ~Enemies() {};

protected:
	int lifePoints;
};

#endif