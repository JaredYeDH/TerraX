#pragma once

namespace fsm
{
    enum class AbstractBehaviourType {
        AB_UNDEFINE,
        AB_STAY,
        AB_MOVE,
        AB_JUMP,
    };
    class AbstractBehaviourArgs_Base
    {
	private:

    public:
        virtual AbstractBehaviourType GetABType() { return AbstractBehaviourType::AB_UNDEFINE; }
    };
}