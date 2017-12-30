#pragma once
#include "ConnectionHandler.h"

class IotaApi
{
public:
	IotaApi();
	~IotaApi();

	bool connectToServer(const std::string &, const unsigned short port);
	void disconnect();

	std::string getNodeInfo();
	std::string getNeighbors();
	std::string addNeighbor(const std::string &);
	std::string removeNeighbor(const std::string &);
	std::string getBalance(const std::string &, const unsigned int threshold = 100);
	std::string getTips();
	std::string findTransaction(const std::string &);
	std::string getTrytes(const std::string &);
	std::string getInclusionStates(const std::string &, const std::string &);
	std::string getTransactionsToApprove(const unsigned int depth);
	std::string attachToTangle(const std::string &, const std::string &, const unsigned int, const std::string &);
	void interruptAttachingToTangle();
	std::string broadcastTransaction(const std::string &);
	std::string storeTransaction(const std::string &);


	void sendHTTPPost(const std::string &commands);
	std::string getHTTPAnswer();

private:

	TCPConnection con;
};

IotaApi::IotaApi()
{

}

inline IotaApi::~IotaApi()
{

}


inline bool IotaApi::connectToServer(const std::string &hostname, const unsigned short port)
{
	return con.connect(hostname, port);
}

inline void IotaApi::disconnect()
{
	con.closeConnection();
}

inline void IotaApi::sendHTTPPost(const std::string &commands)
{
	std::string packet = "";

	//Use original client header for anonymity
	packet += "POST / HTTP/1.1\r\n";
	packet += "Host: " + con.getHost() + ":" + std::to_string(con.getPort()) + "\r\n";
	packet += "Content-Length: " + std::to_string(commands.length()) + "\r\n";
	packet += "Connection: keep-alive\r\n";
	packet += "Origin: file://\r\n";
	packet += "X-IOTA-API-Version: 1\r\n";
	packet += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) IOTAWallet/2.5.6 Chrome/58.0.3029.110 Electron/1.7.9 Safari/537.36\r\n";
	packet += "Content-Type: application/json\r\n";
	packet += "Accept: */*\r\n";
	packet += "\r\n";
	packet += commands;

	con.send(packet);
}


inline std::string IotaApi::getHTTPAnswer()
{
	std::string packet = con.getPacket();
	const unsigned int pos = packet.find("\r\n\r\n");
	if (pos == std::string::npos) return "";
	return packet.substr(pos + 4);
}



std::string IotaApi::getNodeInfo()
{
	sendHTTPPost("{\"command\":\"getNodeInfo\"}");
	return getHTTPAnswer();
}

std::string IotaApi::getNeighbors()
{
	sendHTTPPost("{\"command\":\"getNeighbors\"}");
	return getHTTPAnswer();
}

inline std::string IotaApi::addNeighbor(const std::string & neighbor)
{
	sendHTTPPost("{\"command\":\"addNeighbors\",\"uris\":[\"" + neighbor + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::removeNeighbor(const std::string & neighbor)
{
	sendHTTPPost("{\"command\":\"removeNeighbor\",\"uris\":[\"" + neighbor + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::getBalance(const std::string & address, const unsigned int threshold)
{
	sendHTTPPost("{\"command\":\"getBalances\",\"addresses\":[\"" + address + "\"],\"threshold\":" + std::to_string(threshold) + "}");
	return getHTTPAnswer();
}

inline std::string IotaApi::getTips()
{
	sendHTTPPost("{\"command\":\"getTips\"}");
	return getHTTPAnswer();
}

inline std::string IotaApi::findTransaction(const std::string & transaction)
{
	sendHTTPPost("{\"command\":\"findTransactions\",\"addresses\":[\"" + transaction + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::getTrytes(const std::string &hashes)
{
	sendHTTPPost("{\"command\":\"getTrytes\",\"hashes\":[\"" + hashes + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::getInclusionStates(const std::string &transactions, const std::string &tips)
{
	sendHTTPPost("{\"command\":\"getInclusionStates\",\"transactions\":[\"" + transactions + "\"],\"tips\":[\"" + tips + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::getTransactionsToApprove(const unsigned int depth)
{
	sendHTTPPost("{\"command\":\"getTransactionsToApprove\",\"depth\":" + std::to_string(depth) + "}");
	return getHTTPAnswer();
}

inline std::string IotaApi::attachToTangle(const std::string &trunkTransaction, const std::string &branchTransaction, const unsigned int minWeightMagnitude, const std::string &trytes)
{
	sendHTTPPost("{\"command\":\"attachToTangle\",\"trunkTransaction\":" + trunkTransaction + "\",\"branchTransaction\":\"" + branchTransaction + "\",\"minWeightMagnitude\":" + std::to_string(minWeightMagnitude) + ",\"trytes\":[\""+ trytes + "\"]}");
	return getHTTPAnswer();
}

inline void IotaApi::interruptAttachingToTangle()
{
	sendHTTPPost("");
}

inline std::string IotaApi::broadcastTransaction(const std::string &trytes)
{
	sendHTTPPost("{\"command\":\"broadcastTransactions\",\"trytes\":[\"" + trytes + "\"]}");
	return getHTTPAnswer();
}

inline std::string IotaApi::storeTransaction(const std::string &trytes)
{
	sendHTTPPost("{\"command\":\"storeTransactions\",\"trytes\":[\"" + trytes + "\"]}");
	return getHTTPAnswer();
}

