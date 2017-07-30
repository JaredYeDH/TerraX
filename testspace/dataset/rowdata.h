#pragma once

#include <sstream>
#include "column.h"
#include "dynamic_bitset.h"
#include "macro.h"
#include "property_define.h"
#include <stack>
using namespace terra;
namespace dataset
{
	template<typename OutType>
	OutType ConvertTo(const char* data)
	{
		OutType out;
		std::stringstream ss;
		ss << data;
		ss >> out;
		return out;
	}

    template <int SIZE>
    class CharStack
    {
    private:
        char buf_[SIZE];
        int cur_index;

    public:
        CharStack() { Reset(); }

        bool Push(char c)
        {
            if (cur_index >= SIZE) {
				return false;
            }
			buf_[cur_index++] = c;
			return true;
        }
		bool Pop()
		{
			if (cur_index <= 0)
			{
				return false;
			}
			buf_[--cur_index] = '\0';
			return true;
		}
		char Top()
		{
			return buf_[cur_index];
		}
		void Reset() { 
			cur_index = 0;
			memset(buf_, 0, sizeof(buf_));
		}
        const char* buffer() const { return buf_; }
		int size() const { return cur_index + 1; }
    };

    class RowData
    {
        DISABLE_COPY(RowData);
        // using ValueChangeCB = std::function<void()>;
    private:
        Column& col_;
        char* data_buffer_{nullptr};
        dynamic_bitset bitset_;

    public:
        RowData(Column& col);
        ~RowData();

        // void RegValueChangeCB()
        std::string SerilizeToString(int flag = prop_null, bool only_dirty = false);
        bool ParseFromString(const char* buffer, int size, int flag = prop_null, bool overwrite = false);

        std::string SerilizeToByte(int flag = prop_null, bool only_dirty = false);
        bool ParseFromByte(const char* buffer, int size, int flag = prop_null, bool overwrite = false);

        template <typename T>
        bool GetValue(const char* field_name, T& val);
        template <typename T>
        bool GetValue(int index, T& val);

        template <typename T>
        bool SetValue(const char* field_name, T val);
        template <typename T>
        bool SetValue(int index, T val);

        const char* GetValueString(const char* field_name);
        const char* GetValueString(int index);

        bool SetValueString(const char* field_name, const char* pVal);
        bool SetValueString(int index, const char* pVal);

        void ClearDirty() { bitset_.reset(); }

    private:
        void AllocBuffer(uint32_t buffer_size);
        bool CheckDirty(int index);
        void Reset();
        uint16_t ParseIndex(const char* buffer, int offset, int buffer_size);
        uint16_t ParseLength(const char* buffer, int offset, int buffer_size);
    };

    template <typename T>
    bool RowData::GetValue(const char* field_name, T& val)
    {
        int nFieldIndex = col_.GetFieldIndex(field_name);
        return GetValue<T>(nFieldIndex, val);
    }
    template <typename T>
    bool RowData::GetValue(int index, T& val)
    {
        Field* field = col_.GetField(index);
        if (!field) {
            return false;
        }
        val = field->GetValue<T>(data_buffer_);
        return true;
    }

    template <typename T>
    bool RowData::SetValue(const char* field_name, T val)
    {
        int nFieldIndex = col_.GetFieldIndex(field_name);
        return SetValue<T>(nFieldIndex, val);
    }
    template <typename T>
    bool RowData::SetValue(int index, T val)
    {
        Field* field = col_.GetField(index);
        if (!field) {
            return false;
        }
        field->SetValue<T>(val, data_buffer_);
        bitset_.set(index);
        return true;
    }
}