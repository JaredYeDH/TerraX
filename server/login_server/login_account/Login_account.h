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
		std::string password_;
		std::string token_;
		int fd_{ 0 };
		TcpConnection* conn_{ nullptr };

	public:
		LoginAccount();
		~LoginAccount(); 

		void EnterState(Account_State_t account_state);
	};
}