#pragma once
#include "base/types.h"
#include "comm/proto/base_type.pb.h"
#include "comm/net/tcp_connection.h"
using namespace pb_base;
namespace terra
{
    class WorldServerObject
    {
    private:
        int server_uid_{0};
        int region_showindex_{0};
        std::string region_name_;
		int server_showindex_{ 0 };
		std::string server_name_;
        ServerStatus status_{ pb_base::MAINTAIN};
        bool recommond_new_{false};
        bool recommond_hot_{false};
		TcpConnection* conn_{ nullptr };
    public:
        WorldServerObject(int server_uid, int region_showindex, const char* region_name,
                          int server_showindex, const char* server_name, int status, bool recommond_new, bool recommond_hot);
        ~WorldServerObject() = default;

		void InitTcpConnection(TcpConnection* conn) { conn_ = conn; }

		void RefreshWorldServerInfo(ServerStatus status) 
		{ 
			status_ = status;
			CONSOLE_DEBUG_LOG(LEVEL_INFO, "server status: %d", status);
		}

        int get_server_uid() const { return server_uid_; }
		int get_region_showindex() const { return region_showindex_; }
		const std::string& get_region_name() const { return region_name_; }
		int get_server_showindex() const { return server_showindex_; }
		const std::string& get_server_name() const { return server_name_; }
		ServerStatus get_server_status() const { return status_; }
		bool get_recommond_new() const { return recommond_new_; }
		bool get_recommond_hot() const { return recommond_hot_; }
    };
}