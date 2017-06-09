#pragma once
#include "base/types.h"
#include "login_account_state.h"

namespace terra
{
	class TcpConnection;
	class LoginAccount
	{
	private:
		std::string account_name_;
		std::string token_;

		TcpConnection* conn_{ nullptr };
		int fd_{ 0 };
		AccountState_Base* account_state_{ nullptr };
	public:
		LoginAccount(TcpConnection* conn);
		~LoginAccount() = default;

		void EnterDefaultState();
		void EnterState(Account_State_t state);

		AccountState_Base* get_current_state() { return account_state_; }
		void set_account_name(const std::string& account_name) { account_name_ = account_name; }
		const std::string& get_account_name() { return account_name_; }
		const std::string& get_token() { return token_; }
		TcpConnection* get_conn() { return conn_; }
	};
}