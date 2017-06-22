#pragma once

#include "base/types.h"
#include "gate_account_state.h"

namespace terra
{
	class TcpConnection;
	class GateAccount
	{
	private:
		std::string account_name_;
		TcpConnection* conn_{ nullptr };
		int fd_{ 0 };
		AccountState_Base* account_state_{ nullptr };
	public:
		GateAccount(TcpConnection* conn);
		~GateAccount() = default;


		void InitAccountName(const std::string& account_name);
		void EnterDefaultState();
		void EnterState(Account_State_t state);

		AccountState_Base* get_current_state() { return account_state_; }
		const std::string& get_account_name() const { return account_name_; }
		TcpConnection* get_conn() { return conn_; }
	};
}