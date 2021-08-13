#include "wn.h"
sf::RenderWindow* wn::_window{ nullptr };
sf::View wn::_view;
sf::View wn::_def_view;
bool inp::_swapping{ false };
sf::Vector2f inp::_swap_start;
sf::Vector2f inp::_swap_center_start;

void wn::show_greed()
{
	const size_t size = 2000;
	const float step = 25.f;
	const float x = -10000.f;
	const float y = -10000.f;
	const sf::Color color{ 100,100,100 };

	sf::Vertex points[2]
	{
		sf::Vertex({x, y}, color),
		sf::Vertex({x, y + step * size}, color),
	};

	for (size_t i = 0; i < size; ++i)
	{
		points[0].position.x += step;
		points[1].position.x += step;
		wn::window().draw(points, 2, sf::Lines);
	}

	points[0].position = { x, y };
	points[1].position = { x + step * size, y };

	for (size_t i = 0; i < size; ++i)
	{
		points[0].position.y += step;
		points[1].position.y += step;
		wn::window().draw(points, 2, sf::Lines);
	}
}
