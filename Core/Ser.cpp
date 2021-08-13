#include "Ser.h"
#include <fstream>
#include <functional>

using namespace Core;

void Ser::SerTo(std::string path)
{
	std::ofstream output(path);
	std::function<void(Ser*, std::string&)>* fixtPoint = nullptr;
	std::function<void(Ser*, std::string&)> serialize =
		[&fixtPoint](Ser* serializable, std::string& result)
		{
			switch (serializable->_type)
			{
			case SerType::INTEGER: result += " " + std::to_string(serializable->_intVal);    break;
			case SerType::FLOAT:   result += " f" + std::to_string(serializable->_floatVal); break;
			case SerType::STRING:  result += " \"" + serializable->_stringVal + '"';         break;
			case SerType::ARRAY: {
				result += '[' + std::to_string(serializable->_arrayChilds.size()) + ']';
				for (auto child : serializable->_arrayChilds) result += "\n ", (*fixtPoint)(child, result);
				result += '\n';
				break;
			}
			case SerType::OBJECT: {
				result += "{";
				for (auto child : serializable->_objectChilds)
				{
					result += "\n " + child.first + ": ", (*fixtPoint)(child.second, result);
				}
				result += "\n}\n";
				break;
			}
			}
		};

	fixtPoint = &serialize;

	std::string result;
	serialize(this, result);

	output << result;
	output.close();
}

void Ser::DeserFrom(std::string path)
{
	std::ifstream input(path);
	std::function<void(Ser*)>* fixtPoint = nullptr;
	std::function<void(Ser*)> deserialize =
		[&input, &fixtPoint](Ser* p)
		{
			char next = input.peek();
			while (std::isspace(next)) input.get(), next = input.peek();
			if (std::isdigit(next)) p->_type = SerType::INTEGER , input >> p->_intVal;
			else if (next == 'f')   p->_type = SerType::FLOAT   , input.get(), input >> p->_floatVal;
			else if (next == '"')   p->_type = SerType::STRING  , input.get(), std::getline(input, p->_stringVal, '"');
			else if (next == '[' || next == '{')
			{
				if (next == '[')
				{
					input.get();
					size_t   size;
					input >> size;
					input.get();
					p->_type = SerType::ARRAY;
					p->_arrayChilds.resize(size);
					for (size_t i = 0; i < size; ++i) p->_arrayChilds[i] = new Ser(), (*fixtPoint)(p->_arrayChilds[i]);
				}
				else
				{
					p->_type = SerType::OBJECT;
					while (next != '}')
					{
						 while (std::isspace(next) || next == '{') input.get(), next = input.peek();
						 if (next == '}') break;
						 std::string key;
						 std::getline(input, key, ':');
						 while (!key.empty() && std::isspace(key.back())) key.pop_back();
						 (*fixtPoint)(p->_objectChilds[key] = new Ser());
						 next = input.peek();
					}
					input.get();
				}
			}
		};
	fixtPoint = &deserialize;
	deserialize(this);
	input.close();
}
