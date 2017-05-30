#pragma once

#include "base/types.h"
#include "base/module_interface.h"

namespace terra
{
	class Client final : public IModule
	{
		DISABLE_COPY(Client);
		MAKE_INSTANCE(Client);

	public:
		Client() = default;
		~Client() = default;

		bool Init() override;
		bool AfterInit() override;
		bool Tick() override;
		bool BeforeShut() override;
		bool Shut() override;

	private:
		bool exit_{ false };
	};
}