#include "master_login_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "server_manager/server_manager.h"

using namespace terra;
using namespace packet_ss;

MasterLoginAcceptService::MasterLoginAcceptService()
{
	REG_PACKET_HANDLER_ARG3(MsgReqServerListLM, this, OnMessage_ReqServerListLM);
	REG_PACKET_HANDLER_ARG1(MsgReqEnterServerLS, this, OnMessage_ReqEnterServerLS);
}


void MasterLoginAcceptService::OnLoginConnected(TcpConnection* conn)
{
	ServerManager::GetInstance().CreateLoginServerObj(conn);
}

void MasterLoginAcceptService::OnLoginDisconnected(TcpConnection* conn)
{
	ServerManager::GetInstance().RemoveLoginServerObj(conn);
}

void MasterLoginAcceptService::OnMessage_ReqServerListLM(TcpConnection* conn, int32_t avatar_id, MsgReqServerListLM* msg)
{
	MsgServerListML ack;
	ack.set_result(0);
	const auto& world_servers = ServerManager::GetInstance().GetWorldServers();
	for (const auto& val : world_servers)
	{
		const auto& obj = val.second;
		ServerProfile* profile = ack.add_servers();
		profile->set_server_uid(obj.get_server_uid());
		profile->set_region_showindex(obj.get_region_showindex());
		profile->set_region_name(obj.get_region_name());
		profile->set_server_showindex(obj.get_server_showindex());
		profile->set_server_name(obj.get_server_name());
		profile->set_server_status(obj.get_server_status());
		profile->set_recommond_new(obj.get_recommond_new());
		profile->set_recommond_hot(obj.get_recommond_hot());
	}

	MsgReqServerListLM* post_back = ack.mutable_post_back();
	post_back->set_account_name(msg->account_name());
	SendPacket(conn, ack);
}

void MasterLoginAcceptService::OnMessage_ReqEnterServerLS(MsgReqEnterServerLS* msg)
{
	//TODO: add_login_serverid
	const std::string& account_name = msg->account_name();
	auto ret = [&account_name](int error_code) {
		MsgReqEnterServerResultSL ack;
		ack.set_result(error_code);
		ack.set_account_name(account_name);
	};
	WorldServerObject* obj = ServerManager::GetInstance().FindWorldServerByUID(msg->server_uid());
	if (!obj)
	{
		ret(1);
		return;
	}
}