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
		uint32_t max_data_size_{ 0 };
	public:
		Field(Property& prop, int max_data_size, int offset)
		{
			memcpy(&prop_, &prop, sizeof prop);
			max_data_size_ = max_data_size;
			offset_ = offset;
		}

		Property& get_property() { return prop_; }
		uint32_t get_data_size() { return data_size_; }
		void clear_data_size() { data_size_ = 0; }

		template <typename T>
		T GetValue(char* data_buffer)
		{
			assert(sizeof(T) == max_data_size_);
			return *((T*)(data_buffer + offset_));
		}
		char* GetValueString(char* data_buffer) { return data_buffer + offset_; }

		template <typename T>
		void SetValue(T value, char* data_buffer)
		{
			assert(sizeof(T) == max_data_size_);
			data_size_ = max_data_size_;
			*((T*)(data_buffer + offset_)) = value;
		}
		void SetValueString(const char* val, char* data_buffer)
		{
			uint32_t len = static_cast<uint32_t>(strlen(val));
			assert(len < max_data_size_);
			data_size_ = len + 1; //'\0'
			strcpy(data_buffer + offset_, val);
		}

		void SerilizeToByte(std::string& str, char* data_buffer)
		{
			str.append(data_buffer + offset_, data_size_);
		}
		void ParseFromByte(const char* buffer, uint32_t size, char* data_buffer)
		{
			assert(size <= max_data_size_);
			data_size_ = size;
			memcpy(data_buffer + offset_, buffer, size);
		}
	};
}