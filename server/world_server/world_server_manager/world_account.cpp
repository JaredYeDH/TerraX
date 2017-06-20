#include "world_account.h"

using namespace terra;

WorldAccount::WorldAccount(const std::string& account_name, int gate_server_id)
    : account_name_(account_name), gate_server_id_(gate_server_id)
{
}