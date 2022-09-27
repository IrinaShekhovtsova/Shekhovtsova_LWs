#pragma once

#include "Message.h"
#include "Session.h"

class Server
{
private:
	static int maxID;
	map<int, shared_ptr<Session>> sessions;

	void ProcessClient(SOCKET hSock);
	void IsActive();

public:
	Server();
};

