#include "world_server/world_server.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (WorldServer::GetInstance().Init())
	{
		WorldServer::GetInstance().AfterInit();
		WorldServer::GetInstance().Tick();
		WorldServer::GetInstance().BeforeShut();
		WorldServer::GetInstance().Shut();
	}

	return 0;
}