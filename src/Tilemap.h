#ifndef TILEMAP_H
#define TILEMAP_H

#define TILE_SIZE 24

#include <fstream> /* For files */
#include <vector> /* For the maps */
#include <map>
#include <SFML/Graphics/RectangleShape.hpp> /* For collision rectangles */
#include <SFML/Graphics/RenderTarget.hpp> /* RenderTarget */
#include <SFML/Graphics/RenderStates.hpp> /* RenderStates */
#include <SFML/Graphics/Drawable.hpp> /* For Drawable */
#include <string> /* For std::getline, std::string */
#include <algorithm> /* std::find */
#include <utility> /* pair */
#include "Blocks.h" /* red block */
#include "Interactables.h"
#include "Collision.h"

class Tilemap : public sf::Drawable
{
public:
    // Defines the collisions that can occurs during the check
    enum class Collision_Type { right, left, down, down_left, down_right, collision, dangerous, slide, none };

public:
    Tilemap();
    ~Tilemap();

    // This function loads a file which contains a map under the form:
    /* ObjectNumber, ObjectNumber....
       ....
    */
    bool load(std::string filename);
    
    // Returns the collision type and the position that the player needs to be at
    std::pair<Collision_Type, sf::Vector2f> 
    collision(sf::FloatRect player);

    // Returns the type of interaction
    std::pair<Interactable::Interaction_Type, sf::Vector2f> 
    interactions(sf::FloatRect player, sf::Vector2f speed);

    // Returns the angle of the block slide being collided
    float getAngle(sf::FloatRect player);

    // Returns the maximum size of the map
    sf::Vector2i getMaxPos();

    // checks if the collision is down
    bool isDown(Collision_Type col);

    // Returns the type of block that the number c returns
    // all the blocks are defined in Blocks.h
    Block getBlock(int c, float x, float y, float size = 0) const;

    Interactable getInteractable(int c, float x, float y) const;

    // As the class is inherited from sf::Drawable, we can call the virtual draw() function
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // The map maximum size (for the boundaries)
    sf::Vector2i max_pos;
private:
    void setMax(int x, int y);
    void setMax(sf::Vector2i new_max);

private:
    // The _map is the 2 dimensional array that contains the number of each block
    std::vector < std::vector <int> > _map;
    // The _bounds is the array containing all the blocks, used for the collision and the drawing
    std::vector < Block > _bounds;
    // The _interactables array  is the array containing the speed ups, portal and such...
    std::vector < Portal > _interactables;
    std::vector < SpeedUp > _speed_ups;
};

#endif
