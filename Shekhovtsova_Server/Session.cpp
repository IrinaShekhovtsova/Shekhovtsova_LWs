#include "pch.h"
#include "Session.h"

void Session::updateLastInteraction()
{
    CSingleLock lock(&cs, TRUE);
    lastInteraction = system_clock::now();
}


bool Session::stillActive()
{
	if (this->inActivity() > 15)
		return false;
	else
		return true;
}

int Session::inActivity()
{
	auto now = system_clock::now();
	auto intSeconds = duration_cast<seconds>(now - lastInteraction);
	return intSeconds.count();
}
