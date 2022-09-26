#include "pch.h"
#include "Server.h"

int Server::maxID = MR_USER;

void Server::ProcessClient(SOCKET hSock)
{
	CSocket s;
	s.Attach(hSock);
	Message m;
	int messageType = m.receive(s);
	cout << "to: " << m.header.to << " msg from: " << m.header.from << " msg type: " << m.header.type << " msg type: " << messageType << endl;
	switch (messageType)
	{
	case MT_INIT:
	{
		auto session = make_shared<Session>(++maxID);
		sessions[session->id] = session;
		Message::send(s, session->id, MR_BROKER, MT_INIT);
		cout << "Client " << session->id << "connected." << endl;
		break;
	}
	case MT_EXIT:
	{
		sessions.erase(m.header.from);
		Message::send(s, m.header.from, MR_BROKER, MT_CONFIRM);
		cout << "Client " << m.header.from << "disconnected." << endl;
		break;
	}
	case MT_GETDATA:
	{
		auto iSession = sessions.find(m.header.from);
		if (iSession != sessions.end())
		{
			iSession->second->send(s);
		}
		break;
	}
	
	default:
	{
		auto iSessionFrom = sessions.find(m.header.from);
		if (iSessionFrom != sessions.end())
		{
			auto iSessionTo = sessions.find(m.header.to);
			if (iSessionTo != sessions.end())
			{
				iSessionTo->second->add(m);
			}
			else if (m.header.to == MR_ALL)
			{
				for (auto& [id,session] : sessions)
				{
					if (id != m.header.from)
						session->add(m);
				}
			}
		}
		break;
	}
	}
}

Server::Server()
{
	AfxSocketInit();
	CSocket server;
	server.Create(12345);
	while (true)
	{
		if (!server.Listen())
			break;
		CSocket s;
		server.Accept(s);
		thread t(&Server::ProcessClient, this, s.Detach());
		t.detach();
	}
}
