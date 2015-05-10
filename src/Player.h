#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SIZE 24

#include <SFML/Graphics/RectangleShape.hpp> /* For sf::RectangleShape */
#include <SFML/Graphics/RenderTarget.hpp> /* RenderTarget */
#include <SFML/Graphics/RenderStates.hpp> /* RenderStates */
#include <SFML/Graphics/Drawable.hpp> /* For Drawable */
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

	void setTilemap(Tilemap tm);
	void setHUD(HUD *new_hud);

	sf::FloatRect getGlobalBounds();

	size_t size();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	void controls(float dt);
    void fly(float dt);

private:
	Controls m_controls;
	Controls::Move last_direction = Controls::Move::none;
	Tilemap::Collision_Type last_collision;

	sf::RectangleShape m_rectangle;

    float portal_timeout = 0.2f;
    bool teleported = false;

	float speed1 = 6, speed2 = 10;
	float min_speed = 20.f;
	float max_walking_speed = 250.f;
	float max_running_speed = 400.f;

	bool falling = false;
	float fall_time = 0.f;
	float max_fall_time = 0.1f;

	bool onGround = false;
	float last_ground;
	float last_speed = 0;

	bool isJumping = false;
	float jump_time = 0.f;
	float max_jump_time = 0.55f;

	float jump_speed = -448.f;
	float jump_height = 0.f;
	float max_jump_height = 175.f;

	bool checkCollision = false;
	Tilemap t_m;

	HUD *m_hud;
	bool hud_available = false;

	float reactivity_percentage = 0.008f;
	float anti_friction = 0.06f;

    bool sliding = false;

    float max_f = 0.f;
    float max_h = 0.f;

    bool released = true;

    bool debug = true;
    bool flying = false;
};

#endif
