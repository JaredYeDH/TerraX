#include "server_table.h"
#include <algorithm>
using namespace terra;

NetObject* ServerTable::GetNetObjectByServerID(int server_id)
{
	for (auto& val : servers_)
	{
		if (val.server_id_ == server_id)
		{
			return &val;
		}
	}
	return nullptr;
}

NetObject* ServerTable::GetNetObjectByFD(int fd)
{
	for (auto& val : servers_)
	{
		if (val.fd_ == fd)
		{
			return &val;
		}
	}
	return nullptr;
}

NetObject* ServerTable::GetNetObjectByConn(TcpConnection* conn)
{
	for (auto& val : servers_)
	{
		if (val.conn_ == conn)
		{
			return &val;
		}
	}
	return nullptr;
}

void ServerTable::AddServerInfo(PeerType_t peer, int server_id, const char* listen_ip, int listen_port, TcpConnection* conn)
{
	NetObject net_obj(peer, server_id, listen_ip, listen_port, conn->get_fd(), conn);
	if (addcb_)
	{
		addcb_(servers_, net_obj);
	}
	servers_.push_back(net_obj);
}

void ServerTable::RemoveByServerID(int server_id)
{
	auto iter = std::find_if(servers_.begin(), servers_.end(),
		[server_id](const NetObject& obj) {
		return obj.server_id_ == server_id;
	});
	if(iter != servers_.end())
	{
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
		servers_.erase(iter);
	}
}

void ServerTable::RemoveByFD(int fd)
{
	auto iter = std::find_if(servers_.begin(), servers_.end(),
		[fd](const NetObject& obj) {
		return obj.fd_ == fd;
	});
	if (iter != servers_.end())
	{
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
		servers_.erase(iter);
	}
}

void ServerTable::RemoveByConn(TcpConnection* conn)
{
	auto iter = std::find_if(servers_.begin(), servers_.end(),
		[conn](const NetObject& obj) {
		return obj.conn_ == conn;
	});
	if (iter != servers_.end())
	{
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
		servers_.erase(iter);
	}
}