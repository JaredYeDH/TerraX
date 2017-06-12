#include "comm/config/jsonstream.h"
#include "comm/net/packet_dispatcher.h"
#include "world_server_manager.h"

using namespace terra;
using namespace packet_ss;

WorldServerManager::WorldServerManager()
{
    REG_PACKET_HANDLER_ARG3(MsgLogin2MasterWM, this, OnMessage_Login2MasterWM);
}

void WorldServerManager::LoadWorldConfig(const std::string& path)
{
    JsonStream js;
    Document& doc = js.LoadFile(path);
    assert(doc.HasMember("server_profile"));
    assert(doc["server_profile"].IsArray());
    for (const auto& val : doc["server_profile"].GetArray()) {
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

void WorldServerManager::OnMessage_Login2MasterWM(TcpConnection* conn, int32_t avatar_id,
                                                  MsgLogin2MasterWM* msg)
{
    int server_uid = msg->server_uid();
    auto iter = world_server_map_.find(server_uid);
    assert(iter != world_server_map_.end());
    iter->second.InitTcpConnection(conn);
    iter->second.RefreshWorldServerInfo(FREE);
}