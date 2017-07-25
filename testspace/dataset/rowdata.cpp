#include "rowdata.h"
#include "property_define.h"
using namespace dataset;

RowData::RowData(Column& col) : col_(col), bitset_(col.get_field_count())
{
	AllocBuffer(col.get_data_size());
}

RowData::~RowData() { delete[] data_buffer_; }

std::string RowData::ToString()
{
	std::string str;
	std::stringstream ss;
	for (int i = 0; i < col_.get_field_count(); ++i)
	{
		Field* field = col_.GetField(i);
		if (!field)
		{
			continue;
		}
		Property& prop = field->get_property();
		ss << prop.prop_name;
		ss << ":";
		int prop_typeid = prop.prop_typeid;
		switch (prop_typeid)
		{
		case TYPE_INT8:
			ss << field->GetValue<int8_t>(data_buffer_);
			break;
		case TYPE_UINT8:
			ss << field->GetValue<uint8_t>(data_buffer_);
			break;
		case TYPE_INT16:
			ss << field->GetValue<int16_t>(data_buffer_);
			break;
		case TYPE_UINT16:
			ss << field->GetValue<uint16_t>(data_buffer_);
			break;
		case TYPE_INT32:
			ss << field->GetValue<int32_t>(data_buffer_);
			break;
		case TYPE_UINT32:
			ss << field->GetValue<uint32_t>(data_buffer_);
			break;
		case TYPE_INT64:
			ss << field->GetValue<int64_t>(data_buffer_);
			break;
		case TYPE_UINT64:
			ss << field->GetValue<uint64_t>(data_buffer_);
			break;
		case TYPE_FLOAT:
			ss << field->GetValue<float>(data_buffer_);
			break;
		case TYPE_DOUBLE:
			ss << field->GetValue<double>(data_buffer_);
			break;
		case TYPE_CHAR16:
			ss << field->GetValueString(data_buffer_);
			break;
		case TYPE_CHAR32:
			ss << field->GetValueString(data_buffer_);
			break;
		case TYPE_CHAR64:
			ss << field->GetValueString(data_buffer_);
			break;
		case TYPE_CHAR128:
			ss << field->GetValueString(data_buffer_);
			break;
		case TYPE_CHAR256:
			ss << field->GetValueString(data_buffer_);
			break;
		default:
			break;
		}
		if (i < (col_.get_field_count() - 1))
		{
			ss << ",";
		}
	}
	ss >> str;
	return str;
}

void RowData::AllocBuffer(uint32_t buffer_size)
{
	data_buffer_ = new char[buffer_size] {0};
}