#pragma once

#include "data_define.h"

namespace fsm
{
	enum class FSMState_t
	{
		STATE_UNDEFINE,
		STATE_IDLE,
		STATE_WALK,
		STATE_RUN,
		STATE_SPRINT,
		STATE_JUMP,
		STATE_SPRINTJUMP,
	};

	enum class Behaviour_t
	{
		BEH_UNDEFINE,

		BEH_IDLE = 1,
		BEH_IDLE_ALERT,
		BEH_IDLE_SELLING,

		BEH_WALK = 1000,
		BEH_RUN,
		BEH_SPRINT,

		BEH_JUMP = 2000,
		BEH_SPRINTJUMP,
	};
	class AbstractBehaviour_Base
	{
	protected:
		Behaviour_t beh_{ Behaviour_t::BEH_UNDEFINE };
		FSMState_t state_{ FSMState_t::STATE_UNDEFINE };
		int stage_{ 0 };
	protected:
		AbstractBehaviour_Base() = default;
	public:
		virtual ~AbstractBehaviour_Base() = default;
	};

	//idle, Beh_Idle_Alert, selling etc.
	class AbstractBehaviour_Stay : public AbstractBehaviour_Base
	{

	};

	//walk, run, sprint
	class AbstractBehaviour_Move : public AbstractBehaviour_Base
	{

	};
	
	//move to position by way point
	class AbstractBehaviour_Movebypos : public AbstractBehaviour_Base
	{

	};
	class AbstractBehaviour_Jump
	{

	};
}