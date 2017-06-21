#pragma once
#include "../Value.h"

namespace ai
{
    class NewPlayerNearbyValue : public CalculatedValue<uint64>
	{
	public:
        NewPlayerNearbyValue(PlayerbotAI* ai) : CalculatedValue<uint64>(ai, "new player nearby") {}
        virtual uint64 Calculate();
    };

    class AlreadySeenPlayersValue : public ManualSetValue<set<uint64>& >
	{
	public:
        AlreadySeenPlayersValue(PlayerbotAI* ai) : ManualSetValue<set<uint64>& >(ai, data, "already seen players") {}

    private:
        set<uint64> data;
    };
}
