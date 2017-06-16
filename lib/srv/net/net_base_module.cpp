#include "net_base_module.h"
#include "packet_processor.h"

using namespace terra;

NetBaseModule::NetBaseModule(PeerType_t peer) 
	: kSelfPeer(peer),
	packet_processor_(PacketProcessor::GetInstance())
{

}

void NetBaseModule::ProcessServerMessage(TcpConnection* conn, evbuffer* evbuf)
{
	packet_processor_.ProcessServerPacket(conn, evbuf);
}

void NetBaseModule::InitConnectInfo(const std::string& ip, int port)
{
	conn_ip_ = ip;
	conn_port_ = port;
}

void NetBaseModule::InitListenInfo(const std::string& ip, int port)
{
	listen_ip_ = ip;
	listen_port_ = port;
}

void NetBaseModule::SendPacket(TcpConnection* conn, google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(conn, msg);
}