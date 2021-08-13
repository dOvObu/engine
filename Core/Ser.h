#ifndef INCLUDED_SER_H
#define INCLUDED_SER_H
#include <string>
#include <vector>
#include <map>

namespace Core {

class Ser {
public:
	void SerTo(std::string path);
	void DeserFrom(std::string path);

	int         AsInt() { return _intVal; }
	float       AsFloat() { return _floatVal; }
	std::string AsString() { return _stringVal; }

	std::vector<     Ser*     >& AsArray() { return _arrayChilds; }
	std::map<std::string, Ser*>& AsObject() { return _objectChilds; }

private:
	enum class SerType
	{
		INTEGER,
		FLOAT,
		STRING,
		ARRAY,
		OBJECT,
	}
	_type;

public:
	Ser& operator[](size_t      index) { return *_arrayChilds[index]; }
	Ser& operator[](std::string   key) { return *_objectChilds[key]; }
	Ser& operator= (int         value) { return _type = SerType::INTEGER, _intVal = value, *this; }
	Ser& operator= (float       value) { return _type = SerType::FLOAT, _floatVal = value, *this; }
	Ser& operator= (std::string value) { return _type = SerType::STRING, _stringVal = value, *this; }

	Ser& Add(Ser* value) { return _type = SerType::ARRAY, _arrayChilds.push_back(value), * this; }
	Ser& Add(std::string key, Ser* value) { return _type = SerType::OBJECT, _objectChilds[key] = value, *this; }
	~Ser()
	{
		for (auto ch : _arrayChilds ) delete ch;
		for (auto ch : _objectChilds) delete ch.second;
	}
	bool HasKey(std::string key) { return 0 < _objectChilds.count(key); }

private:
	int         _intVal;
	float       _floatVal;
	std::string _stringVal;

	std::vector<Ser*>           _arrayChilds;
	std::map<std::string, Ser*> _objectChilds;
};

}
#endif
