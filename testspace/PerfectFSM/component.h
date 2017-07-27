#pragma once

#include "ai_controller.h"

namespace fsm
{
    class FSMComponent;
    class AIComponent;
    class Avatar
    {
    private:
        std::unique_ptr<FSMComponent> fsm_component_;
        std::unique_ptr<AIComponent> ai_component_;

    public:
        void InitFSMComponnet() { fsm_component_ = std::make_unique<FSMComponent>(new FSMComponent(this)); }
        FSMComponent* GetFSMComponent() { return fsm_component_.get(); }
        void InitAIComponet() { ai_component_ = std::make_unique<AIComponent>(new AIComponent(this)); }
        AIComponent* GetAIComponent() { return ai_component_.get(); }
    };
    class FSMComponent
    {
    private:
        Avatar* self_{nullptr};

    public:
        FSMComponent(Avatar* avatar) : self_(avatar) {}
    };

    class AIComponent
    {
    private:
        Avatar* self_{nullptr};
        std::unique_ptr<AIController_Base> controller_;

    public:
        AIComponent(Avatar* avatar) : self_(avatar) {}
        void InitAIController(const AIControllerArgs& args)
        {
            if (args.controller_type == AIControllerType::MONSTER_COMMON) {
                controller_ = std::make_unique<AIController_Base>(new AIController_CommonMonster());
                controller_->Start();
            }
        }
    };
}
