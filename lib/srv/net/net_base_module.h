#pragma once

#include "base/types.h"
#include "comm/net/eventloop.h"
#include "comm/net/tcp_connection.h"
#include "comm/net/tcp_server.h"
#include "server_table.h"
#include "packet_processor.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class NetBaseModule
	{
	protected:
		const PeerType_t kSelfPeer;
		EventLoop loop_;
		PacketProcessor& packet_processor_;
	public:
		NetBaseModule(PeerType_t peer);
		virtual ~NetBaseModule(){}

		PeerType_t get_peer_type() const { return kSelfPeer; }
		EventLoop* get_event_loop() { return &loop_; }

		void SendPacket(TcpConnection* conn, google::protobuf::Message& msg);

		virtual void ProcessServerMessage(TcpConnection* conn, evbuffer* evbuf);
	};

}