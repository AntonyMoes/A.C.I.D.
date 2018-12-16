#ifndef ACID_INCLUDE_FIREBALL_CREATION_NODE_H_
#define ACID_INCLUDE_FIREBALL_CREATION_NODE_H_

#include <node.h>
#include <input_mouse_component.h>
#include <collision_component.h>
#include <damage_component.h>
#include <body_component.h>


class FireballCreationNode : public Node<FireballCreationNode> {
  public:
    FireballCreationNode() {
        add_component<DamageComponent>();
        add_component<CollisionComponent>();
        add_component<BodyComponent>();
    }
};

#endif  // ACID_INCLUDE_FIREBALL_CREATION_NODE_H_
