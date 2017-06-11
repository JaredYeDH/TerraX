#pragma once

#include "base/types.h"
#include "base/module_interface.h"

namespace terra
{
	class MasterServer final : public IModule
	{
		DISABLE_COPY(MasterServer);
		MAKE_INSTANCE(MasterServer);

	public:
		MasterServer() = default;
		~MasterServer() = default;

		bool Init() override;
		bool AfterInit() override;
		bool Tick() override;
		bool BeforeShut() override;
		bool Shut() override;

	private:
		bool exit_{ false };
	};
}