#include "node_server/node_server.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (NodeServer::GetInstance().Init())
	{
		NodeServer::GetInstance().AfterInit();
		NodeServer::GetInstance().Tick();
		NodeServer::GetInstance().BeforeShut();
		NodeServer::GetInstance().Shut();
	}

	return 0;
}