#pragma once

#include "property.h"
#include <cassert>
#include <type_traits>
#include <string.h>

namespace dataset
{
	// pod type
	struct Property
	{
		void Init(const char* prop_name, int prop_typeid, int prop_flag)
		{
			assert(strlen(prop_name) < 32);
			strcpy(this->prop_name, prop_name);
			this->prop_typeid = prop_typeid;
			this->prop_flag = prop_flag;
		}

		char prop_name[32];
		int prop_typeid;
		int prop_flag;
	};

	static_assert(std::is_pod<Property>::value, "property must be pod_type");
}