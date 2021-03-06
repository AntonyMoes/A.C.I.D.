#ifndef ACID_INCLUDE_CLIENT_MOVE_SYSTEM_H_
#define ACID_INCLUDE_CLIENT_MOVE_SYSTEM_H_

#define MOVE_SCALE 2

#include <reactive_system.h>
#include <client_move_node.h>

class ClientMoveSystem: public ReactiveSystem<ClientMoveNode> {
  public:
    void execute() override {
        for (auto& node : reactive_nodes) {
            auto input_move_comp = node->get_component<InputMoveComponent>();
            auto pos_comp = node->get_component<PositionComponent>();

            auto keys = input_move_comp->get_keys();
            auto pos = pos_comp->get_coords();
            if ((*keys)[sf::Keyboard::W]) {
                pos.y -= MOVE_SCALE;
            }
            if ((*keys)[sf::Keyboard::A]) {
                pos.x -= MOVE_SCALE;
            }
            if ((*keys)[sf::Keyboard::S]) {
                pos.y += MOVE_SCALE;
            }
            if ((*keys)[sf::Keyboard::D]) {
                pos.x += MOVE_SCALE;
            }
            pos_comp->set_coords(pos);
        }
    }
};


#endif  // ACID_INCLUDE_CLIENT_MOVE_SYSTEM_H_
