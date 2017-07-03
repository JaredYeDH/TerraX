#pragma once

namespace fsm
{
	enum class Behaviour
	{

	};

	class Behaviour_Base
	{
	protected:

	};

	//idle, idle_in_battle, selling etc.
	class Behaviour_Idle : public Behaviour_Base
	{

	};

	//walk, run, sprint
	class Behaviour_Move : public Behaviour_Base
	{

	};

	//move to position by way point
	class Behaviour_Movebypos : public Behaviour_Base
	{

	};

	class Behaviour_Jump : public Behaviour_Base
	{

	};
}