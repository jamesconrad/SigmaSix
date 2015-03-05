#include "Item.h"

class I_Shield : public Item
{
public:
	I_Shield(Entity* owner, float cooldown, float procRate);
	void Activate();
	void Update(float dTime);
	void OnFire();
private:
	
};	