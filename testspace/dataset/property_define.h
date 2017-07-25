#pragma once

#include <cstdint>

namespace dataset
{
	enum
	{
		prop_unicast = 1,
		prop_multicast = 1 << 1,

		prop_readonly = 1 << 2,
		prop_save = 1 << 3,

		prop_triggercallback = 1 << 4,

		prop_role = 1 << 5,
	};

	enum
	{
		TYPE_NULL,			//"null"
		TYPE_INT8,			//"int8"
		TYPE_UINT8,			//"uint8"
		TYPE_INT16,			//"int16"
		TYPE_UINT16,		//"uint16"
		TYPE_INT32,			//"int32"
		TYPE_UINT32,		//"uint32"
		TYPE_INT64,			//"int64"
		TYPE_UINT64,		//"uint64"
		TYPE_FLOAT,			//"float"
		TYPE_DOUBLE,		//"double"
		TYPE_CHAR16,		//"char16"
		TYPE_CHAR32,		//"char32"
		TYPE_CHAR64,		//"char64"
		TYPE_CHAR128,		//"char128"
		TYPE_CHAR256,		//"char256"
	};

	class PropertyUtil
	{
	public:
		static int GetPropertyDataSizeByTypeID(int prop_typeid)
		{
			switch (prop_typeid)
			{
			case TYPE_INT8: return sizeof(int8_t);
			case TYPE_UINT8: return sizeof(uint8_t);
			case TYPE_INT16: return sizeof(int16_t);
			case TYPE_UINT16: return sizeof(uint16_t);
			case TYPE_INT32: return sizeof(int32_t);
			case TYPE_UINT32: return sizeof(uint32_t);
			case TYPE_INT64: return sizeof(int64_t);
			case TYPE_UINT64: return sizeof(uint64_t);
			case TYPE_FLOAT: return sizeof(float);
			case TYPE_DOUBLE: return sizeof(double);
			case TYPE_CHAR16: return 16;
			case TYPE_CHAR32: return 32;
			case TYPE_CHAR64: return 64;
			case TYPE_CHAR128: return 128;
			case TYPE_CHAR256: return 256;
				break;
			default:
				break;
			}
			return 0;
		}
	};
}