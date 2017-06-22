#include "botpch.h"
#include "../../playerbot.h"
#include "AttackersValue.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

#include "Group.h"

using namespace ai;
using namespace Trinity;

list<uint64> AttackersValue::Calculate()
{
	set<Unit*> targets;

	AddAttackersOf(bot, targets);

	Group* group = bot->GetGroup();
	if (group)
		AddAttackersOf(group, targets);

	RemoveNonThreating(targets);

	list<uint64> result;
	for (set<Unit*>::iterator i = targets.begin(); i != targets.end(); i++)
		result.push_back((*i)->GetGUID());

	if (bot->duel && bot->duel->opponent)
		result.push_back(bot->duel->opponent->GetGUID());

	return result;
}

void AttackersValue::AddAttackersOf(Group* group, set<Unit*>& targets)
{
	Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
	for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
	{
		Player *member = ObjectAccessor::FindPlayer(itr->guid);
		if (!member || !member->IsAlive() || member == bot)
			continue;

		AddAttackersOf(member, targets);
	}
}

void AttackersValue::AddAttackersOf(Player* player, set<Unit*>& targets)
{
	if (player->IsBeingTeleported())
		return;

	list<Unit*> units;

	AnyUnfriendlyUnitInObjectRangeCheck u_check(player, player, sPlayerbotAIConfig.sightDistance);
	UnitListSearcher<AnyUnfriendlyUnitInObjectRangeCheck> searcher(player, units, u_check);
	bot->VisitNearbyObject(bot->GetMap()->GetVisibilityRange(), searcher);

	for (list<Unit*>::iterator i = units.begin(); i != units.end(); i++)
		targets.insert(*i);
}

void AttackersValue::RemoveNonThreating(set<Unit*>& targets)
{
	for (set<Unit *>::iterator tIter = targets.begin(); tIter != targets.end();)
	{
		Unit* unit = *tIter;
		if (!bot->IsWithinLOSInMap(unit) || bot->GetMapId() != unit->GetMapId() || !hasRealThreat(unit))
		{
			set<Unit *>::iterator tIter2 = tIter;
			++tIter;
			targets.erase(tIter2);
		}
		else
			++tIter;
	}
}

bool AttackersValue::hasRealThreat(Unit *attacker)
{
	bool isPlayer = false;
	Player* checkPlayer = (Player*)attacker;
	if (checkPlayer)
	{
		isPlayer = true;
	}
	return attacker &&
		attacker->IsInWorld() &&
		attacker->IsAlive() &&
		!attacker->IsPolymorphed() &&
		!attacker->isInRoots() &&
		!attacker->IsFriendlyTo(bot) &&
		(attacker->getThreatManager().getCurrentVictim() || isPlayer);
}