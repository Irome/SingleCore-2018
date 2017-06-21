#include "botpch.h"
#include "../../playerbot.h"
#include "SetHomeAction.h"
#include "../../PlayerbotAIConfig.h"


using namespace ai;

bool SetHomeAction::Execute(Event event)
{
    Player* master = ai->GetMaster();
    if (!master)
        return false;
	
	Unit* masterSelectedUnit = master->GetSelectedUnit();	
	if (masterSelectedUnit)
	{
		if (masterSelectedUnit->IsInnkeeper())
		{
			float angle = GetFollowAngle();
			float x = masterSelectedUnit->GetPositionX() + sPlayerbotAIConfig.followDistance * cos(angle);
			float y = masterSelectedUnit->GetPositionY() + sPlayerbotAIConfig.followDistance * sin(angle);
			float z = masterSelectedUnit->GetPositionZ();
			WorldLocation loc(masterSelectedUnit->GetMapId(), x, y, z);
			bot->SetHomebind(loc, masterSelectedUnit->GetAreaId());
			ai->TellMaster("This inn is my new home");
			return true;
		}
	}

    list<uint64> npcs = AI_VALUE(list<uint64>, "nearest npcs");
    for (list<uint64>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
        Creature *unit = bot->GetNPCIfCanInteractWith(*i, UNIT_NPC_FLAG_INNKEEPER);
        if (!unit)
            continue;

        bot->GetSession()->SendBindPoint(unit);
        ai->TellMaster("This inn is my new home");
        return true;
    }

    ai->TellMaster("Can't find any innkeeper around");
    return false;
}
