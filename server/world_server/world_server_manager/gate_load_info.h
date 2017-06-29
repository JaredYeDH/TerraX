#include "base/types.h"

namespace terra
{
	class GateLoadInfo
	{
	private:
		int server_id{ 0 };
		int account_count_{ 0 };

	public:
		int get_account_count() const { return account_count_; }
	};
}