#include "botpch.h"
#include "../../playerbot.h"
#include "NewPlayerNearbyValue.h"

using namespace ai;

uint64 NewPlayerNearbyValue::Calculate()
{
    list<uint64> players = ai->GetAiObjectContext()->GetValue<list<uint64> >("nearest friendly players")->Get();
    set<uint64>& alreadySeenPlayers = ai->GetAiObjectContext()->GetValue<set<uint64>& >("already seen players")->Get();
    for (list<uint64>::iterator i = players.begin(); i != players.end(); ++i)
    {
        uint64 guid = *i;
        if (alreadySeenPlayers.find(guid) == alreadySeenPlayers.end())
            return guid;
    }

    return 0;
}
