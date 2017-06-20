#include "comm/config/jsonstream.h"
#include "comm/net/packet_dispatcher.h"
#include "server_manager.h"
#include "master_net_module.h"

using namespace terra;
using namespace packet_ss;

ServerManager::ServerManager()
{
}

void ServerManager::LoadWorldConfig(const std::string& path)
{
    JsonStream js;
    Document* doc = js.LoadFile(path);
	assert(doc);
    assert(doc->HasMember("server_profile"));
    assert((*doc)["server_profile"].IsArray());
    for (const auto& val : (*doc)["server_profile"].GetArray()) {
        int server_uid = val["server_uid"].GetInt();
        int region_showindex = val["region_showindex"].GetInt();
        const char* region_name = val["region_name"].GetString();
        int server_showindex = val["server_showindex"].GetInt();
        const char* server_name = val["server_name"].GetString();
        int server_status = val["server_status"].GetInt();
        bool recommond_new = val["recommond_new"].GetBool();
        bool recommond_hot = val["recommond_hot"].GetBool();
        world_server_map_.emplace(std::make_pair(
            server_uid, WorldServerObject(server_uid, region_showindex, region_name, server_showindex,
                                          server_name, server_status, recommond_new, recommond_hot)));
    }
}

void ServerManager::CreateLoginServerObj(TcpConnection* conn)
{
	login_server_map_.emplace(std::make_pair(conn->get_fd(), LoginServerObject()));
}

void ServerManager::RemoveLoginServerObj(TcpConnection* conn)
{
	login_server_map_.erase(conn->get_fd());
}

WorldServerObject* ServerManager::FindWorldServerByUID(int server_uid)
{
	auto iter = world_server_map_.find(server_uid);
	assert(iter != world_server_map_.end());
	if (iter != world_server_map_.end())
	{
		return &(iter->second);
	}
	return nullptr;
}

LoginServerObject* ServerManager::FindLoginServerById(int login_server_id)
{
	auto iter = login_server_map_.find(login_server_id);
	assert(iter != login_server_map_.end());
	if (iter != login_server_map_.end())
	{
		return &(iter->second);
	}
	return nullptr;
}