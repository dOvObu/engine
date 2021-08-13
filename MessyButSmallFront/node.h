#ifndef NODE_H
#define NODE_H
#include "wn.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <set>
#include <string>

struct text
{
	text(sf::String const& t, size_t pt = 14, sf::Color _color = sf::Color::White) { _text.setFont(_def_font), _text.setCharacterSize(pt), _text.setPosition(0.f, 0.f), _text.setFillColor(_color), _text.setString(t); }
	inline void set_position(sf::Vector2f p) { _text.setPosition(p); }
	inline sf::Vector2f position() const { return _text.getPosition(); }
	inline void show_in(sf::RenderTarget& t) const { t.draw(_text); }
	inline void show() const { show_in(wn::window()); }
	static void init(std::string const& pth) { _def_font.loadFromFile(pth); }
private:
	sf::Text _text;
	static sf::Font _def_font;
};

struct scrollable
{
	void show() { show_in(wn::window()); }
	void show_in(sf::RenderTarget& t)
	{
		_screen.clear(sf::Color::Black);
		for (auto t : _texts) t->show_in(_screen);
		for (auto c : _canvases) c->show_in(_screen);
		_image.setTexture(&_screen.getTexture());
		t.draw(_image);
	}
	scrollable& add(scrollable* c) { _canvases.insert(c); return *this; }
	scrollable& add(text* t) { _texts.insert(t); return *this; }
	scrollable& rm(scrollable* c) { if (_canvases.count(c)) _canvases.erase(c); return *this; }
	scrollable& rm(text* t) { if (_texts.count(t)) _texts.erase(t); return *this; }

//private:
	std::set<text*> _texts;
	std::set<scrollable*> _canvases;
	sf::RenderTexture _screen;
	sf::RectangleShape _image;
	sf::Vector2f _internal_size;
};

struct node
{
private:
	sf::RectangleShape _shape;
};

#endif // ! NODE_H
