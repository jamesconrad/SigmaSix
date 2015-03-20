#include "Entity.h"

class I_MaxHealthMod : public Item
{
public:
	I_MaxHealthMod(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};