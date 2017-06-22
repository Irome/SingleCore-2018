#include "botpch.h"
#include "../../playerbot.h"
#include "RepairAllAction.h"


using namespace ai;

bool RepairAllAction::Execute(Event event)
{
	list<uint64> npcs = AI_VALUE(list<uint64>, "nearest npcs");
	for (list<uint64>::iterator i = npcs.begin(); i != npcs.end(); i++)
	{
		Creature *unit = bot->GetNPCIfCanInteractWith(*i, UNIT_NPC_FLAG_REPAIR);
		if (!unit)
			continue;

		if (bot->HasUnitState(UNIT_STATE_DIED))
			bot->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

		bot->SetFacingToObject(unit);
		float discountMod = bot->GetReputationPriceDiscount(unit);
		uint32 totalCost = bot->DurabilityRepairAll(true, discountMod, false);

		ostringstream out;
		out << "Repair: " << chat->formatMoney(totalCost) << " (" << unit->GetName() << ")";
		ai->TellMasterNoFacing(out.str());

		return true;
	}

	ai->TellMaster("Cannot find any npc to repair at");
	return false;
}
