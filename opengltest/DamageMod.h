#include "Item.h"

class I_DamageMod : public Item
{
public:
	I_DamageMod(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};