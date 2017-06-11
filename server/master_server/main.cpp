#include "master_server.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (MasterServer::GetInstance().Init())
	{
		MasterServer::GetInstance().AfterInit();
		MasterServer::GetInstance().Tick();
		MasterServer::GetInstance().BeforeShut();
		MasterServer::GetInstance().Shut();
	}

	return 0;
}