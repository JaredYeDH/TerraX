#pragma once
#include "base/types.h"

namespace terra
{
	class WorldAccount
	{
	private:
		std::string account_name_;
		std::string account_token_;
		int gate_server_id_{ -1 };

	public:
		WorldAccount(const std::string& account_name, int gate_server_id);
		~WorldAccount() = default;

	};
}