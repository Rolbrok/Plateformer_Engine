#include "Player.h"
#include <iostream>

Player::Player()
{
	setPlayer(0, 0);
}

Player::Player(float x, float y)
{
	setPlayer(x, y);
}

Player::Player(sf::Vector2f pos)
{
	setPlayer(pos.x, pos.y);
}

Player::~Player()
{
}

void Player::setPlayer(float x, float y)
{
	// Sets the speed to 0
	// Sets the acceleration to gravity
	// Sets the position to the position given
	setSpeed(0, Vector2b(true, true));
	setAcceleration(0, Vector2b(true, true));
	setPosition(x, y);

	// Changes the color of the player drawn (m_rectangle), and its size
	m_rectangle.setFillColor(sf::Color::Black);
	m_rectangle.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    max_jump_height = 5*(TILE_SIZE);
    jump_time = (-max_jump_height) / (jump_speed);
}

size_t Player::size()
{
	return PLAYER_SIZE;
}

void Player::setTilemap(Tilemap *tm)
{
	t_m = tm;
	checkCollision = true;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// Draws the player
	target.draw(m_rectangle, states);
}

void Player::controls(float dt)
{
	// Code for the controls
	// Checks if the player can move, and apply

	// Sets the joysticks
	// If the joystick/controller is not connected:
	// the input will be directed to the keyboard
	m_controls.setJoystick(0);

    if (m_controls.isKeyPressed(Controls::Button::debug)) {
        debug = (debug) ? false : true;
    }
    if (m_controls.isKeyPressed(Controls::Button::special)) {
        flying = (flying) ? false : true;
        if (flying) return;
    }

	last_direction = (getSpeed().x == 0) ? Controls::Move::none : ((getSpeed().x < 0) ? Controls::Move::left : Controls::Move::right);

	// Changes the speed modifier and the max jump height
	// If the player is sprinting, the speed modifier will be speed2
	// Else, it will be speed1
	// with speed2 > speed1
	float speed_modifier = (m_controls.sprint_pressed) ? speed2 : speed1;

    // Sets the friction and the reactivity percentage
    // If the player is falling of jumping, the friction will be higher
    // The physics will be more enjoyable if there is not much friction on the ground
    // (nobody wants to slide from a high tower)
    if ((isJumping || falling) && !onGround) {
        anti_friction = 0.03f;
        reactivity_percentage = 0.005f; 
    } else {
        anti_friction = 0.4f;
        reactivity_percentage = 0.0001f;
    }

	// If there is actually a movement speed
	// If keyboard: the speed, if the left/right key is pressed will be 85/-85
	// If joystick:
	// The speed will be equal to the analog value of the left stick
	// which goes from 0 -> 100 and -100 -> 0
	if (m_controls.move_speed != 0) {
		
		// Checks which side is the collision
		Controls::Move l_col = Controls::Move::none;
		switch (last_collision) {
		case Tilemap::Collision_Type::left:
			l_col = Controls::Move::left;
			break;
		case Tilemap::Collision_Type::right:
			l_col = Controls::Move::right;
			break;
		default:
			break;
		}

		// Can the player move right/left
		// if the collision side is the same as the movement side
		// this doesn't do anything
		if (l_col != m_controls.direction)
		{
			// If the direction is the same as before
			// or if we weren't moving before, move normally
			// acceleration.x = signof(move_speed)*speed_modifier
			// else, we use the reactivity percentage:
			// in which case: 
			// acceleration.x = signof(move_speed)*speed_modifier + acceleration.x*percentage
			if (last_direction == Controls::Move::none || last_direction == m_controls.direction) {
				setAcceleration(signof(m_controls.move_speed)*speed_modifier, Vector2b(1, 0));
			}
			else if (last_direction != m_controls.direction){
				setAcceleration(signof(m_controls.move_speed)*speed_modifier + getAcceleration().x*reactivity_percentage, Vector2b(1, 0));
			}
		}
	}
	// If the move_speed is equal to 0
	// Reduce slowly the acceleration
	// such that acceleration.x = -speed.x * friction
	else {
		setAcceleration(-getSpeed().x*anti_friction, Vector2b(1, 0));
		// If the speed is too slow
		// set it to 0
		if (signof(getSpeed().x)*getSpeed().x < min_speed) {
			setSpeed(0, Vector2b(1, 0));
		}
	}

	// If the speed is too high
	// sets it the maximum
	// Handles if the player is running or walking
	if (!m_controls.sprint_pressed && signof(getSpeed().x)*getSpeed().x >= max_walking_speed)
		setSpeed(signof(getSpeed().x)*max_walking_speed, Vector2b(1, 0));
	else if (signof(getSpeed().x)*getSpeed().x >= max_running_speed)
		setSpeed(signof(getSpeed().x)*max_running_speed, Vector2b(1, 0));

	if (falling) {
		fall_time += dt;
	}

    if (fall_time > max_f) {
        max_f = fall_time;
    }

	// If the player is on the ground or is not falling for more than max_fall_time, and he pressed the jump button and is not already jumping
	// set the jump time to 0
	// define the last speed, the last ground height
	// the player won't be on the ground anymore, and will be jumping
	// sets the speed and disables the acceleration
	// such that:
	// speed.y = jump_speed with jump_speed < 0 (because SFML axis y is on the top of the window)
	// acceleration.y = -GRAVITY (to disable the gravity during the jump)
	if ((onGround || (falling && fall_time <= max_fall_time)) && m_controls.isKeyPressed(Controls::Button::jump) && !isJumping && released) {
		last_speed = getSpeed().y;
		last_ground = getPosition().y;
		isJumping = true;
		onGround = false;
		setSpeed(jump_speed, Vector2b(0, 1));
		//setAcceleration(-GRAVITY, Vector2b(0, 1));
		jump_time = 0.f;
        last_x = getPosition().x;
	}
	// If the jump key is released or the jump height is over the limit
	// set the speed to the height of the jump, and re-enable the gravity
	// reset the jump height and jump time to 0
	else if (!onGround && (m_controls.isKeyReleased(Controls::Button::jump) || jump_height >= max_jump_height || jump_time >= max_jump_time) && isJumping) {
    	setSpeed(0, Vector2b(0,1));
		//setAcceleration(0, Vector2b(false, true));
		jump_height = 0.f;
		jump_time = 0.f;
		isJumping = false;
	    falling = true;
        max_d = abs(getPosition().x - last_x);
    }

    if (!m_controls.isKeyPressed(Controls::Button::jump))
        released = true;
    else
        released = false;

	// if the jump key isn't pressed and the player is on the ground
	// the player isn't jumping anymore
	// speed.y = 0
	if (!m_controls.isKeyPressed(Controls::Button::jump) && onGround) {
		isJumping = false;
	}

	// If the player is jumping, updates the jump height
	// else, resets the jump height to 0
	if (isJumping) {
		jump_height = last_ground - getPosition().y;
		jump_time += dt;
	}
	else {
		jump_height = 0.f;
		jump_time = 0.f;
	}

    if (jump_height > max_h) {
        max_h = jump_height;
    }

	// Finally, updates the controls
	// such that the keys are resets and the isKeyReleased function works.
	m_controls.update();
}

void Player::fly(float dt)
{
    m_controls.setJoystick(0);

    if (m_controls.isKeyPressed(Controls::Button::debug)) {
        debug = (debug) ? false : true;
    }
    if (m_controls.isKeyPressed(Controls::Button::special)) {
        flying = (flying) ? false : true;
        if (!flying) {
	        setSpeed(0, Vector2b(true, true));
	        setAcceleration(0, Vector2b(true, true));
            return;
        }
    }

    setAcceleration(-GRAVITY, Vector2b(0,1));
    setSpeed(m_controls.axis[Controls::Axis::X]*speed2, Vector2b(1, 0));
    setSpeed(m_controls.axis[Controls::Axis::Y]*speed2, Vector2b(0, 1));

    m_controls.update();
}

void Player::update_player(float dt)
{
	// Order of process:
	// - Controls : sets the speed, acceleration of the player
	// - Entity::update : applies speed, acceleration to the position
	// - Collision checking : check for collision with the new position and updates

	// Checks the controls if not flying
	if (!flying) controls(dt);
    else fly(dt);

	// Updates the player
	// this function is from the class Entity
	// from which the Player class is inherited
	// Changes the position, and updates the speed and acceleration
	update(dt);

	// If a tilemap has been set, we can check the collisions between the player and the blocks
	if (checkCollision && (getSpeed().y != 0) && !flying) {

        // Checks if the player can  teleport again
        if (teleported) {
            portal_timeout -= dt;
            if (portal_timeout <= 0) {
                teleported = false;
                portal_timeout = 0.2f;
            }
        }
    
		// Get the collision pair from the Tilemap class
		// Return a pair of collision with a position, from where to move
		std::pair<Tilemap::Collision_Type, sf::Vector2f> collisions = (*t_m).collision(getGlobalBounds(), (last_collision != Tilemap::Collision_Type::portal && !teleported));

		// Check if the player is falling
        if ((*t_m).isDown(collisions.first)) {
            onGround = true;
        } else {
            onGround = false;
        }
		
        if ((*t_m).isDown(last_collision) && !(*t_m).isDown(collisions.first)) {
			falling = true;
			onGround = false;
        }
		else if ((*t_m).isDown(collisions.first) && !isJumping) {
			falling = false;
			onGround = true;
			fall_time = 0.f;
			jump_time = 0.f;  
        }

        if (last_collision == Tilemap::Collision_Type::left || last_collision == Tilemap::Collision_Type::right) 
            setAcceleration(0);

		// Checks the type of collision that occured with the blocks
		// If the collision was down, sets the last ground, and stops the player from moving in the Y-axis
		// If the collision was a portal, teleport if the conditions are verified (timeout passed)
		// If the collision was dangerous (a trap), reset the player to the position defined for now as { 16, 16 }
		// Then updates the position
		switch (collisions.first) {
		case Tilemap::Collision_Type::portal:
			if (last_collision != collisions.first && !teleported) {
				setPosition(collisions.second);
		        teleported = true;
        	}
			break;
		case Tilemap::Collision_Type::collision:
			setPosition(collisions.second);
            setSpeed(0, Vector2b(0, 1));
            setAcceleration(0, Vector2b(0, 1));
            break;
		case Tilemap::Collision_Type::left:
		case Tilemap::Collision_Type::right:
            setSpeed(0, Vector2b(1, 0));
	        if (isJumping)
      	        setAcceleration(signof(getSpeed().y) * speed2 - wall_accel, Vector2b(0, 1));
            else if (falling)
                setAcceleration(-speed1, Vector2b(0, 1));
            else 
                setAcceleration(0, Vector2b(0, 1));
            setPosition(collisions.second);
			break;
		case Tilemap::Collision_Type::down_left:
		case Tilemap::Collision_Type::down_right:
			setSpeed(0);
			setPosition(collisions.second);
            setAcceleration(0, Vector2b(0, 1));
			last_ground = getPosition().y;
			break;
		case Tilemap::Collision_Type::down:
			setSpeed(0, Vector2b(0, 1));
            setAcceleration(0, Vector2b(0, 1));
			setPosition(collisions.second);
			last_ground = getPosition().y;
			break;
		case Tilemap::Collision_Type::dangerous:
			setPosition(0, 50);
			setSpeed(0);
			setAcceleration(0);
			break;
		}

		// Defines the last collision
		// Needed in the controls part
		if (collisions.first == Tilemap::Collision_Type::left || collisions.first == Tilemap::Collision_Type::down_left) {
			last_collision = Tilemap::Collision_Type::left;
		}
		else if (collisions.first == Tilemap::Collision_Type::right || collisions.first == Tilemap::Collision_Type::down_right) {
			last_collision = Tilemap::Collision_Type::right;
		}
		else if (collisions.first == Tilemap::Collision_Type::portal) {
			last_collision = Tilemap::Collision_Type::portal;
		}
        else if ((*t_m).isDown(collisions.first)) {
            last_collision = Tilemap::Collision_Type::down;
        }
		else {
			last_collision = collisions.first;
		}

        // Check if the player is on a slide
        if (collisions.first == Tilemap::Collision_Type::slide && !isJumping) {
            sliding = true;    
			setSpeed(0, Vector2b(0, 1));
            setAngle((*t_m).getAngle(getGlobalBounds()));
            setPosition(getPosition().x, collisions.second.x * (getPosition().x+size()) + collisions.second.y - size()/2);
        } else {
            sliding = false;
            setAngle(0);
        }
	}

    // Checks the boundaries (Bottom screen, top screen, left, and right end of the map)
    if (getPosition().y <= 0)
    {
        setPosition(getPosition().x, 0);
    }  
    if (getPosition().y >= (*t_m).getMaxPos().y-size())
    {
        setPosition(getPosition().x, (*t_m).getMaxPos().y-size());
        setSpeed(0, Vector2b(0, 1));
        onGround = true;
        falling = false;
        jump_time = 0.f;
        fall_time = 0.f;
    }
    if (getPosition().x <= 0) {
        setPosition(0, getPosition().y);
    }        
    if (getPosition().x + size() > (*t_m).getMaxPos().x) {
        setPosition((*t_m).getMaxPos().x - size(), getPosition().y);
    }

	// Changes the position of the object drawn to the screen (for now sf::RectangleShape)
	m_rectangle.setPosition(getPosition());
    m_rectangle.setRotation(getAngle());

    // Changes the view
    // Side-scoller code
    // Only changes if the map is bigger that can be seen
    if ((*t_m).getMaxPos().x > (*m_view).getSize().x) {
        if (getPosition().x < (*m_view).getSize().x/2) {
            (*m_view).setCenter((*m_view).getSize().x/2.f, (*m_view).getCenter().y);
        } else if (getPosition().x > (*t_m).getMaxPos().x - (*m_view).getSize().x/2) {
            (*m_view).setCenter((*t_m).getMaxPos().x-(*m_view).getSize().x/2, (*m_view).getCenter().y); 
        } else {
            (*m_view).setCenter(getPosition().x, (*m_view).getCenter().y);
        }
    }
  
    if ((*t_m).getMaxPos().y > (*m_view).getSize().y) { 
        if (getPosition().y < (*m_view).getSize().y/2) {
            (*m_view).setCenter((*m_view).getCenter().x, (*m_view).getSize().y/2);
        } else if (getPosition().y > (*t_m).getMaxPos().y - (*m_view).getSize().y/2) {
            (*m_view).setCenter((*m_view).getCenter().x, (*t_m).getMaxPos().y-(*m_view).getSize().y/2); 
        } else {
            (*m_view).setCenter((*m_view).getCenter().x, getPosition().y);
        }
    }
    
    // Debug information
    // Relative to the side-scrolling   
    if (hud_available && debug) {  
        sf::Vector2f view_origin = sf::Vector2f((*m_view).getCenter().x-(*m_view).getSize().x/2+20,
                                                (*m_view).getCenter().y-(*m_view).getSize().y/2);

        char c[50];
        sprintf(c, "pos: %.2f, %.2f", getPosition().x, getPosition().y);
        std::string v = std::string(c);
        sf::Text text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
        
        sprintf(c, "speed: %.2f, %.2f", getSpeed().x, getSpeed().y);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+1*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
        
        sprintf(c, "acceleration: %.2f, %.2f", getAcceleration().x, getAcceleration().y);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+2*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
       
        sprintf(c, "onGround: %d, collision: %d", onGround, (int)last_collision);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+3*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 

        sprintf(c, "Flying: %d, Debug: %d", flying, debug);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+4*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 

        sprintf(c, "Max fall: %.4f, falling: %d", max_f, falling);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+5*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 

        sprintf(c, "Max height: %.4f : %.2f blocks", max_h, max_h/TILE_SIZE);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+6*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
        
        sprintf(c, "Max distance: %.2f, current: %.2f", max_d, signof(getPosition().x - last_x)*(getPosition().x - last_x));
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+7*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
        
        sprintf(c, "Max: %d, %d", (*t_m).getMaxPos().x, (*t_m).getMaxPos().y);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+8*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
        
        sprintf(c, "center: %.1f, %.1f , size: %.1f %.1f", (*m_view).getCenter().x, (*m_view).getCenter().y, (*m_view).getSize().x, (*m_view).getSize().y);
        v = std::string(c);
        text = sf::Text(v, (*m_hud).getFont(), 20);
        text.setPosition(view_origin.x, view_origin.y+9*20);
        text.setColor(sf::Color::White);
        (*m_hud).addText(text); 
    }
}

sf::FloatRect Player::getGlobalBounds()
{
	// Returns the bounds of the player, defines as
	// left = position.x, top = position.y, width = player_size, height = player_size
	return sf::FloatRect(getPosition().x, getPosition().y, PLAYER_SIZE, PLAYER_SIZE);
}

void Player::setHUD(HUD *new_hud)
{
	m_hud = new_hud;
	hud_available = true;
}

void Player::setView(sf::View *new_view)
{
    m_view = new_view;
}
