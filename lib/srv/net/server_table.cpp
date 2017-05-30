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
	servers_.push_back(net_obj);
	if (addcb_)
	{
		addcb_(servers_, net_obj);
	}
	//PrintServerTable();
}

void ServerTable::RemoveByServerID(int server_id)
{
	auto iter = std::find_if(servers_.begin(), servers_.end(),
		[server_id](const NetObject& obj) {
		return obj.server_id_ == server_id;
	});
	if(iter != servers_.end())
	{
		servers_.erase(iter);
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
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
		servers_.erase(iter);
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
	}
}

void ServerTable::RemoveByConn(TcpConnection* conn)
{
	assert(conn);
	auto iter = std::find_if(servers_.begin(), servers_.end(),
		[conn](const NetObject& obj) {
		return obj.conn_ == conn;
	});
	if (iter != servers_.end())
	{
		servers_.erase(iter);
		if (remcb_)
		{
			remcb_(servers_, *iter);
		}
	}
}

void ServerTable::PrintServerTable()
{
#ifndef NDEBUG
	CONSOLE_DEBUG_LOG(LEVEL_WARNING, "%s", __FUNCTION__);
	for (auto& val : servers_)
	{
		CONSOLE_DEBUG_LOG(LEVEL_INFO, "%s %d %s %d %d", NetHelper::ServerName(val.peer_type_), val.server_id_, val.listen_ip_, val.listen_port_, val.fd_);
	}
#endif // !NDEBUG
}