#pragma once
#include "../Value.h"

namespace ai
{
	class LogLevelValue : public ManualSetValue<LogLevel>
	{
	public:
		LogLevelValue(PlayerbotAI* ai) :
			ManualSetValue<LogLevel>(ai, LOGL_BASIC) {}
	};
}
