#ifndef VMATH_H
#define VMATH_H

#include <SFML/Graphics/Transform.hpp> /* for sf::Vector2 */
#include <math.h>

#define MATH_PI 3.141592653589793

float dot_product(sf::Vector2f a, sf::Vector2f b);
float length(sf::Vector2f a);
float angle_between_vectors(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f vector_angle(sf::Vector2f a, sf::Vector2f b, float angle);
sf::Vector2f equation_factor(sf::Vector2f s, sf::Vector2f e);

#endif
