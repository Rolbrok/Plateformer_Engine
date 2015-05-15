#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SIZE 24

#include <SFML/Graphics/RectangleShape.hpp> /* For sf::RectangleShape */
#include <SFML/Graphics/RenderTarget.hpp> /* RenderTarget */
#include <SFML/Graphics/RenderStates.hpp> /* RenderStates */
#include <SFML/Graphics/Drawable.hpp> /* For Drawable */
#include <SFML/Graphics/View.hpp> /* for sf::View */
#include <SFML/Graphics/Font.hpp> /* for sf::Font */
#include "Entity.h" /* For Entity */
#include "Controls.h" /* For keyboard implementation */
#include "Tilemap.h" /* For collisions */
#include "HUD.h"

enum Move { left, right, none };

class Player : public Entity, public sf::Drawable
{
public:
    Player();
    Player(float x, float y);
    Player(sf::Vector2f pos);
    ~Player();

    void setPlayer(float x, float y);

    void update_player(float dt);

    void setTilemap(Tilemap *tm);
    void setHUD(HUD *new_hud);
    void setView(sf::View *new_view);

    sf::FloatRect getGlobalBounds();

    size_t size();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void controls(float dt);
    void fly(float dt);
    void collision(float dt);
    void interactions(float dt);
    void debug_informations();

private:
    Controls m_controls;
    Controls::Move last_direction = Controls::Move::none;
    Tilemap::Collision_Type last_collision;

    sf::RectangleShape m_rectangle;

    float portal_timeout = 0.5f;
    bool teleported = false;

    float boost_timeout = 0.3f;

    bool isJumping = false;
    float jump_time = 0.f;
    float max_jump_time = 0.55f;

    float jump_speed = -448.f;
    float jump_height = 0.f;
    float max_jump_height = 175.f;

    float speed1 = 6, speed2 = 10;
    float min_speed = 20.f;
    float max_walking_speed = (8*TILE_SIZE)/max_jump_time;
    float max_running_speed = (16*TILE_SIZE)/max_jump_time;

    bool falling = false;
    float fall_time = 0.f;
    float max_fall_time = 0.1f;

    bool onGround = false;
    float last_ground;
    float last_speed = 0;

    bool checkCollision = false;
    Tilemap *t_m;

    HUD *m_hud;
    bool hud_available = false;

    float reactivity_percentage = 0.008f;
    float anti_friction = 0.06f;

    bool sliding = false;

    float max_f = 0.f;
    float max_h = 0.f;
    float max_d = 0.f;

    float last_x = 0.f;

    bool released = true;

    float wall_accel = 10.f;

    bool debug = true;
    bool flying = false;

    sf::View *m_view;
    Vector2b follow = Vector2b(false, false);
};

#endif
