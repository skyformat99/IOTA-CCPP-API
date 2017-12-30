
#include "IotaApi.h"

#include <iostream>

using namespace std;

int main()
{
	IotaApi iota;

	//iota.connectToServer("iota.bitfinex.com", 80);
	iota.connectToServer("node03.iotatoken.nl", 15265);
	cout << iota.getNodeInfo() << endl;
	cout << iota.addNeighbor("tcp:test.ml:271839") << endl;
	cout << iota.getNeighbors() << endl;
	
	cout << iota.getBalance("RWDUOYMHMXRRWPMSR9ZSMGSVEOBKALBRIXCQWVCZQ9QINNKPOQGKROBXCWRTBLGYABINNNLVYEZXZ9999", 10) << endl;
	
	
	cout << iota.getTransactionsToApprove(30) << endl;

	cin.get();
}