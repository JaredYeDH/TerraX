#pragma once

#include <cstdint>

namespace dataset
{
	enum
	{
		prop_null = 0,
		prop_unicast = 1,
		prop_multicast = 1 << 1,

		prop_readonly = 1 << 2,
		prop_save = 1 << 3,

		prop_role = 1 << 4,
	};

	enum
	{
		TYPE_NULL,					//"null"
		TYPE_INT8	= 1,			//"int8"
		TYPE_UINT8	= 2,			//"uint8"
		TYPE_INT16	= 3,			//"int16"
		TYPE_UINT16 = 4,			//"uint16"
		TYPE_INT32	= 5,			//"int32"
		TYPE_UINT32 = 6,			//"uint32"
		TYPE_INT64	= 7,			//"int64"
		TYPE_UINT64 = 8,			//"uint64"
		TYPE_FLOAT	= 9,			//"float"
		TYPE_DOUBLE = 10,			//"double"
		TYPE_CHAR16 = 11,			//"char16"
		TYPE_CHAR32 = 12,			//"char32"
		TYPE_CHAR64 = 13,			//"char64"
		TYPE_CHAR128 = 14,			//"char128"
		TYPE_CHAR256 = 15,			//"char256"
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
		static bool CheckPropertyFlag(int property_flag, int flag)
		{
			if (flag == prop_null)
			{
				return true;
			}
			if (property_flag & flag)
			{
				return true;
			}
			return false;
		}
	};
}