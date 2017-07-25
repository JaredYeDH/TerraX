#include "db_server/db_server.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (DBServer::GetInstance().Init())
	{
		DBServer::GetInstance().AfterInit();
		DBServer::GetInstance().Tick();
		DBServer::GetInstance().BeforeShut();
		DBServer::GetInstance().Shut();
	}

	return 0;
}