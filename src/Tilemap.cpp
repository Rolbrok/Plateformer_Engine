#include <sstream>
#include "Tilemap.h"
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

bool Tilemap::load(std::string filename)
{
    // Create a file from the filename
    std::ifstream _file(filename.c_str());

    // If the file cannot be openned, returns false
    // else, loads the map and the blocks into the memory
    if (!_file) {
        std::cout << "Cannot open file. Aborting." << std::endl;
        return false;
    } else {
        // For the max size of the map
        sf::Vector2i curr_max = sf::Vector2i(0, 0);

        // three vectors for the portals
        // One for each done portal (works with the number)
        // One for the start of the portal (first occurence)
        // One for the end of the portal (last occurence)
        std::vector< int > p_done;
        std::vector< Portal > p_start;
        std::vector< Portal > p_end;

        // For reach line of the file,
        // Reads between the commas the number of the block, and add it to the _map vector
        std::string line;
        for (size_t y = 0; std::getline(_file, line); y++) {
            if ((int)y > curr_max.y)
                curr_max.y = (int)y;
            
            // Increments the size of the _map vector (We add a line)
            _map.resize(_map.size() + 1);

            // Reads between the commas
            std::string chars;
            std::stringstream ss_line(line);
            for (size_t x = 0; std::getline(ss_line, chars, ','); x++) {
                if ((int)x > curr_max.x)
                    curr_max.x = (int)x;

                // We add the corresponding number to the end of the current map line
                _map[y].push_back(atoi(chars.c_str()));

                // If the block is a Portal
                // Checks the number, if the start is already defined, defines the end, else
                // defines the start
                // If the block is not a portal and is not empty
                // Create a Block object according to the result of the getBlock() function, that returns the inherited class of Block
                // Then sets the position of this block, which is equal to map_position * TILE_SIZE and the size to TILE_SIZE
                // Then add the Block to the _bounds vector, which will be used to draw and check the collisions of the map
                if (chars[0] == 'P') {
                    int portal_number = chars[1] - 48;
                    Portal curr_portal((float)x*TILE_SIZE, (float)y*TILE_SIZE);
                    curr_portal.setSize(TILE_SIZE, TILE_SIZE);
    
                    // If the portal number is found on the done portal vector, defines the end
                    // else, defines the start and add the number to the done portal vector
                    if (std::find(p_done.begin(), p_done.end(), portal_number) != p_done.end()) {
                        // Resizes the p_end vector to have the same number of portal in each 
                        if (portal_number + 1 >= (int)p_end.size()) {
                            p_end.resize(portal_number + 1);
                        }
                        p_end[portal_number] = curr_portal;
                    }
                    else {
                        // Resizes the p_start vector to have the same number of portal in each 
                        if (portal_number + 1 >= (int)p_start.size()) {
                            p_start.resize(portal_number + 1);
                        }
                        p_done.push_back(portal_number);
                        p_start[portal_number] = curr_portal;
                    }
                } else {
                    if (_map[y][x] != 0) {
                        Block curr_block = getBlock(_map[y][x], (float)x*TILE_SIZE, (float)y*TILE_SIZE, (float)TILE_SIZE);

                        _bounds.push_back(curr_block);
                    }
                }
            }
        }

        // If the size of the start vector and the end vector (for the portals) is not the size (end not found or otherwise)
        // Error, return false;
        if (p_end.size() != p_start.size()) {
            std::cout << "Error in the portal, check the maps." << std::endl;
            return false;
        }

        // Else, for each start portal, creates a Start block that points to the End block, 
        // and a End block, that points to the Start Block (So we can teleport from both sides of the portal)
        // Adds then the portals to the _bounds vector (the Block_Portal has a color, and can be collided)
        for (size_t i = 0; i < p_start.size(); i++) {
            Portal block_start = p_start[i];
            block_start.setDestination(p_end[i].getPosition());

            Portal block_end = p_end[i];
            block_end.setDestination(p_start[i].getPosition());

            _interactables.push_back(block_start);
            _interactables.push_back(block_end);
        }

        // Create a block for the ground, transparent, just for the collisions, and adds it to the _bounds vector
        Block block_ground;
        block_ground.setColor(sf::Color(0, 0, 0, 0));
        block_ground.setPosition(0.f, (float)_map.size()*TILE_SIZE);
        block_ground.setSize((float)(_map[0].size() * 2)*TILE_SIZE);
        _bounds.push_back(block_ground);
    
        curr_max += sf::Vector2i(1, 1);
        setMax(curr_max*TILE_SIZE);
    }

    // The file loading worked
    return true;
}

std::pair<Tilemap::Collision_Type, sf::Vector2f>
Tilemap::collision(sf::FloatRect player)
{
    // Creates a copy of the player's position
    sf::Vector2f pos(player.left, player.top);

    // Define a temporary collision type
    Collision_Type col_side = Collision_Type::none;

    // For each Block in the _bounds vector
    for (size_t i = 0; i < _bounds.size(); i++) {

        // If there is a collision with a dangerous/trap Block
        // return the Collision type dangerous and a temporary position that may not be used by the player
        if (player.intersects(_bounds[i].getGlobalBounds()) && _bounds[i].dangerous()) {
            return std::make_pair(Collision_Type::dangerous, sf::Vector2f(16, 16));
        }
        // If this is a slide block
        // Returns the type and no move point
        if (_bounds[i].getAngle() != 0.f && player.intersects(_bounds[i].getGlobalBounds())) {
            return std::make_pair(Collision_Type::slide, _bounds[i].getEquationFactor());
        }

        // Temporary move_point with the side and the movement of the collision
        std::pair<Collision::Side, sf::Vector2f> move_point = Collision::getMovingPoint(player, _bounds[i].getGlobalBounds());
        // Adds the move_point position to the position
        pos += move_point.second;
        
        // Checks the side of the collision and changes accordingly
        // If the collision is downwards, makes the col_side down
        // If the collision is left/right, makes the col_side left/right
        // If the collision is down and left/right, add the types to have down_left/down_right
        // Else, the collision type will stay normal
        switch (move_point.first) {
        case Collision::Side::down:
            if (col_side == Collision_Type::left)
                col_side = Collision_Type::down_left;
            else if (col_side == Collision_Type::right)
                col_side = Collision_Type::down_right;
            else
                col_side = Collision_Type::down;
            break;
        case Collision::Side::left:
            if (col_side == Collision_Type::down)
                col_side = Collision_Type::down_left;
            col_side = Collision_Type::left;
            break;
        case Collision::Side::right:
            if (col_side == Collision_Type::down)
                col_side = Collision_Type::down_right;
            col_side = Collision_Type::right;
            break;
        case Collision::Side::top:
            if (col_side == Collision_Type::none)
                col_side = Collision_Type::collision;
            break;
        default:
            break;
        }
    }

    // Returns the collision type and the wanted position for the player
    return std::make_pair(col_side, pos);
}

std::pair<Interactable::Interaction_Type, sf::Vector2f>
Tilemap::interactions(sf::FloatRect player, sf::Vector2f speed)
{
    for (size_t i = 0; i < _interactables.size(); i++) {
        if (player.intersects(_interactables[i].getGlobalBounds())) {
            return std::make_pair(_interactables[i].getType(), _interactables[i].interact(player, speed));
        }
    }

    return std::make_pair(Interactable::Interaction_Type::none, sf::Vector2f(0, 0));
}

float Tilemap::getAngle(sf::FloatRect player)
{
    for (size_t i=0; i < _bounds.size(); i++) {
        if (_bounds[i].getAngle() != 0 && player.intersects(_bounds[i].getGlobalBounds()))
            return _bounds[i].getAngle();
    }
}

sf::Vector2i Tilemap::getMaxPos()
{
    return max_pos;
}

void Tilemap::setMax(int x, int y)
{
    max_pos = sf::Vector2i(x, y);
}

void Tilemap::setMax(sf::Vector2i new_max)
{
    max_pos = new_max;
}

Block Tilemap::getBlock(int c, float x, float y, float size) const
{
    // Return the type of block added to the bounds
    switch (c)
    {
    case BLOCK_RED:
        return Block_Red(x, y, size);
        break;
    case BLOCK_BLUE:
        return Block_Blue(x, y, size);
        break;
    case BLOCK_GREEN:
        return Block_Green(x, y, size);
        break;
    case BLOCK_TRAP:
        return Block_Trap(x, y, size);
        break;
    case BLOCK_SLIDERIGHT:
        return Block_SlideRight(x, y, size);
        break;
    case BLOCK_SLIDELEFT:
        return Block_SlideLeft(x, y, size);
        break;
    default:
        return Block(x, y, size);
        break;
    }

    return Block(x, y, size);
}

Interactable Tilemap::getInteractable(int c, float x, float y) const
{
    switch (c) {
    case SPEEDUP:
        return SpeedUp(x, y);
        break;
    case PORTAL:
        return Portal(x, y);
        break;
    }
    return Interactable(x, y);
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // For each object in the _bounds vector, draw it 
    for (size_t i = 0; i < _bounds.size(); i++) {
        target.draw(_bounds[i], states);
    }

    // For each interactable
    for (size_t i = 0; i < _interactables.size(); i++) {
        target.draw(_interactables[i], states);
    }
}

bool Tilemap::isDown(Tilemap::Collision_Type col)
{
    // Checks if the collision is downwards (on the ground)
    return (col == Collision_Type::down || col == Collision_Type::down_left || col == Collision_Type::down_right || col == Collision_Type::slide);
}
