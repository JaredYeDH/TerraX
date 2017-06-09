#pragma once
#include "base/types.h"
#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"
#include "srv/net/server_accept_service.h"
#include "login_account_state.h"
#include <unordered_map>
#include <memory>
#include <array>

namespace terra
{
	class LoginAccount;
	class LoginAccountManager
	{
		MAKE_INSTANCE(LoginAccountManager);
		DISABLE_COPY(LoginAccountManager);
		using LoginAccountMap = std::unordered_map<int, std::unique_ptr<LoginAccount> >;
		using Account2FdMap = std::unordered_map<std::string, int >;
		using AccountStateArray = std::array<std::unique_ptr<AccountState_Base>, static_cast<int>(Account_State_t::ACCOUNT_COUNT)>;
	private:
		LoginAccountMap account_map_;
		Account2FdMap account2fd_map_;

		AccountStateArray states_;
	public:
		LoginAccountManager();
		~LoginAccountManager() = default;

		void CreateAccount(TcpConnection* conn);
		void RemoveAccount(TcpConnection* conn);
		AccountState_Base* GetAccountState(Account_State_t account_state) { return states_[static_cast<int>(account_state)].get(); }
		LoginAccount* GetAccountByAccountName(const std::string& account_name);
	private:
		void InitAccountState();

		void OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgReqLoginCL* msg);
		
		void OnMessage_MsgServerListML(packet_ss::MsgServerListML* msg);
	};
}