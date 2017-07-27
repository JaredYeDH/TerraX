#pragma once

namespace fsm
{
	enum class AIControllerType
	{
		PLAYER,
		MONSTER_COMMON,
	};

	struct AIControllerArgs
	{
		AIControllerType controller_type;
	};

	class AIController_Base
	{

	};

	class AIController_CommonMonster
	{

	};
}