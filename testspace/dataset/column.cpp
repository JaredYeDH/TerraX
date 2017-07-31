#include "column.h"
#include "property_define.h"
using namespace dataset;

void Column::InitProperty(Document& d)
{
	for (Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
		auto val = d[itr->name].GetObject();
		assert(d.IsObject() && val.HasMember("field_name"));
		assert(d.IsObject() && val.HasMember("type_id"));
		assert(d.IsObject() && val.HasMember("flag"));
		InitProperty(val["field_name"].GetString(), val["type_id"].GetInt(), val["flag"].GetInt());
	}
}


Field* Column::GetField(const char* field_name)
{
	return GetField(GetFieldIndex(field_name));
}

Field* Column::GetField(uint32_t index)
{
	if (index >= 0 && index < fields_.size()) {
		return &fields_[index];
	}
	return nullptr;
}

int Column::GetFieldIndex(const char* field_name) const
{
	auto& iter = name2index_.find(field_name);
	if (iter != name2index_.end()) {
		return iter->second;
	}
	return -1;
}

void Column::InitProperty(const char* prop_name, int prop_typeid, int prop_flag)
{
	assert(name2index_.find(prop_name) == name2index_.end());
	name2index_[prop_name] = static_cast<int>(fields_.size());
	int data_size = PropertyUtil::GetPropertyDataSizeByTypeID(prop_typeid);
	Property prop;
	prop.Init(prop_name, prop_typeid, prop_flag);
	fields_.emplace_back(Field(prop, data_size, data_size_));
	data_size_ += data_size;
}