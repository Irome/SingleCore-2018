#include "botpch.h"
#include "../../playerbot.h"
#include "TellItemCountAction.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool TellItemCountAction::Execute(Event event)
{
    string text = event.getParam();
    list<Item*> found = parseItems(text);
    map<uint32, uint32> itemMap;
    for (list<Item*>::iterator i = found.begin(); i != found.end(); i++)
    {
        ItemTemplate const* proto = (*i)->GetTemplate();
        itemMap[proto->ItemId] += (*i)->GetCount();
    }

    for (map<uint32, uint32>::iterator i = itemMap.begin(); i != itemMap.end(); ++i)
    {
        ItemTemplate const* proto = sObjectMgr->GetItemTemplate(i->first);
        TellItem(proto, i->second);
    }

    return true;
}
