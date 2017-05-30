#include "login_server/login_server.h"

using namespace terra;

int main(int argc, char* argv[])
{
	if (LoginServer::GetInstance().Init())
	{
		LoginServer::GetInstance().AfterInit();
		LoginServer::GetInstance().Tick();
		LoginServer::GetInstance().BeforeShut();
		LoginServer::GetInstance().Shut();
	}

	return 0;
}