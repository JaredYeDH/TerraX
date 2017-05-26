#pragma once
#include <functional>
#include <map>
#include <vector>
#include "base/types.h"
#include "comm/net/net_define.h"
#include "comm/net/tcp_connection.h"
namespace terra
{
    struct NetObject {
        NetObject(PeerType_t peer_type, int server_id, const char* listen_ip, int listen_port, int fd,
                  TcpConnection* conn)
            : peer_type_(peer_type),
              server_id_(server_id),
              listen_port_(listen_port),
              fd_(conn->get_fd()),
              conn_(conn)
        {
            int len = strlen(listen_ip);
            assert(len < 32);
            if (len > 0 && len < 32) {
                memcpy(listen_ip_, listen_ip, strlen(listen_ip));
            }
        }

        PeerType_t peer_type_{PeerType_t::UNDEFINE};
        int server_id_{0};
        char listen_ip_[32]{0};
        int listen_port_{0};
        int fd_{0};
        TcpConnection* conn_{nullptr};
    };

    using AddNetObjectCB = std::function<void(const std::vector<NetObject>&, const NetObject&)>;
    using RemoveNetObjectCB = std::function<void(const std::vector<NetObject>&, const NetObject&)>;
    class ServerTable
    {
        DISABLE_COPY(ServerTable);

    private:
        PeerType_t self_peer_{PeerType_t::UNDEFINE};
        int self_server_id_{-1};
        std::vector<NetObject> servers_;
        AddNetObjectCB addcb_;
        RemoveNetObjectCB remcb_;

    public:
        ServerTable(){};
        ~ServerTable() = default;

        void InitSelfServerInfo(PeerType_t peer, int server_id)
        {
            self_peer_ = peer;
            self_server_id_ = server_id;
        }

        int get_self_server_id() { return self_server_id_; }
        void SetAddNetObjectEventCB(AddNetObjectCB cb) { addcb_ = cb; }

        NetObject* GetNetObjectByServerID(int server_id);
        NetObject* GetNetObjectByFD(int fd);
        NetObject* GetNetObjectByConn(TcpConnection* conn);

        void AddServerInfo(PeerType_t peer, int server_id, const char* listen_ip, int listen_port,
                           TcpConnection* conn);
        void RemoveByServerID(int server_id);
        void RemoveByFD(int fd);
        void RemoveByConn(TcpConnection* conn);
    };
}