#include <SFML/Graphics.hpp>
#include "wn.h"
#include "node.h"

int main()
{
	sf::RenderWindow window({ 800,600 }, ". . .");
	text::init("RobotoMono-Regular.ttf");
	wn::view().setSize(800, 600);
	wn::set_window(window);
	text txt(L"test");
	txt.set_position(wn::view().getCenter());
	scrollable scrl;
	scrl._image.setPosition(wn::view().getCenter());
	scrl._image.setSize({ 300, 500.f });
	
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed || e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (e.type == sf::Event::Resized)
			{
				wn::resize(e.size.width, e.size.height);
			}
			if ((e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased) && e.mouseButton.button == sf::Mouse::Middle)
			{
				inp::start_swap(e.type == sf::Event::MouseButtonPressed);
			}
			if (e.type == sf::Event::MouseMoved)
			{
				inp::swap_view();
			}
		}
		wn::clear();
		wn::show_greed();
		scrl.show();
		window.display();
	}
	return 0;
}
