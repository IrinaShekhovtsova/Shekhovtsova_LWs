#include "pch.h"
#include "Client.h"
#include "../Shekhovtsova_Server/Message.h"
#include "../Shekhovtsova_Server/Message.cpp"

void Client::ProcessMessages()
{
	while (true)
	{
		Message m = Message::send(MR_BROKER, MT_GETDATA);
		switch (m.header.type)
		{
		case MT_DATA:
			cout << "User " << m.header.from << " sent msg: \n" << m.data << endl;
			break;
		default:
			Sleep(2000);
			break;
		}
	}
}

void Client::Menu()
{
	cout << "\n 1. Send msg to user" <<
		"\n 2. Send msg to all users" <<
		"\n 3. Close connection \n";
}

Client::Client()
{
	AfxSocketInit();
	thread t(&Client::ProcessMessages, this);
	t.detach();

	Message m = Message::send(MR_BROKER, MT_INIT);
	this->id = m.clientID;

	while (true)
	{
		Menu();
		int i;
		cin >> i;
		switch (i)
		{
		case(1):
		{
			cout << "\n Enter user id: ";
			int id;
			cin >> id;
			cout << "\n Enter message: ";
			string str;
			cin >> ws;
			getline(cin, str);
			Message::send(id, MT_DATA, str);
			break;
		}
		case(2):
		{
			cout << "\n Enter message: ";
			string str;
			cin >> ws;
			getline(cin, str);
			Message::send(MR_ALL, MT_DATA, str);
			break;
		}
		case(3):
		{
			Message::send(MR_BROKER, MT_EXIT);
			exit(0);
			break;
		}
		default:
		{
			cout << "\n try again";
		}
		}

	}

}
