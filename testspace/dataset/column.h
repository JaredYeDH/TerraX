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
		std::size_t get_data_size() const { return data_size_; }
		std::size_t get_field_count() const { return fields_.size(); }

		Field* GetField(uint32_t index);
		int GetFieldIndex(const char* field_name) const;

	private:
		void InitProperty(const char* prop_name, int prop_typeid, int prop_flag);
	};
}