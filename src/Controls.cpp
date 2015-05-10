#include "Controls.h"

bool Controls::setJoystick(int c)
{
	// If the joystick is connected,
	// changes the type of the controls, and returns true
	// else resets the controls to the keyboard
    if (sf::Joystick::isConnected(c)) {
        type = Controller::joystick;
        joystick_number = c;
        return true;
    } else {
		type = Controller::keyboard;
		joystick_number = -1;
        return false;
    }
}

bool Controls::isKeyPressed(Button move)
{
	// Checks if the key is pressed
	// accordingly to the type of the controls
    switch (type) {
    case Controller::keyboard:
		switch (move) {
		case Button::jump:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			break;
		case Button::back:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
			break;
		case Button::special:
			return sf::Keyboard::isKeyPressed(sf::Keyboard::X);
			break;
        case Button::debug:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            break;
		}
        break;
    case Controller::joystick:
        return sf::Joystick::isButtonPressed(joystick_number, (unsigned int)move);
        break;
    default:
        return false;
        break;
    }
	return false;
}

bool Controls::isKeyReleased(Button move)
{
	// If the key was pressed and is now released
	// returns true
	// else returns false
    bool current_state = isKeyPressed(move);

    if (buttons[move] && !current_state) {
        return true;
    } else {
        return false;
    }
}

float Controls::movementSpeed()
{
	// Returns the movement speed according to the type of controls
	// If the controls are keyboard, then return the KEYBOARD_SPEED constant with the sign of the move (left = -1, right = 1)
	// Joystick: returns the value of the left analog stick, unless its value is under 70 or over -70
    switch (type) {
    case Controller::keyboard:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            return 0;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            return -KEYBOARD_SPEED;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            return KEYBOARD_SPEED;
        } else {
            return 0;
        }
        break;
    case Controller::joystick:
		float val = sf::Joystick::getAxisPosition(joystick_number, sf::Joystick::X);
        if (val >= 70) return KEYBOARD_SPEED;
        else if (val <= -70) return -KEYBOARD_SPEED;
        else return 0;
        break;
    }
    return 0;
}

float Controls::getJoystickSpeed(Axis axis)
{
    float mvt = 0;
    bool left = false, up = false;
    bool right = false, down = false;
    switch (type) {
    case Controller::keyboard:
        switch (axis) {
        case Axis::X:
            left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            if (left && right)
                return 0;
            else if (left)
                return -KEYBOARD_SPEED;
            else if (right)
                return KEYBOARD_SPEED;  
            else
                return 0;
            break;
        case Axis::Y:
            up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            if (up && down)
                return 0;
            else if (up)
                return -KEYBOARD_SPEED;
            else if (down)
                return KEYBOARD_SPEED;  
            else
                return 0;
            break; 
        }
        break;
    case Controller::joystick:
        switch (axis) {
        case Axis::X:
            mvt = sf::Joystick::getAxisPosition(joystick_number, sf::Joystick::X);
            if (mvt < -60 || mvt > 60)
                return mvt;
            else 
                return 0;
            break;
        case Axis::Y:
            mvt = sf::Joystick::getAxisPosition(joystick_number, sf::Joystick::Y);
            if (mvt < -60 || mvt > 60)
                return mvt;
            else 
                return 0;
            break;
        }
        break;
    }

    return 0;
}

void Controls::update()
{
	// updates the movement speed, the direction of the movement
    move_speed = movementSpeed();
    direction = (move_speed == 0) ? Move::none : ((move_speed < 0) ? Move::left : Move::right);

	// checks whether the sprint key is pressed or not
	sprint_pressed = (type == Controller::keyboard) ? sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) :
		(sf::Joystick::getAxisPosition(joystick_number, sf::Joystick::Z) <= -70 ||
		sf::Joystick::getAxisPosition(joystick_number, sf::Joystick::Z) >= 70);

	// updates the buttons for the isKeyReleased() function
    buttons[Button::jump] = isKeyPressed(Button::jump);
    buttons[Button::back] = isKeyPressed(Button::jump);
    buttons[Button::special] = isKeyPressed(Button::special);

    axis[Axis::X] = getJoystickSpeed(Axis::X);
    axis[Axis::Y] = getJoystickSpeed(Axis::Y);
}
