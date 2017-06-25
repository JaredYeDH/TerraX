#pragma once
#include "base/types.h"
#include "base/multi_index_map.h"
#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"
#include "srv/net/server_accept_service.h"
#include "login_account_state.h"
#include <memory>
#include <array>
#include "login_account.h"

namespace terra
{
	class LoginAccountManager
	{
		MAKE_INSTANCE(LoginAccountManager);
		DISABLE_COPY(LoginAccountManager);
		using AccountStateArray = std::array<std::unique_ptr<AccountState_Base>, static_cast<int>(Account_State_t::ACCOUNT_COUNT)>;
	private:
		MultiKeyIndexMap1<int, std::string, std::unique_ptr<LoginAccount>, true> accounts_;
		AccountStateArray states_;
	public:
		LoginAccountManager();
		~LoginAccountManager() = default;

		void CreateAccount(TcpConnection* conn);
		void RemoveAccount(TcpConnection* conn);

		void AddAccount2FdInfo(const std::string& account_name, int fd)
		{
			accounts_.SetFKey2PKey(account_name, fd);
		}
		void RemoveAccount2FdInfo(const std::string& account_name)
		{
			accounts_.EraseForeignKeyOnly(account_name);
		}

		AccountState_Base* GetAccountState(Account_State_t account_state) { return states_[static_cast<int>(account_state)].get(); }
		LoginAccount* GetAccountByAccountName(const std::string& account_name);
	private:
		void InitAccountState();

		template<class T>
		void ProcessMessageByfd(int fd, T* msg);
		template<class T>
		void ProcessMessageByAccountName(const std::string& account_name, T* msg);

		void OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgReqLoginCL* msg);
		void OnMessage_ServerListML(packet_ss::MsgServerListML* msg);
		void OnMessage_SelectServerCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgSelectServerCL* msg);
		void OnMessage_ReqEnterServerResultSL(packet_ss::MsgReqEnterServerResultSL* msg);
		void OnMessage_QuitLoginCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgQuitLoginCL* msg);
	};

	template<class T>
	void LoginAccountManager::ProcessMessageByfd(int fd, T* msg)
	{
		auto ptr = accounts_.GetValueByPrimaryKey(fd);
		if (!ptr)
		{
			assert(0);
			return;
		}
		LoginAccount* account = (*ptr).get();
		AccountState_Base* state = account->get_current_state();
		state->HandleMessage(*account, msg);
	}

	template<class T>
	void LoginAccountManager::ProcessMessageByAccountName(const std::string& account_name, T* msg)
	{
		LoginAccount* account = GetAccountByAccountName(account_name);
		if (!account)
		{
			assert(0);
			return;
		}
		AccountState_Base* state = account->get_current_state();
		state->HandleMessage(*account, msg);
	}
}