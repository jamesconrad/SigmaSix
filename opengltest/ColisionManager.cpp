#include "ColisionManager.h"

ColisionManager::ColisionManager()
{
	mapLoader = MapLoader::instance();
	entityManager = EntityManager::instance();
	tileManager = TileManager::instance();
	projectileManager = ProjectileManager::instance();
	tileManager->GetVars(&chunkW, &mapW, chunkVectorPtr);
	chunkVectorPtr = tileManager->GetChunkVectorPtr();
}

void ColisionManager::RebuildColisionMap()
{
	//Attempt #2
	//this time we go chunk by chunk building that chunks colisionMap
	tileManager->GetVars(&chunkW, &mapW, chunkVectorPtr);
	chunkVectorPtr = tileManager->GetChunkVectorPtr();

	colisionMap.clear();
	portalMap.clear();
	RECT tileRect = tileManager->GetTileRect(0, 0);
	std::vector<RECT> initPushBack;
	initPushBack.push_back(tileRect);
	for (int chunkNum = 0, numOfChunks = chunkVectorPtr->size(); chunkNum < numOfChunks; chunkNum++)
	{
		colisionMap.push_back(initPushBack);
		for (int chunkPos = 0, chunkSize = chunkVectorPtr->at(chunkNum).size(); chunkPos < chunkSize; chunkPos++)
		{
			if (chunkVectorPtr->at(chunkNum).at(chunkPos)->GetColision()) //check to see if it is a solid object 
			{
				tileRect = chunkVectorPtr->at(chunkNum).at(chunkPos)->GetRect(); //returns the location of the bullet & tileRect is equated to it
				
				if (chunkVectorPtr->at(chunkNum).at(chunkPos)->IsPortal())
				{
					Portal tmpPort;
					tmpPort.chunkNum = chunkNum;
					tmpPort.colisionPos = colisionMap.at(chunkNum).size();
					tmpPort.pos = tileRect;
					tmpPort.mapTransitionID = chunkVectorPtr->at(chunkNum).at(chunkPos)->GetPortalMapID();
					portalMap.push_back(tmpPort);//why are we pushing back?
				}

				if (colisionMap.at(chunkNum).back().right == tileRect.left && colisionMap.at(chunkNum).back().bottom == tileRect.bottom)
				{//is this where we check if they actually collide? 
					colisionMap.at(chunkNum).back().right = tileRect.right;
				}
				else
				{
					colisionMap.at(chunkNum).push_back(tileRect);
				}
			}
		}
	}
}

void ColisionManager::Update()
{
	projectileVectorPtr = projectileManager->GetProjectileVector();//rederive location incase pushback caused it to move
	RECT entPos;
	for (int entityIter = 0, numOfEnts = entityManager->GetSize(); entityIter < numOfEnts; entityIter++)
	{
		entPos = entityManager->getRectOfID(entityIter);
		int chunkNum = (int)((entPos.bottom / 15) / chunkW) * mapW + (int)((entPos.left / 15) / chunkW);
		
		UpdateChunk(chunkNum - mapW - 1, entityIter);
		UpdateChunk(chunkNum - mapW, entityIter);
		UpdateChunk(chunkNum - mapW + 1, entityIter);

		UpdateChunk(chunkNum - 1, entityIter);
		UpdateChunk(chunkNum, entityIter);
		UpdateChunk(chunkNum + 1, entityIter);

		UpdateChunk(chunkNum + mapW - 1, entityIter);
		UpdateChunk(chunkNum + mapW, entityIter);
		UpdateChunk(chunkNum + mapW + 1, entityIter);
		

		//Attempt #2 Fuck the seperating axis theorm
		for (int projectileIter = projectileVectorPtr->size() - 1; projectileIter >= 0; projectileIter--)
		{
			//check if projectiles are owned by the entity
			if (entityIter == ProjectileManager::instance()->GetOwner(projectileIter))
				break;
			else if (entityIter != 0 && ProjectileManager::instance()->GetOwner(projectileIter) != 0)
				break;
			RECT proj = projectileVectorPtr->at(projectileIter)->GetRect();
			float l = proj.left - entPos.right;
			float r = proj.right - entPos.left;
			float t = proj.bottom - entPos.top;
			float b = proj.top - entPos.bottom;

			if (!(l > 0 || r < 0 || t > 0 || b < 0))
			{
				if (projectileVectorPtr->at(projectileIter)->GetType != -1)
				{
					entityManager->DamageID(entityIter, projectileVectorPtr->at(projectileIter)->GetDamage());
					entityManager->OnHit(ProjectileManager::instance()->GetOwner(projectileIter));
				}
				else if (entityManager->GetType(entityIter) == NEUTRAL)
				{
					Dialog::instance()->Say(entityManager->GetType(entityIter), 1);
				}
				ProjectileManager::instance()->RemoveProjectile(projectileIter);
			}
		}
		//Check for Item pickup if entityiter 0
		if (entityIter == 0)
		{
			for (int i = EntityManager::instance()->droppedItems.size() - 1; i >= 0; i--)
			{
				RECT drop = EntityManager::instance()->droppedItems[i]->pickup;
				float l = drop.left - entPos.right;
				float r = drop.right - entPos.left;
				float t = drop.bottom - entPos.top;
				float b = drop.top - entPos.bottom;

				if (!(l > 0 || r < 0 || t > 0 || b < 0))
				{
					entityManager->GiveItem(entityIter, EntityManager::instance()->droppedItems[i]->itemId);
					EntityManager::instance()->droppedItems.erase(EntityManager::instance()->droppedItems.begin() + i);
					EntityManager::instance()->droppedItems.shrink_to_fit();
				}
			}
		}
	}
}

bool ColisionManager::CheckAxis(RECT entPos, RotatedRectangle rRect, POINT axis)
{
	if (axis.x == 0 && axis.y == 0)
		return false;
	POINT aProj[4], bProj[4];
	//0 = UR
	aProj[0].x = (entPos.right * axis.x + entPos.top * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	aProj[0].y = (entPos.right * axis.x + entPos.top * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;

	bProj[0].x = (rRect.maxX * axis.x + rRect.maxY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	bProj[0].y = (rRect.maxX * axis.x + rRect.maxY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;
	//1 = UL
	aProj[1].x = (entPos.left * axis.x + entPos.top * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	aProj[1].y = (entPos.left * axis.x + entPos.top * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;

	bProj[1].x = (rRect.minX * axis.x + rRect.maxY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	bProj[1].y = (rRect.minX * axis.x + rRect.maxY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;
	//2 = LR
	aProj[2].x = (entPos.right * axis.x + entPos.bottom * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	aProj[2].y = (entPos.right * axis.x + entPos.bottom * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;

	bProj[2].x = (rRect.maxX * axis.x + rRect.minY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	bProj[2].y = (rRect.maxX * axis.x + rRect.minY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;
	//3 = LL
	aProj[3].x = (entPos.left * axis.x + entPos.bottom * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	aProj[3].y = (entPos.left * axis.x + entPos.bottom * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;

	bProj[3].x = (rRect.minX * axis.x + rRect.minY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.x;
	bProj[3].y = (rRect.minX * axis.x + rRect.minY * axis.y) / (axis.x * axis.x + axis.y * axis.y) * axis.y;

	float bMax, bMin, aMax, aMin;
	POINT tmp;

	tmp = GetMinMax(aProj, axis);
	aMax = tmp.x;
	aMin = tmp.y;
	tmp = GetMinMax(bProj, axis);
	bMax = tmp.x;
	bMin = tmp.y;

	if (bMin <= aMax && bMax >= aMin)
		return true;
	else
		return false;
}
//x = max, y = min
POINT ColisionManager::GetMinMax(POINT proj[4], POINT axis)
{
	float max, min, tmp;
	max = min = proj[0].x * axis.x + proj[0].y * axis.y;
	for (int i = 1; i < 4; i++)
	{
		tmp = proj[i].x * axis.x + proj[i].y * axis.y;
		if (tmp > max)
			max = tmp;
		else if (tmp < min)
			min = tmp;
	}
	POINT rVal;
	rVal.x = max;
	rVal.y = min;
	return rVal;	
}

void ColisionManager::UpdateChunk(int chunkNum, int entityIter)
{
	vec2 mtd;
	RECT entPos = entityManager->getRectOfID(entityIter);
	if (chunkNum < 0 || chunkNum > (signed)chunkVectorPtr->size() - 1)
		return;
	for (int i = 0, s = colisionMap.at(chunkNum).size(); i < s; i++)
	{
		float l = colisionMap.at(chunkNum).at(i).left - entPos.right;
		float r = colisionMap.at(chunkNum).at(i).right - entPos.left;
		float t = colisionMap.at(chunkNum).at(i).bottom - entPos.top;
		float b = colisionMap.at(chunkNum).at(i).top - entPos.bottom;

		if (!(l > 0 || r < 0 || t > 0 || b < 0))
		{
			if (entityIter == 0)
			{
				for (int portalIter = 0, numOfPortals = portalMap.size(); portalIter < numOfPortals; portalIter++)
				{
					if (portalMap.at(portalIter).chunkNum == chunkNum && portalMap.at(portalIter).colisionPos == i)
					{
						l = portalMap.at(portalIter).pos.left - entPos.right;
						r = portalMap.at(portalIter).pos.right - entPos.left;
						t = portalMap.at(portalIter).pos.bottom - entPos.top;
						b = portalMap.at(portalIter).pos.top - entPos.bottom;

						if (!(l > 0 || r < 0 || t > 0 || b < 0))
						{
							//Now we get to load the map
							int mapID = portalMap.at(portalIter).mapTransitionID;
							mapLoader->LoadMap(mapID);
							RebuildColisionMap();
							return;
						}
					}
				}
			}


			if (abs(l) < r)
				mtd.x = l;
			
			else
				mtd.x = r;
			if (abs(t) < b)
				mtd.y = t;
			else
				mtd.y = b;

			if (abs(mtd.x) < abs(mtd.y))
				mtd.y = 0;
			else
				mtd.x = 0;

			entityManager->ModPosOfID(entityIter, mtd);			
		}
		//Check for projectile hitting wall
		for (int projIter = projectileVectorPtr->size() - 1; projIter >= 0; projIter--)
		{
			RECT projRect = projectileVectorPtr->at(projIter)->GetRect();
			l = colisionMap.at(chunkNum).at(i).left - projRect.right;
			r = colisionMap.at(chunkNum).at(i).right - projRect.left;
			t = colisionMap.at(chunkNum).at(i).bottom - projRect.top;
			b = colisionMap.at(chunkNum).at(i).top - projRect.bottom;

			if (!(l > 0 || r < 0 || t > 0 || b < 0))
			{
				ProjectileManager::instance()->RemoveProjectile(projIter);
			}
		}
	}
}