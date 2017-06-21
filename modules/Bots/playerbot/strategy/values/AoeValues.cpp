#include "botpch.h"
#include "../../playerbot.h"
#include "AoeValues.h"

#include "../../PlayerbotAIConfig.h"
using namespace ai;

list<uint64> FindMaxDensity(Player* bot)
{
    list<uint64> units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<list<uint64> >("possible targets");
    map<uint64, list<uint64> > groups;
    int maxCount = 0;
    uint64 maxGroup;
    for (list<uint64>::iterator i = units.begin(); i != units.end(); ++i)
    {
        Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
        if (!unit)
            continue;

        for (list<uint64>::iterator j = units.begin(); j != units.end(); ++j)
        {
            Unit* other = bot->GetPlayerbotAI()->GetUnit(*j);
            if (!other)
                continue;

            float d = unit->GetDistance2d(other);
            if (d <= sPlayerbotAIConfig.aoeRadius * 2)
                groups[*i].push_back(*j);
        }

        if (maxCount < groups[*i].size())
        {
            maxCount = groups[*i].size();
            maxGroup = *i;
        }
    }

    if (!maxCount)
        return list<uint64>();

    return groups[maxGroup];
}

WorldLocation AoePositionValue::Calculate()
{
    list<uint64> group = FindMaxDensity(bot);
    if (group.empty())
        return WorldLocation();

    float x1, y1, x2, y2;
    for (list<uint64>::iterator i = group.begin(); i != group.end(); ++i)
    {
        Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
        if (!unit)
            continue;

        if (i == group.begin() || x1 > unit->GetPositionX())
            x1 = unit->GetPositionX();
        if (i == group.begin() || x2 < unit->GetPositionX())
            x2 = unit->GetPositionX();
        if (i == group.begin() || y1 > unit->GetPositionY())
            y1 = unit->GetPositionY();
        if (i == group.begin() || y2 < unit->GetPositionY())
            y2 = unit->GetPositionY();
    }
    float x = (x1 + x2) / 2;
    float y = (y1 + y2) / 2;
    float z = bot->GetPositionZ();
    bot->UpdateGroundPositionZ(x, y, z);
    return WorldLocation(bot->GetMapId(), x, y, z, 0);
}

uint8 AoeCountValue::Calculate()
{
    return FindMaxDensity(bot).size();
}
