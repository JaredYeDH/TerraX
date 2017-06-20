#include "game_state.h"
#include "game_state_manager.h"
#include "guest.h"
#include "client_net_module.h"
#include "comm/proto/client_server.pb.h"

using namespace packet_cs;
using namespace terra;

void GameState_Press2Start::Enter()
{
	std::cout << "Press Enter to continue...";
	std::cin.get();
	GameStateManager::GetInstance().NextState(GameState_t::LOGIN_FORM);
}


void GameState_eLoginForm::Enter()
{
	std::cout << "Please input you account:\t " << std::endl;
	std::string account_name;
	std::getline(std::cin, account_name);
	std::cout << "Please input you password:\t " << std::endl;
	std::string password;
	std::getline(std::cin, password);
	Guest::GetInstance().InitAccountInfo(std::move(account_name), std::move(password));
	GameStateManager::GetInstance().NextState(GameState_t::CONNECTING2LOGIN);
}

void GameState_Connecting2Login::Enter()
{
	ClientNetModule::GetInstance().StartConnectLoginServer();
}

void GameState_AccountLoggingin::Enter()
{
	MsgReqLoginCL msg;
	msg.set_account_name(Guest::GetInstance().get_account_name());
	msg.set_password(Guest::GetInstance().get_password());
	ClientNetModule::GetInstance().SendPacket2LoginServer(msg);
}

void GameState_ChosingServer::Enter()
{
	std::cout << "Please input server id:\t " << std::endl;
	int server_id = 0;
	std::cin >> server_id;
	MsgSelectServerCL msg;
	msg.set_server_id(server_id);
	ClientNetModule::GetInstance().SendPacket2LoginServer(msg);
}

void GameState_Connecting2Gate::Enter()
{
	MsgQuitLoginCL req;
	ClientNetModule::GetInstance().SendPacket2LoginServer(req);

	//TODO: login2gate
}

void GameState_CheckingPermission::Enter()
{
	//PktGameLoginReq pkt;
	//pkt.set_account_name(LocalGuest::GetInstance().GetAccountName());
	//pkt.set_session_key(LocalGuest::GetInstance().GetSessionKey());
	//NetManagerClient::GetInstance().SendPacket(PeerType_t::gateserver, pkt);
}

void GameState_AccountEnteringWorld::Enter()
{
}