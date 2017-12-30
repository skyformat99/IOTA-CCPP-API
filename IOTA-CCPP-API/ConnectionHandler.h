#pragma once

//CPP INCLUDES
#include <string>


//WIN INCLUDES
#include <windows.h>

#pragma comment( lib, "ws2_32.lib" )

class TCPConnection
{
public:
	TCPConnection();
	~TCPConnection();

	int send(const std::string &);
	std::string getPacket();
	std::string getHost() { return host; }
	unsigned short getPort() { return port; }
	bool isConnected() { return connected; }
	void closeConnection();

	bool connect(std::string hostname, unsigned short port = 80);

private:
	std::string host;
	SOCKADDR_IN addr;
	unsigned short port;
	unsigned int s;
	bool connected;
};

TCPConnection::TCPConnection()
{
	connected = false;
}

inline TCPConnection::~TCPConnection()
{
	closeConnection();
}


inline int TCPConnection::send(const std::string &packet)
{
	return ::send(s, packet.c_str(), packet.length(), 0);
}

inline std::string TCPConnection::getPacket()
{
	const unsigned short bufSize = 256;
	char buf[bufSize] = "";
	std::string returnString;
	int len = 0;

	do 
	{
		len = recv(s, buf, bufSize - 1, 0);
		buf[len] = '\0';
		returnString += buf;
	}
	while (len == bufSize - 1);

	if (len == SOCKET_ERROR)
		connected = false;
		

	return returnString;
}


inline bool TCPConnection::connect(std::string hostname, unsigned short port)
{
	WSADATA wsa; //Windows
	WSAStartup(MAKEWORD(2, 2), &wsa);

	this->host = hostname;
	this->port = port;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
		return false;

	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	
	addr.sin_addr = *(in_addr*)(gethostbyname(hostname.c_str())->h_addr);

	if (::connect(s, (SOCKADDR*)&addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		return false;

	connected = true;
	return true;
}

inline void TCPConnection::closeConnection()
{
	shutdown(s, 2);
	closesocket(s);
	WSACleanup();
}