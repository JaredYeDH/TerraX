#pragma once
#include "base/types.h"
#include "comm/proto/client_server.pb.h"
#include "srv/net/server_accept_service.h"
#include <unordered_map>

namespace terra
{
	class LoginAccount;
	class LoginAccountManager
	{
		MAKE_INSTANCE(LoginAccountManager);
		DISABLE_COPY(LoginAccountManager);
		using LoginAccountMap = std::unordered_map<std::string, std::unique_ptr<LoginAccount> >;
	private:
		LoginAccountMap account_map_;
	public:
		LoginAccountManager();
		~LoginAccountManager() = default;

		void CreateAccount(TcpConnection*);

	private:
		void OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgReqLoginCL* msg);
	};
}