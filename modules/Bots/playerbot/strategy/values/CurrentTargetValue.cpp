#include "botpch.h"
#include "../../playerbot.h"
#include "CurrentTargetValue.h"

using namespace ai;

Unit* CurrentTargetValue::Get()
{
	if (selection == 0)
		return NULL;

	Unit* unit = ObjectAccessor::GetUnit(*bot, selection);
	if (unit && !bot->IsWithinLOSInMap(unit))
		return NULL;

	return unit;
}

void CurrentTargetValue::Set(Unit* target)
{
	selection = target ? target->GetGUID() : 0;
}
