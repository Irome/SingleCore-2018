#include "botpch.h"
#include "../../playerbot.h"
#include "GreetAction.h"

#include "../../PlayerbotAIConfig.h"

#include "Unit.h"

using namespace ai;

GreetAction::GreetAction(PlayerbotAI* ai) : Action(ai, "greet")
{
}

bool GreetAction::Execute(Event event)
{
	uint64 guid = AI_VALUE(uint64, "new player nearby");
	Player* player = ObjectAccessor::FindPlayer(guid);
	if (!player) return false;

	if (!bot->isInFront(player, M_PI / 3.0f) && !bot->IsTaxi())
	{
		bot->SetFacingToObject(player);
		return true;
	}

	bot->SetSelection(guid);
	bot->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
	ai->PlaySound(TEXT_EMOTE_HELLO);

	Unit* oldSel = bot->GetSelectedUnit();
	if (oldSel)
	{
		bot->SetSelection(oldSel->GetGUID());
	}

	set<uint64>& alreadySeenPlayers = ai->GetAiObjectContext()->GetValue<set<uint64>& >("already seen players")->Get();
	alreadySeenPlayers.insert(guid);
	return true;
}
