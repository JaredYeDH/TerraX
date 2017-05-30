#include "client.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (Client::GetInstance().Init())
	{
		Client::GetInstance().AfterInit();
		Client::GetInstance().Tick();
		Client::GetInstance().BeforeShut();
		Client::GetInstance().Shut();
	}

	return 0;
}