#include "botpch.h"
#include "../../playerbot.h"
#include "CheckMountStateAction.h"

#include "SpellAuras.h"
#include "SpellAuraEffects.h"

using namespace ai;

uint64 extractGuid(WorldPacket& packet);

bool CheckMountStateAction::Execute(Event event)
{
	Player* master = GetMaster();
	if (!bot->GetGroup() || !master)
		return false;

	if (bot->IsTaxi())
		return false;

	if (master->IsMounted() && !bot->IsMounted())
	{
		return Mount();
	}
	else if (!master->IsMounted() && bot->IsMounted())
	{
		WorldPacket emptyPacket;
		bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
		return true;
	}
	return false;
}

bool CheckMountStateAction::Mount()
{
	Player* master = GetMaster();
	ai->RemoveShapeshift();

	Unit::AuraEffectList const& auras = master->GetAuraEffectsByType(SPELL_AURA_MOUNTED);

	if (auras.empty()) return false;

	const SpellInfo* masterSpell = auras.front()->GetSpellInfo();
	int32 masterSpeed = max(masterSpell->Effects[1].BasePoints, masterSpell->Effects[2].BasePoints);

	map<int32, vector<uint32> > spells;
	for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
	{
		uint32 spellId = itr->first;
		const SpellInfo* pSpellInfo = sSpellMgr->GetSpellInfo(spellId);
		if (itr->second->State == PLAYERSPELL_REMOVED || pSpellInfo->IsPassive())
			continue;

		const SpellEntry* pSpellEntry = sSpellStore.LookupEntry(spellId);
		if (!pSpellEntry || pSpellInfo->Effects[0].ApplyAuraName != SPELL_AURA_MOUNTED)
			continue;

		int32 effect = max(pSpellInfo->Effects[1].BasePoints, pSpellInfo->Effects[2].BasePoints);
		if (effect < masterSpeed)
			continue;

		spells[effect].push_back(spellId);
	}

	for (map<int32, vector<uint32> >::iterator i = spells.begin(); i != spells.end(); ++i)
	{
		vector<uint32>& ids = i->second;
		int index = urand(0, ids.size() - 1);
		if (index >= ids.size())
			continue;

		ai->CastSpell(ids[index], bot);
		return true;
	}

	return false;
}
