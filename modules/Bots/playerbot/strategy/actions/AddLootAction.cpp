#include "botpch.h"
#include "../../playerbot.h"
#include "AddLootAction.h"

#include "../../LootObjectStack.h"
#include "../../PlayerbotAIConfig.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

using namespace ai;
using namespace Trinity;

using namespace ai;

bool AddLootAction::Execute(Event event)
{
    uint64 guid = event.getObject();
    if (!guid)
        return false;

    return AI_VALUE(LootObjectStack*, "available loot")->Add(guid);
}

bool AddAllLootAction::Execute(Event event)
{
    bool added = false;

    list<uint64> gos = context->GetValue<list<uint64> >("nearest game objects")->Get();
    for (list<uint64>::iterator i = gos.begin(); i != gos.end(); i++)
        added |= AddLoot(*i);

    list<uint64> corpses = context->GetValue<list<uint64> >("nearest corpses")->Get();
    for (list<uint64>::iterator i = corpses.begin(); i != corpses.end(); i++)
        added |= AddLoot(*i);

    return added;
}

bool AddLootAction::isUseful()
{
    return AI_VALUE(uint8, "bag space") < 80;
}

bool AddAllLootAction::isUseful()
{
    return AI_VALUE(uint8, "bag space") < 80;
}

bool AddAllLootAction::AddLoot(uint64 guid)
{
    return AI_VALUE(LootObjectStack*, "available loot")->Add(guid);
}

bool AddGatheringLootAction::AddLoot(uint64 guid)
{
    LootObject loot(bot, guid);

    WorldObject *wo = loot.GetWorldObject(bot);
    if (loot.IsEmpty() || !wo)
        return false;

    if (!bot->IsWithinLOSInMap(wo))
        return false;

    if (loot.skillId == SKILL_NONE)
        return false;

    if (!loot.IsLootPossible(bot))
        return false;

    if (bot->GetDistance2d(wo) > sPlayerbotAIConfig.tooCloseDistance)
    {
        list<Unit*> targets;
		AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, bot, sPlayerbotAIConfig.grindDistance);
		UnitListSearcher<AnyUnfriendlyUnitInObjectRangeCheck> searcher(bot, targets, u_check);
		bot->VisitNearbyObject(bot->GetMap()->GetVisibilityRange(), searcher);

        if (!targets.empty())
        {
            ostringstream out;
            out << "Kill that " << targets.front()->GetName() << " so I can loot freely";
            ai->TellMaster(out.str());
            return false;
        }
    }

    return AddAllLootAction::AddLoot(guid);
}
