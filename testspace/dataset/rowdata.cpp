#include "rowdata.h"
using namespace dataset;

RowData::RowData(Column& col) : col_(col), bitset_(col.get_field_count())
{
    AllocBuffer(col.get_data_size());
}

RowData::~RowData() { delete[] data_buffer_; }

bool RowData::ParseFromString(const char* buffer, int size, int flag /*= prop_null*/, bool overwrite /*= false*/)
{
	if (overwrite)
	{
		Reset();
	}
	CharStack<256> readstream;
	Field* cur_field = nullptr;
	bool parse_key = false , parse_value = false;
	for (int i = 0; i <= size; ++i) //until '\0'
	{
		readstream.Push(buffer[i]);
		if (buffer[i] == ':' && parse_key == false)
		{
			//get key
			parse_key = true;
			readstream.Pop();
			int index = col_.GetFieldIndex(readstream.buffer());
			cur_field = col_.GetField(index);
			readstream.Reset();
			continue;
		}
		if (buffer[i] == '"')
		{
			readstream.Pop();
		}
		if (buffer[i] == ',' || buffer[i] == '\0')
		{
			if ()
			{
			}
			//get value
			parse_value == true;
			readstream.Pop();
			const char* val = readstream.buffer();
			if (!cur_field)
			{
				continue;
			}
			Property& prop = cur_field->get_property();
			int prop_typeid = prop.prop_typeid;
			switch (prop_typeid) {
			case TYPE_INT8:
				cur_field->SetValue<int8_t>(ConvertTo<int8_t>(val), data_buffer_);
				break;
			case TYPE_UINT8:
				cur_field->SetValue<uint8_t>(ConvertTo<uint8_t>(val), data_buffer_);
				break;
			case TYPE_INT16:
				cur_field->SetValue<int16_t>(ConvertTo<int16_t>(val), data_buffer_);
				break;
			case TYPE_UINT16:
				cur_field->SetValue<uint16_t>(ConvertTo<uint16_t>(val), data_buffer_);
				break;
			case TYPE_INT32:
				cur_field->SetValue<int32_t>(ConvertTo<int32_t>(val), data_buffer_);
				break;
			case TYPE_UINT32:
				cur_field->SetValue<uint32_t>(ConvertTo<uint32_t>(val), data_buffer_);
				break;
			case TYPE_INT64:
				cur_field->SetValue<int64_t>(ConvertTo<int64_t>(val), data_buffer_);
				break;
			case TYPE_UINT64:
				cur_field->SetValue<uint64_t>(ConvertTo<uint64_t>(val), data_buffer_);
				break;
			case TYPE_FLOAT:
				cur_field->SetValue<float>(ConvertTo<float>(val), data_buffer_);
				break;
			case TYPE_DOUBLE:
				cur_field->SetValue<double>(ConvertTo<double>(val), data_buffer_);
				break;
			case TYPE_CHAR16:
			case TYPE_CHAR32:
			case TYPE_CHAR64:
			case TYPE_CHAR128:
			case TYPE_CHAR256:
				cur_field->SetValueString(val, data_buffer_);
				break;
			default:
				break;
			}
			readstream.Reset();
			continue;
		}
	}
	return true;
}
bool RowData::ParseFromByte(const char* buffer, int size, int flag /*= prop_null*/, bool overwrite /*= false*/)
{
	if (overwrite)
	{
		Reset();
	}
	int start_index = 0;
	while (start_index < size)
	{
		uint16_t index = ParseIndex(buffer, start_index, size);
		start_index += sizeof(uint16_t);
		uint16_t length = ParseLength(buffer, start_index, size);
		start_index += sizeof(uint16_t);
		Field* field = col_.GetField(index);
		if (!field) {
			return false;
		}
		Property& prop = field->get_property();
		if (!PropertyUtil::CheckPropertyFlag(prop.prop_flag, flag))
		{
			start_index += length;
			continue;
		}
		field->ParseFromByte(buffer + start_index, length, data_buffer_);
		start_index += length;
	}
	return true;
}

//t-l-v do not use ',' ':' as delimiter
std::string RowData::SerilizeToByte(int flag /*= prop_null*/, bool only_dirty /*= false*/)
{
	std::string str;
	for (uint16_t i = 0; i < col_.get_field_count(); ++i) {
		Field* field = col_.GetField(i);
		if (!field) {
			continue;
		}
		Property& prop = field->get_property();
		if (!PropertyUtil::CheckPropertyFlag(prop.prop_flag, flag))
		{
			continue;
		}
		if (only_dirty && !CheckDirty(i))
		{
			continue;
		}
		//index[16]:length[16]:value
		str.append((char*)&i, sizeof(uint16_t));
		uint16_t data_size = field->get_data_size();
		str.append((char*)&data_size, sizeof(uint16_t));
		field->SerilizeToByte(str, data_buffer_);
	}
	return str;
}

std::string RowData::SerilizeToString(int flag /*= prop_null*/, bool only_dirty /*= false*/)
{
	std::stringstream ss;
	for (int i = 0; i < col_.get_field_count(); ++i) {
		Field* field = col_.GetField(i);
		if (!field) {
			continue;
		}
		Property& prop = field->get_property();
		if (!PropertyUtil::CheckPropertyFlag(prop.prop_flag, flag))
		{
			continue;
		}
		if (only_dirty && !CheckDirty(i))
		{
			continue;
		}

		ss << prop.prop_name;
		ss << ":";
		int prop_typeid = prop.prop_typeid;
		switch (prop_typeid) {
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
			ss << '"' << field->GetValueString(data_buffer_) << '"';
			break;
		case TYPE_CHAR32:
			ss << '"' << field->GetValueString(data_buffer_) << '"';
			break;
		case TYPE_CHAR64:
			ss << '"' << field->GetValueString(data_buffer_) << '"';
			break;
		case TYPE_CHAR128:
			ss << '"' << field->GetValueString(data_buffer_) << '"';
			break;
		case TYPE_CHAR256:
			ss << '"' << field->GetValueString(data_buffer_) << '"';
			break;
		default:
			break;
		}
		if (i < (col_.get_field_count() - 1)) {
			ss << ",";
		}
	}
	return ss.str();
}


void RowData::AllocBuffer(uint32_t buffer_size) { data_buffer_ = new char[buffer_size]{0}; }

const char* RowData::GetValueString(const char* field_name)
{
    int nFieldIndex = col_.GetFieldIndex(field_name);
    return GetValueString(nFieldIndex);
}

const char* RowData::GetValueString(int index)
{
    Field* field = col_.GetField(index);
    return field->GetValueString(data_buffer_);
}

bool RowData::SetValueString(const char* field_name, const char* pVal)
{
    int nFieldIndex = col_.GetFieldIndex(field_name);
    return SetValueString(nFieldIndex, pVal);
}

bool RowData::SetValueString(int index, const char* pVal)
{
    Field* field = col_.GetField(index);
    if (!field) {
        return false;
    }
    field->SetValueString(pVal, data_buffer_);
    bitset_.set(index);
    return true;
}


bool RowData::CheckDirty(int index)
{
	return bitset_.test(index);
}

void RowData::Reset()
{
	for (int i = 0; i < col_.get_field_count(); ++i)
	{
		Field* field = col_.GetField(i);
		if (!field) {
			continue;
		}
		field->clear_data_size();
	}
	memset(data_buffer_, 0, col_.get_data_size());
}

uint16_t RowData::ParseIndex(const char* buffer, int offset, int buffer_size)
{
	assert(offset + sizeof(uint16_t) <= buffer_size);
	return *(uint16_t*)(buffer + offset);
}

uint16_t RowData::ParseLength(const char* buffer, int offset, int buffer_size)
{
	assert(offset + sizeof(uint16_t) <= buffer_size);
	return *(uint16_t*)(buffer + offset);
}