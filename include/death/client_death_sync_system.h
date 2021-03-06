#ifndef ACID_INCLUDE_CLIENT_DEATH_SYNC_SYSTEM_H_
#define ACID_INCLUDE_CLIENT_DEATH_SYNC_SYSTEM_H_


#include <network_manager.h>
#include <active_system.h>
#include <network_id.h>
#include <entity_manager.h>

class ClientDeathSyncSystem : public ActiveSystem<NoneNode> {
  public:
    ClientDeathSyncSystem(NetworkManager* _net, EntityManager* _entity_manager):
                entity_manager(_entity_manager), net(_net) {}

    void execute() override {
        auto packet = net->get_system_packet(DEATH_SYSTEM);
        while (!packet.endOfPacket()) {
            uint16_t id = 0;
            packet >> id;
            entity_manager->delete_entity(id);
        }
    }

  private:
    NetworkManager* net;
    EntityManager* entity_manager;
};

#endif  // ACID_INCLUDE_CLIENT_DEATH_SYNC_SYSTEM_H_
