#include "botpch.h"
#include "../../playerbot.h"
#include "GossipHelloAction.h"


using namespace ai;

bool GossipHelloAction::Execute(Event event)
{
	uint64 guid = 0;

	WorldPacket &p = event.getPacket();
	if (p.empty())
	{
		Player* master = GetMaster();
		if (master)
		{
			Unit* masterSelectedUnit = master->GetSelectedUnit();
			if (masterSelectedUnit)
			{
				guid = masterSelectedUnit->GetGUID();
			}			
		}
	}
	else
	{
		p.rpos(0);
		p >> guid;
	}

	if (!guid)
		return false;

	Creature *pCreature = bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
	if (!pCreature)
	{
		sLog->outStaticDebug("[PlayerbotMgr]: HandleMasterIncomingPacket - Received  CMSG_GOSSIP_HELLO %d not found or you can't interact with him.", guid);
		return false;
	}

	GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr->GetGossipMenuItemsMapBounds(pCreature->GetCreatureTemplate()->GossipMenuId);
	if (pMenuItemBounds.first == pMenuItemBounds.second)
		return false;

	WorldPacket p1;
	p1 << guid;
	bot->GetSession()->HandleGossipHelloOpcode(p1);
	bot->SetFacingToObject(pCreature);

	ostringstream out; out << "--- " << pCreature->GetName() << " ---";
	ai->TellMasterNoFacing(out.str());

	GossipMenu& menu = bot->PlayerTalkClass->GetGossipMenu();
	unsigned int i = 0, loops = 0;
	set<uint32> alreadyTalked;
	while (i < menu.GetMenuItemCount() && loops++ < 100)
	{
		GossipMenuItem const* item = menu.GetItem(i);
		ai->TellMasterNoFacing(item->Message);

		// EJ ? less than 1000
		if (item->OptionType < GOSSIP_OPTION_MAX && item->OptionType != GOSSIP_OPTION_GOSSIP)
		{
			i++;
			continue;
		}

		WorldPacket p1;
		std::string code;
		p1 << guid << menu.GetMenuId() << i << code;
		bot->GetSession()->HandleGossipSelectOptionOpcode(p1);

		i = 0;
	}

	bot->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
	return true;
}
