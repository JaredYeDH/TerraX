#pragma once

#include "base/types.h"
#include "base/module_interface.h"
#include "db_net_module.h"
//#include <vector>
namespace terra
{
	class DBServer final : public IModule
	{
		DISABLE_COPY(DBServer);
		MAKE_INSTANCE(DBServer);

	public:
		DBServer() = default;
		~DBServer() = default;

		bool Init() override;
		bool AfterInit() override;
		bool Tick() override;
		bool BeforeShut() override;
		bool Shut() override;

	private:
		bool exit_{ false };
	};
}