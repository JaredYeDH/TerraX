#include "world_account_manager.h"

using namespace terra;


WorldAccount* WorldAccountManager::FindAccountByAccountName(const std::string& account_name)
{
	auto iter = accounts_.find(account_name);
	if (iter != accounts_.end())
	{
		return (iter->second).get();
	}
	return nullptr;
}