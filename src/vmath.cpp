#include "vmath.h"

float dot_product(sf::Vector2f a, sf::Vector2f b)
{
    return (a.x*b.x+a.y*b.y);
}

float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

float angle_between_vectors(sf::Vector2f a, sf::Vector2f b)
{
    float m_dot = dot_product(a, b);
    return acos( (a.x*b.x + a.y*b.y) / (length(a)*length(b)) ) * 180/MATH_PI;
}

sf::Vector2f vector_angle(sf::Vector2f v_start, sf::Vector2f v_end, float angle)
{
    sf::Vector2f V = v_end - v_start;

    sf::Vector2f destination;
    destination.x = v_end.x;
    destination.y = v_end.y - (abs(V.x)*cos(angle))/cos(90-abs(angle));

    return destination;
}

sf::Vector2f equation_factor(sf::Vector2f v_start, sf::Vector2f v_end)
{
    float m = (v_end.y - v_start.y) / (v_end.x - v_start.x);
    float b = v_start.y - m * v_start.x;

    return sf::Vector2f(m, b);
}
