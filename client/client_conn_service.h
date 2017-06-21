#pragma once
#include <memory>
#include "comm/net/tcp_connection.h"
#include "client_net_module.h"


namespace terra
{
	class IPInfo
	{
	public:
		std::string ip_;
		int port_{ 0 };

		IPInfo() = default;
		~IPInfo() = default;
		IPInfo(std::string&& ip, int port) :
			ip_(ip), port_(port)
		{
		}
	};
	class ClientConnService
	{
		MAKE_INSTANCE(ClientConnService);
		DISABLE_COPY(ClientConnService);

	private:
		ClientNetModule* net_;
		ClientPacketProcessor& packet_processor_;
		std::vector<std::unique_ptr<TcpConnection>> conns_;
		std::vector<IPInfo> login_info_;
		IPInfo gate_info_;
		TcpConnection* login_conn_{ nullptr };
		TcpConnection* gate_conn_{ nullptr };
	public:
		ClientConnService();
		~ClientConnService();

		void InitNetModule(ClientNetModule* net) { net_ = net; }
		void SetGateIpPort(const std::string& ip, int port) 
		{ 
			gate_info_.ip_ = ip;
			gate_info_.port_ = port;
		}
		void LoadLoginServerInfo(const std::string& path);

		void Connect2Login();
		void Connect2Gate();

		void SendPacket2LoginServer(google::protobuf::Message& msg);
		void SendPacket2GateServer(google::protobuf::Message& msg);

		TcpConnection* Connect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);

		void ProcessLoginMessage(TcpConnection* conn, evbuffer* evbuf);
		void ProcessGateMessage(TcpConnection* conn, evbuffer* evbuf);

		void OnLoginConnected(TcpConnection* conn);
		void OnLoginDisconnected(TcpConnection* conn);

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);

	private:
		void DestroyConnection(TcpConnection* conn);
	};
}