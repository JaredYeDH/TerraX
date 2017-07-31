#pragma once
#include <map>
#include <vector>
#include "field.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;
namespace dataset
{
	class Column
	{
	private:
		int data_size_{ 0 };
		std::map<std::string, int> name2index_;
		std::vector<Field> fields_;

	public:
		void InitProperty(Document& d);
		int get_data_size() const { return data_size_; }
		int get_field_count() const { return static_cast<int>(fields_.size()); }

		Field* GetField(const char* field_name);
		Field* GetField(uint32_t index);
		int GetFieldIndex(const char* field_name) const;

	private:
		void InitProperty(const char* prop_name, int prop_typeid, int prop_flag);
	};
}