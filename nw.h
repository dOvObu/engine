#ifndef NW_H
#define NW_H
#include <SFML/Network/TcpSocket.hpp>
#include <string>

namespace nw
{
	struct nw
	{
		sf::TcpSocket _socket;
		::nw::nw& operator<<(std::string const& s) { return _socket.send(s.c_str(), s.length() + 1), * this; }
		::nw::nw& operator>>(std::string& s)
		{
			char buff[2000];
			size_t sz;
			_socket.receive(buff, sizeof(buff), sz);
			s = buff;
			return *this;
		}
	};

	struct srv
	{
		srv(unsigned short port) { _listener.listen(port); _listener.accept(_nw._socket); }
		::nw::nw& operator<<(std::string const& s) { return _nw << s; }
		::nw::nw& operator>>(std::string& s) { return _nw >> s; }
		sf::TcpListener _listener;
		::nw::nw _nw;
	};

	struct clt
	{
		clt(unsigned short port) { _nw._socket.connect(_address, port); }
		::nw::nw& operator<<(std::string const& s) { return _nw << s; }
		::nw::nw& operator>>(std::string& s) { return _nw >> s; }
		sf::IpAddress _address = sf::IpAddress::getLocalAddress();
		::nw::nw _nw;
	};

}

#endif // ! NW_H
