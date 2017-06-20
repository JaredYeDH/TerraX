#pragma once
#include "base/types.h"
#include "comm/proto/base_type.pb.h"
#include "comm/net/tcp_connection.h"
using namespace pb_base;
namespace terra
{
	class LoginServerObject
	{
	private:
		TcpConnection* conn_{ nullptr };
	public:
		LoginServerObject(TcpConnection* conn);
		~LoginServerObject() = default;

		TcpConnection* get_conn() { return conn_; }
	};
}