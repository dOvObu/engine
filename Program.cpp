#include "program.h"

#include "Core/HardcodedPaths.h"
#include "Core/GuiSystem.h"
#include "Core/Ser.h"
#include "Core/PhysicsBlock.h"
#include "Core/Time.h"

#include <SFML/Graphics.hpp>
#include <iostream>

float Core::Time::DeltaTime{ 0.f };

void Program::Run()
{
	Core::GuiSystem gui;
	gui.Init();
	LoadSettings();
	sf::RenderWindow window{ {_width, _height}, _title};
	sf::Clock clock;

	auto tr1 = new Core::Transform{}, tr2 = new Core::Transform{};
	Core::Physics::Add(tr1), Core::Physics::Add(tr2);
	sf::RectangleShape view1, view2;
	view1.setFillColor(sf::Color::Red);
	view1.setPosition(tr1->PositionX = 150, tr1->PositionY = 50);
	view2.setPosition(tr2->PositionX = 150, tr2->PositionY = 200);
	view1.setSize({ (tr1->HalfWidth = 10.f) * 2.f, (tr1->HalfHeight = 10.f) * 2.f });
	view2.setSize({ (tr2->HalfWidth = 100.f) * 2.f, (tr2->HalfHeight = 10.f) * 2.f });
	
	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed) window.close();
		}
		Core::Time::DeltaTime = clock.getElapsedTime().asSeconds();;

		clock.restart();
		Core::Physics::Update();
		tr2->PositionX = 100.f, tr2->PositionY = 200.f;
		tr2->VelocityDx = tr2->VelocityDy = 0.f;
		view1.setPosition(tr1->PositionX, tr1->PositionY);
		view2.setPosition(tr2->PositionX, tr2->PositionY);

		window.clear();
		window.draw(view1);
		window.draw(view2);
		window.display();
	}
}


void Program::LoadSettings()
{
	using namespace Core;
	Ser settings;
	settings.DeserFrom(HardcodedPaths::assets_path + "window_settings.txt");
	if (settings.HasKey("size" )) { auto& sz = settings["size"]; _width = sz[0].AsInt(), _height = sz[1].AsInt(); }
	if (settings.HasKey("title")) { _title   = settings["title"].AsString(); }
}
