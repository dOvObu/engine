#ifndef INCLUDED_PROGRAM_H
#define INCLUDED_PROGRAM_H
#include "Core/GuiSystem.h"
#include <string>

class Program {
private:
	unsigned _width { 800 };
	unsigned _height{ 600 };
	std::string _title{ "program" };

public:
	void Run();
	void LoadSettings();
	Core::GuiSystem gui;
};

#endif
