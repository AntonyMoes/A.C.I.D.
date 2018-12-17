#include <map>
#include <unistd.h>

#include <i_component.h>
#include <node.h>
#include <entity_life_system.h>
#include <game_loop.h>
#include <active_system.h>

#include <network_manager.h>
#include <network_id.h>
#include <client_network_sr_systems.h>
#include <client_network_move_system.h>
#include <generators/client_network_spawn_system.h>
#include <graphic/client_graphic_system.h>
#include <graphic/tmx_level.h>
#include <single_world.h>
#include <graphic/map_draw_system.h>
#include <window_event_system.h>
#include <graphic/displayer_system.h>
#include <input_move_system.h>
#include <movements/client_move_system.h>
#include <input_mouse_system.h>
#include <movements/move_node.h>
#include <custom_loop.h>
#include <fireball_creation_node.h>
#include <fireball_creation_system.h>
#include <client_shot_sychronization_system.h>
#include <single_world.h>
#include <collision/collision_listener.h>
#include <death/client_death_sync_system.h>
#include <health/client_health_sync_system.h>
#include <healthbar.hpp>
#include <hp_node.hpp>
#include <graphic/texture_manager.h>
#include <client_exp_sync_system.h>
#include <client_exp_sync_node.h>

#include <X11/Xlib.h>   // Мust be included last


int main() {
    XInitThreads();  // <-- Need this to use multithreading along with graphics

    // creating map
    tmx_level level;
    try {
        level.LoadFromFile("../res/map.tmx");
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    auto* world = SingleWorld::get_instance();
    world->SetContactListener(new CollisionListener());
    // AFTER MAP LOADING!..
    // Creating window
    sf::RenderWindow window(sf::VideoMode(700, 700), "ACID");
    window.setFramerateLimit(60);
    window.setFramerateLimit(60);

    NetworkManager net;
    net.connect("localhost", 55503);

    TextureManager texture_manager;

    Loop loop(&window, false);

    // Network systems
    auto spawn_system = new NetworkSpawnSystem(&net);
    auto net_receive = new NetworkReceiveSystem(&net);
    auto net_receive_move = new NetworkReceiveMoveSystem(&net);
    auto net_send = new NetworkSendSystem(&net);
    auto net_send_move_system = new NetworkSendMoveSystem(&net);
    auto client_death_sync = new ClientDeathSyncSystem(&net, loop.get_entity_manager());
    auto client_health_sync = new ClientHealthSyncSystem(&net);
    auto client_exp_sync = new ClientExpSyncSystem(&net);
    // Client systems
    auto* camera = new CameraSystem;
    auto* map = new MapSystem(&window, level);
    auto* graph_system = new GraphicSystem(&window, camera);
    auto* window_event_system = new WindowEventSystem(&window);
    auto* displayer_system = new DisplayerSystem(&window);
    auto* physic_system = new PhysicalSystem(world, level);
    auto* input_move_system = new InputMoveSystem;
    auto* move_system = new MoveSystem;
    auto* input_mouse_system = new InputMouseSystem(&window);
    auto* cl_shot = new ClientShotReceiveSystem(&net);
    auto* cl_shot_send = new ClientShotSendSystem(&net);
    auto healthbar_system = new Healthbar(&window, &texture_manager);
    // Nodes
    auto* input_mouse_node = new InputMouseNode;
    auto* move_node = new MoveNode;
    auto* input_move_node = new InputMoveNode;
    auto* graphic_node = new GraphicNode;
    auto* camera_node = new CameraNode;
    auto* player_pos_sync = new PlayerPosSyncNode;
    auto* client_pos_sync = new ClientPosSyncNode;
    auto* fireball_node = new FireballCreationNode;
    auto* mouse_node = new InputMouseNode;
    auto hp_node = new HPNode;
    auto health_sync_node = new ClientHealthSyncNode;
    auto exp_sync_node = new ClientExpSyncNode;

    // Nodes registration
    loop.add_prototype(camera_node);
    loop.add_prototype(input_move_node);
    loop.add_prototype(graphic_node);
    loop.add_prototype(move_node);
    loop.add_prototype(input_mouse_node);
    loop.add_prototype(client_pos_sync);
    loop.add_prototype(player_pos_sync);
    loop.add_prototype(fireball_node);
    loop.add_prototype(mouse_node);
    loop.add_prototype(hp_node);
    loop.add_prototype(health_sync_node);
    loop.add_prototype(exp_sync_node);
    // Systems registration
    loop.register_term_system(window_event_system);
    loop.register_life_system(spawn_system);
    loop.register_life_system(cl_shot);

    loop.add_system(net_receive);
    loop.add_system(spawn_system);
    loop.add_system(net_receive_move);
    loop.add_system(cl_shot);
    loop.add_system(physic_system);
    loop.add_system(camera);
    loop.add_system(window_event_system);
    loop.add_system(displayer_system);
    loop.add_system(map);
    loop.add_system(graph_system);
    loop.add_system(move_system);
    loop.add_system(input_move_system);
    loop.add_system(input_mouse_system);
    loop.add_system(healthbar_system);
    loop.add_system(client_health_sync);
    loop.add_system(client_exp_sync);
    loop.add_system(client_death_sync);

    loop.add_system(cl_shot_send);
    loop.add_system(net_send_move_system);
    loop.add_system(net_send);

    loop.register_term_system(window_event_system);
    
    loop.run();
}