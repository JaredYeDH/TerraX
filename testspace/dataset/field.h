#pragma once

#include "property.h"
#include <cstdint>

namespace dataset
{
	class Field
	{
	private:
		Property prop_;
		uint32_t offset_{ 0 };
		uint32_t data_size_{ 0 };
	public:
		Field(Property& prop, int data_size, int offset)
		{
			memcpy(&prop_, &prop, sizeof prop);
			data_size_ = data_size;
			offset_ = offset;
		}

		Property& get_property() { return prop_; }

		template <typename T>
		T GetValue(char* data_buffer)
		{
			assert(sizeof(T) == data_size_);
			return *((T*)(data_buffer + offset_));
		}
		char* GetValueString(char* data_buffer) { return data_buffer + offset_; }

		template <typename T>
		void SetValue(T& value, char* pDataBuffer)
		{
			assert(sizeof(T) == data_size_);
			*((T*)(pDataBuffer + offset_)) = value;
		}
		void SetValueString(const char* val, char* data_buffer)
		{
			std::size_t len = strlen(val);
			assert(len + 1 < data_size_);
			memcpy(data_buffer, val, len);
		}
	};
}