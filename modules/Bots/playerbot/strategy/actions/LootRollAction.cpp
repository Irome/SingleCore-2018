#include "botpch.h"
#include "../../playerbot.h"
#include "LootRollAction.h"

#include "Group.h"

using namespace ai;

bool LootRollAction::Execute(Event event)
{
	Player *bot = QueryItemUsageAction::ai->GetBot();

	WorldPacket p(event.getPacket()); //WorldPacket packet for CMSG_LOOT_ROLL, (8+4+1)
	uint64 guid;
	uint32 slot;
	uint8 rollType;
	p.rpos(0); //reset packet pointer
	p >> guid; //guid of the item rolled
	p >> slot; //number of players invited to roll
	p >> rollType; //need,greed or pass on roll

	Group* group = bot->GetGroup();
	if (!group)
		return false;

	RollVote vote = RollVote::PASS;
	for (vector<Roll*>::iterator i = group->GetRolls().begin(); i != group->GetRolls().end(); ++i)
	{
		if ((*i)->isValid() && (*i)->itemGUID == guid && (*i)->itemSlot == slot)
		{
			uint32 itemId = (*i)->itemid;
			ItemTemplate const *proto = sObjectMgr->GetItemTemplate(itemId);
			if (!proto)
				continue;

			if (IsLootAllowed(itemId, bot->GetPlayerbotAI()))
			{
				vote = RollVote::NEED;
				break;
			}
		}
	}

	switch (group->GetLootMethod())
	{
	case MASTER_LOOT:
	case FREE_FOR_ALL:
		group->CountRollVote(bot->GetGUID(), guid, ROLL_PASS);
		break;
	default:
		group->CountRollVote(bot->GetGUID(), guid, vote);
		break;
	}

	return true;
}
