#include "login_account_state.h"
#include "login_account.h"
#include "comm/proto/server_server.pb.h"
#include "login_server/login_net_module.h"

using namespace terra;
using namespace packet_cs;
using namespace packet_ss;


void AccountState_Base::HandleMessage(LoginAccount& account, packet_cs::MsgQuitLoginCL* msg)
{
	account.EnterState(Account_State_t::ACCOUNT_DESTROY);
}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingLogin::Enter(LoginAccount& account) {}
void AccountState_WaitingLogin::Tick(LoginAccount& account) {}
void AccountState_WaitingLogin::Leave(LoginAccount& account) {}
void AccountState_WaitingLogin::HandleMessage(LoginAccount& account, MsgReqLoginCL* msg)
{
	account.InitAccountName(msg->account_name());

#ifdef NEED_BILLING_AUTH
	//account, password
	//send packet 2 billing
	account.EnterState(Account_State_t::ACCOUNT_WAITING_BILLINGAUTH);
#else
	account.set_token("token_key");
	MsgReqServerListLM req;
	req.set_account_name(msg->account_name());
	LoginNetModule::GetInstance().SendPacket2Master(req);
	account.EnterState(Account_State_t::ACCOUNT_WAITING_SERVERLIST);
#endif
}
//////////////////////////////////////////////////////////////////////////

void AccountState_WaitingBillingAuth::Enter(LoginAccount& account) {}
void AccountState_WaitingBillingAuth::Tick(LoginAccount& account) {}
void AccountState_WaitingBillingAuth::Leave(LoginAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingServerList::Enter(LoginAccount& account) {}
void AccountState_WaitingServerList::Tick(LoginAccount& account) {}
void AccountState_WaitingServerList::Leave(LoginAccount& account) {}

void AccountState_WaitingServerList::HandleMessage(LoginAccount& account, MsgServerListML* msg)
{
	MsgLoginResultLC ack;
	ack.set_result(0);
	ack.set_token(account.get_token());
	ack.mutable_servers()->Swap(msg->mutable_servers());
	LoginNetModule::GetInstance().SendPacket2Client(account.get_conn(), ack);
	account.EnterState(Account_State_t::ACCOUNT_WAITING_REQ_ENTERSERVER);
}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingReqEnterServer::Enter(LoginAccount& account) {}
void AccountState_WaitingReqEnterServer::Tick(LoginAccount& account) {}
void AccountState_WaitingReqEnterServer::Leave(LoginAccount& account) {}
void AccountState_WaitingReqEnterServer::HandleMessage(LoginAccount& account, packet_cs::MsgSelectServerCL* msg)
{
	MsgReqEnterServerLS req;
	req.set_account_name(account.get_account_name());
	req.set_account_token(account.get_token());
	req.set_server_uid(msg->server_id());
	req.set_login_serverid(LoginNetModule::GetInstance().GetLoginServerId());
	LoginNetModule::GetInstance().SendPacket2Master(req);
	account.EnterState(Account_State_t::ACCOUNT_WAITING_GETGATEINFO);
}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingGetGateInfo::Enter(LoginAccount& account) {}
void AccountState_WaitingGetGateInfo::Tick(LoginAccount& account) {}
void AccountState_WaitingGetGateInfo::Leave(LoginAccount& account) {}

void AccountState_WaitingGetGateInfo::HandleMessage(LoginAccount& account, packet_ss::MsgReqEnterServerResultSL* msg)
{
	MsgSeclectServerResultLC ack;
	ack.set_result(msg->result());
	ack.set_gate_ip(msg->gate_ip());
	ack.set_gate_port(msg->gate_port());
	LoginNetModule::GetInstance().SendPacket2Client(account.get_conn(), ack);
	account.EnterState(Account_State_t::ACCOUNT_WAITING_CLIENTSWITCH2GATE);
}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingClientSwitch2Gate::Enter(LoginAccount& account) {}
void AccountState_WaitingClientSwitch2Gate::Tick(LoginAccount& account) {}
void AccountState_WaitingClientSwitch2Gate::Leave(LoginAccount& account) {}
//////////////////////////////////////////////////////////////////////////
void AccountState_Destory::Enter(LoginAccount& account) 
{
	TcpConnection* conn = account.get_conn();
	if (conn)
	{
		LoginNetModule::GetInstance().CloseClientConnection(conn->get_fd());
	}
}
void AccountState_Destory::Tick(LoginAccount& account) {}
void AccountState_Destory::Leave(LoginAccount& account) {}