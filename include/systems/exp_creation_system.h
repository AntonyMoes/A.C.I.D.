#ifndef ACID_INCLUDE_EXP_CREATION_SYSTEM_H_
#define ACID_INCLUDE_EXP_CREATION_SYSTEM_H_


#include <reactive_system.h>
#include <exp_ball.h>
#include <entity_life_system.h>
#include <exp_creation_node.h>

class ExpCreationSystem: public ReactiveSystem<ExpCreationNode>, public EntityLifeSystem {
  public:
    void execute() override {
        for (auto& node : reactive_nodes) {
            auto death_comp = node->get_component<DeathComponent>();
            if (death_comp->get_state()) {
                auto body_comp = node->get_component<BodyComponent>();
                auto exp_comp = node->get_component<ExpComponent>();
                auto pos = body_comp->get_body()->GetPosition();
                auto exp = exp_comp->get_death_exp();
                auto exp_ball = new ExpBall(pos, exp);
                create_entity(exp_ball);
            }
        }
    }
};

#endif  // ACID_INCLUDE_EXP_CREATION_SYSTEM_H_
