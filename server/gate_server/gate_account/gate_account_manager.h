#pragma once

#include "base/types.h"
#include "base/multi_index_map.h"
#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"
#include "srv/net/server_accept_service.h"
#include "gate_account_state.h"
#include <unordered_map>
#include <memory>
#include <array>
#include "gate_account.h"

namespace terra
{
	class GateAccountManager
	{
		MAKE_INSTANCE(GateAccountManager);
		DISABLE_COPY(GateAccountManager);
		using AccountStateArray = std::array<std::unique_ptr<AccountState_Base>, static_cast<int>(Account_State_t::ACCOUNT_COUNT)>;
	private:
		MultiKeyIndexMap1<int, std::string, std::unique_ptr<GateAccount>, true> accounts_;

		AccountStateArray states_;
	public:
		GateAccountManager();
		~GateAccountManager() = default;

		void CreateAccount(TcpConnection* conn);
		void RemoveAccount(TcpConnection* conn);

		void AddAccount2FdInfo(const std::string& account_name, int fd);
		void RemoveAccount2FdInfo(const std::string& account_name);

		AccountState_Base* GetAccountState(Account_State_t account_state) { return states_[static_cast<int>(account_state)].get(); }
		GateAccount* GetAccountByAccountName(const std::string& account_name);
	private:
		void InitAccountState();

		template<class T>
		void ProcessMessageByfd(int fd, T* msg);
		template<class T>
		void ProcessMessageByAccountName(const std::string& account_name, T* msg);

		void OnMessage_ReqLoginGameCS(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgReqLoginGameCS* msg);
	};

	template<class T>
	void GateAccountManager::ProcessMessageByfd(int fd, T* msg)
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
	void GateAccountManager::ProcessMessageByAccountName(const std::string& account_name, T* msg)
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