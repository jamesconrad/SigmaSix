#include "Entity.h"

class I_SpeedMod : public Item
{
public:
	I_SpeedMod(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};