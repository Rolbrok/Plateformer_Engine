#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Window/Keyboard.hpp> /* for keyboard */
#include <SFML/Window/Joystick.hpp> /* for joystick */
#include <map>

#define KEYBOARD_SPEED 85

struct Controls
{
	// Defines the controller type,
	// the moves possibles
	// and the buttons/keys
	enum class Controller { keyboard, joystick };
	enum class Move { left, right, up, down, none };
	enum class Button { jump, back, special, debug };
    enum class Axis { X, Y };

	// The controller is a keyboard at first
	Controller type = Controller::keyboard;
	int joystick_number = -1;

    std::map<Axis, float> axis;	

	// Defines the map that will contain the buttons
	// Defines the direction of the stick/keys, and the move_speed
	std::map<Button, bool> buttons;
	Move direction = Move::none;
	float move_speed = 0;

	// Is the sprint button pressed ?
	bool sprint_pressed = false;

	// Functions that checks wether the c joystick is connected or not
    bool setJoystick(int c);

	// Functions to interact with the controller easily
    bool isKeyPressed(Button key);
    bool isKeyReleased(Button key);

	// Returns the movement speed
	float movementSpeed();

    float getJoystickSpeed(Axis ax);

	// Updates all the values
    void update();
};

#endif
