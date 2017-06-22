#include "botpch.h"
#include "../../playerbot.h"
#include "FollowActions.h"
#include "../../PlayerbotAIConfig.h"
#include "../values/Formations.h"

using namespace ai;


bool FollowAction::Execute(Event event)
{
	Formation* formation = AI_VALUE(Formation*, "formation");
	string target = formation->GetTargetName();
	bool moved = false;
	if (!target.empty())
	{
		moved = Follow(AI_VALUE(Unit*, target));
	}
	else
	{
		WorldLocation loc = formation->GetLocation();
		if (Formation::IsNullLocation(loc) || loc.GetMapId() == -1)
			return false;

		moved = MoveTo(loc.GetMapId(), loc.GetPositionX(), loc.GetPositionY(), loc.GetPositionZ());
	}

	if (moved) ai->SetNextCheckDelay(sPlayerbotAIConfig.reactDelay);
	return moved;
}

bool FollowAction::isUseful()
{
	Formation* formation = AI_VALUE(Formation*, "formation");
	float distance = 0;
	string target = formation->GetTargetName();

	if (!target.empty())
	{
		distance = AI_VALUE2(float, "distance", target);
	}
	else
	{
		WorldLocation loc = formation->GetLocation();
		if (Formation::IsNullLocation(loc) || bot->GetMapId() != loc.GetMapId())
			return false;

		distance = bot->GetDistance(loc.GetPositionX(), loc.GetPositionY(), loc.GetPositionZ());
	}

	return distance > formation->GetMaxDistance() &&
		!AI_VALUE(bool, "can loot");
}

