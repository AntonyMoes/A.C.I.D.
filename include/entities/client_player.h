#ifndef ACID_INCLUDE_CLIENT_PLAYER_H_
#define ACID_INCLUDE_CLIENT_PLAYER_H_


#include <Box2D/Box2D.h>

#include <entity.h>
#include <position_component.h>
#include <texture_component.h>
#include <exp_component.h>
#include <single_world.h>
#include <collision_component.h>
#include <input_move_component.h>
#include <input_mouse_component.h>
#include <name_component.h>
#include <death_component.h>
#include <health_component.h>
#include <texture_manager.h>
#include <ACID_math.h>

class ClientPlayer: public Entity {
  public:
    explicit ClientPlayer(uint16_t id, float x, float y, int texture);
    explicit ClientPlayer(uint16_t id, b2Vec2 pos, int texture) : ClientPlayer(id, pos.x, pos.y, texture) {}
    explicit ClientPlayer(uint16_t id, sf::Vector2f pos, int texture) : ClientPlayer(id, pos.x, pos.y, texture) {}

  private:
    sf::Vector2f sizes = {32.0f, 32.0f};
};

#endif  // ACID_INCLUDE_CLIENT_PLAYER_H_
