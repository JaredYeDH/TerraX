#pragma once

#include "base/types.h"
#include <string>

namespace terra
{
	class Guest
	{
		DISABLE_COPY(Guest);
		MAKE_INSTANCE(Guest);
	private:
		std::string account_name_;
		std::string pass_word_;
		std::string login_token_;

	public:
		Guest() = default;
		~Guest() = default;

		void InitAccountInfo(std::string&& account_name, std::string&& password)
		{
			account_name_ = std::move(account_name);
			pass_word_ = std::move(password);
		}
		void set_login_token(const std::string& token)
		{
			login_token_ = token;
		}
		std::string& get_account_name() { return account_name_; }
		std::string& get_password() { return pass_word_; }
		std::string& get_token() { return login_token_; }
	private:
		void EncryptPassword(std::string& password) {};
	};
}