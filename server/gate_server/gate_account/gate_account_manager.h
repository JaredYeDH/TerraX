#pragma once

#include "base/types.h"
#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"
#include "srv/net/server_accept_service.h"
#include "gate_account_state.h"
#include <unordered_map>
#include <memory>
#include <array>

namespace terra
{
	class GateAccount;
	class GateAccountManager
	{
		MAKE_INSTANCE(GateAccountManager);
		DISABLE_COPY(GateAccountManager);
		using GateAccountMap = std::unordered_map<int, std::unique_ptr<GateAccount> >;
		using Account2FdMap = std::unordered_map<std::string, int >;
		using AccountStateArray = std::array<std::unique_ptr<AccountState_Base>, static_cast<int>(Account_State_t::ACCOUNT_COUNT)>;
	private:
		GateAccountMap account_map_;
		Account2FdMap account2fd_map_;

		AccountStateArray states_;
	public:
		GateAccountManager();
		~GateAccountManager() = default;

		void CreateAccount(TcpConnection* conn);
		void RemoveAccount(TcpConnection* conn);

		void AddAccount2FdInfo(const std::string& account_name, int fd)
		{
			account2fd_map_.insert(std::make_pair(account_name, fd));
		}
		void RemoveAccount2FdInfo(const std::string& account_name)
		{
			account2fd_map_.erase(account_name);
		}

		AccountState_Base* GetAccountState(Account_State_t account_state) { return states_[static_cast<int>(account_state)].get(); }
		GateAccount* GetAccountByAccountName(const std::string& account_name);
	private:
		void InitAccountState();
	};
}