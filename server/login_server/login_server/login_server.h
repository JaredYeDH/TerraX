#pragma once

#include "base/types.h"
#include "base/module_interface.h"

namespace terra
{
	class LoginServer final : public IModule
	{
		DISABLE_COPY(LoginServer);
		MAKE_INSTANCE(LoginServer);

	public:
		LoginServer() = default;
		~LoginServer() = default;

		bool Init() override;
		bool AfterInit() override;
		bool Tick() override;
		bool BeforeShut() override;
		bool Shut() override;

	private:
		bool exit_{ false };
	};
}