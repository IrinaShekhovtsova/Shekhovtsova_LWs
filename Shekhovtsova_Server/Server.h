#pragma once
#pragma once
#include "pch.h"
#include "Message.h"
#include "Session.h"

class Server
{
private:
	int maxID = MR_USER;
	map<int, shared_ptr<Session>> sessions;

	void ProcessClient(SOCKET hSock);
	void IsActive();

public:
	Server();
	int getMaxID();
};

