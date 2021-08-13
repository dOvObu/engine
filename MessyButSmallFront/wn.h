#ifndef WN_H
#define WN_H
#include <SFML/Graphics.hpp>

struct wn
{
	static inline sf::RenderWindow& window() { return *_window; }
	static inline sf::View& view() { return _view; }
	static inline void set_window(sf::RenderWindow& w)
	{
		_window = &w;
		_def_view = w.getView();
		w.setView(_view);
	}
	static inline void clear() { _window->setView(_view), _window->clear(sf::Color(80, 80, 80)); }
	static inline sf::View& def_view() { return _def_view; }
	static inline void resize(float w, float h) { _view.setSize(w, h), _def_view.setSize(w, h); }

	static void show_greed();
private:
	static sf::RenderWindow* _window;
	static sf::View _view;
	static sf::View _def_view;
};

struct inp
{
	static inline sf::Vector2f mouse() { return wn::window().mapPixelToCoords(mouse_px()); }
	static inline sf::Vector2i mouse_px() { return sf::Mouse::getPosition(wn::window()); }
	static inline sf::Vector2f mouse_ui() { return wn::window().mapPixelToCoords(mouse_px(), wn::def_view()); }
	static inline bool mouse_btn(sf::Mouse::Button btn) { return sf::Mouse::isButtonPressed(btn); }
	static inline bool key(sf::Keyboard::Key k) { return sf::Keyboard::isKeyPressed(k); }
	
	static inline void swap_view()
	{
		if (!_swapping) return;
		wn::view().setCenter(_swap_center_start + _swap_start - mouse_ui());
	}

	static inline void start_swap(bool start)
	{
		_swapping = start;
		_swap_start = mouse_ui();
		_swap_center_start = wn::view().getCenter();
	}

private:
	static bool _swapping;
	static sf::Vector2f _swap_center_start;
	static sf::Vector2f _swap_start;
};

#endif // ! WN_H
