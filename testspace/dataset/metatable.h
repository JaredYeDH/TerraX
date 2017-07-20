#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <sstream>
#include "dynamic_bitset.h"
#include "macro.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;
namespace terra
{
	struct Property
	{
		void Init(const char* name, const char* type, int pub, int pri, int sv)
		{
			assert(strlen(name) < 32);
			strcpy(prop_name, name);
			assert(strlen(type) < 32);
			strcpy(prop_type, type);
			prop_public = pub;
			prop_private = pri;
			prop_save = sv;
		}
		const char* get_prop_name() { return prop_name; }
		const char* get_prop_type() { return prop_type; }
		char prop_name[32];
		char prop_type[32];
		int prop_public;
		int prop_private;
		int prop_save;
	};


	template <class PropertyT>
    class Field
	{
	private:
		PropertyT prop_;
		int offset_{ 0 };
		std::size_t data_size_{ 0 };
    public:
        Field(PropertyT& prop, int data_size, int offset)
        {
			memcpy(&prop_ , &prop, sizeof prop);
            data_size_ = data_size;
            offset_ = offset;
        }

		const PropertyT& get_property() { return prop_; }

        template <typename T>
        T GetValue(char* data_buffer)
        {
            assert(sizeof(T) == data_size_);
            return *((T*)(data_buffer + offset_));
        }
        char* GetValueString(char* databuffer) { return databuffer + offset_; }

        template <typename T>
        void SetValue(T& value, char* pDataBuffer)
        {
            assert(sizeof(T) == data_size_);
            *((T*)(pDataBuffer + offset_)) = value;
        }
        void SetValueString(const char* val, char* pDataBuffer)
        {
            std::size_t len = strlen(val);
            if (len > data_size_) {
                len = data_size_;
            }
            memcpy(pDataBuffer, val, len);
        }
    };

    template <class PropertyT>
    class Column
    {
    public:
        void InitProperty(Document& d) {}
        int get_data_size() const { return 0; }
        int get_field_count() const { return 0; }
        Field<PropertyT>* GetField(std::size_t index) { return nullptr; }
        int GetFieldIndex(const char* field_name) const { return -1; }
    };
    template <>
    class Column<Property>
	{
		//DISABLE_COPY(Column);
    private:
        int data_size_{0};
        std::map<std::string, int> name2index_;
        std::vector<Field<Property>> fields_;

    public:
        void InitProperty(Document& d)
        {
            for (Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
                auto val = d[itr->name].GetObject();
                assert(d.IsObject() && val.HasMember("Field_Name"));
                assert(d.IsObject() && val.HasMember("Type"));
                assert(d.IsObject() && val.HasMember("Public"));
                assert(d.IsObject() && val.HasMember("Private"));
                assert(d.IsObject() && val.HasMember("Save"));
                InitProperty(val["Field_Name"].GetString(), val["Type"].GetString(), val["Public"].GetInt(),
                             val["Private"].GetInt(), val["Save"].GetInt());
            }
        }

		std::size_t get_data_size() const { return data_size_; }
        std::size_t get_field_count() const { return fields_.size(); }
		Field<Property>* GetField(std::size_t index)
        {
            if (index >= 0 && index < fields_.size()) {
                return &fields_[index];
            }
            return nullptr;
        }
        int GetFieldIndex(const char* field_name) const
        {
            auto& iter = name2index_.find(field_name);
            if (iter != name2index_.end()) {
                return iter->second;
            }
            return -1;
        }

    private:
        void InitProperty(const char* field_name, const char* type_name, int pub, int pri, int sv)
        {
            assert(name2index_.find(field_name) == name2index_.end());
            name2index_[field_name] = static_cast<int>(fields_.size());
            int data_size = 0;
            if (strcmp(type_name, "int32") == 0) {
                data_size = 4;
            } else if (strcmp(type_name, "char16") == 0) {
                data_size = 16;
            } else {
                data_size = 0;
            }
			Property prop;
			prop.Init(field_name, type_name, pub, pri, sv);
            fields_.emplace_back(Field<Property>(prop, data_size, data_size_));
            data_size_ += data_size;
        }
    };

    template <class PropertyT>
    class Row
    {
		//DISABLE_COPY(Row);
        // using ValueChangeCB = std::function<void()>;
    private:
        Column<PropertyT>& col_;
        char* data_buffer_{nullptr};
        dynamic_bitset bitset_;

    public:
        Row( Column<PropertyT>& col) : col_ (col), bitset_(col.get_field_count())
        {
            AllocBuffer(col.get_data_size());
        }
        ~Row() { delete[] data_buffer_; }

        // void RegValueChangeCB()
		std::string ToString()
		{
			std::string str;
			std::stringstream ss;
			for ( int i=0; i < col_.get_field_count(); ++i)
			{
				Field<PropertyT>* field = col_.GetField(i);
				if (!field)
				{
					continue;
				}
				PropertyT prop = field->get_property();
				const char* prop_name = prop.get_prop_name();
				ss << prop_name;
				ss << ":";
				const char* type_name = prop.get_prop_type();
				if (strcmp(type_name, "int32") == 0) {
					ss << field->GetValue<int>(data_buffer_);
				}
				else if (strcmp(type_name, "char16") == 0) {
					ss << field->GetValueString(data_buffer_);
				}
				else {
				}
				if (i < (col_.get_field_count() - 1))
				{
					ss << ",";
				}
			}
			ss >> str;
			return str;
		}

        template <typename T>
        bool GetValue(const char* field_name, T& val)
        {
            int nFieldIndex = col_.GetFieldIndex(field_name);
            return GetValue<T>(nFieldIndex, val);
        }
        template <typename T>
		bool GetValue(int index, T& val)
        {
            Field<PropertyT>* field = col_.GetField(index);
			if (!field)
			{
				return false;
			}
			val = field->GetValue<T>(data_buffer_);
			return true;
        }

		template <typename T>
		bool SetValue(const char* field_name, T val)
		{
			int nFieldIndex = col_.GetFieldIndex(field_name);
			return SetValue<T>(nFieldIndex, val);
		}
        template <typename T>
        bool SetValue(int index, T val)
        {
            Field<PropertyT>* field = col_.GetField(index);
			if (!field)
			{
				return false;
			}
			field->SetValue<T>(val, data_buffer_);
            bitset_.set(index);
			return true;
        }

        const char* GetValueString(const char* field_name)
        {
            int nFieldIndex = col_.GetFieldIndex(field_name);
            return GetValueString(nFieldIndex);
        }
        const char* GetValueString(int index)
        {
            Field<PropertyT>* field = col_.GetField(index);
            return field->GetValueString(data_buffer_);
        }

        bool SetValueString(const char* field_name, const char* pVal)
        {
            int nFieldIndex = col_.GetFieldIndex(field_name);
            return SetValueString(nFieldIndex, pVal);
        }
        bool SetValueString(int index, const char* pVal)
        {
            Field<PropertyT>* field = col_.GetField(index);
			if (!field)
			{
				return false;
			}
            field->SetValueString(pVal, data_buffer_);
            bitset_.set(index);
			return true;
        }

    private:
        void AllocBuffer(std::size_t buffer_size) { data_buffer_ = new char[buffer_size]{0}; }
    };

    template <class PropertyT, int COUNT>
    class MultiDataTable
    {
        DISABLE_COPY(MultiDataTable);

    private:
        const std::string& table_name_;
        Column<PropertyT>& col_;
		std::array<std::unique_ptr<Row<PropertyT>>, COUNT> rows_;
    public:
		MultiDataTable(const std::string& table_name, Column<PropertyT>& col)
            : table_name_(table_name), col_(col)
        {
        }

		Row<PropertyT>* GetRow(int index, bool create_if_not_exist) 
		{ 
			if (rows_[index] == nullptr)
			{
				rows_[index].reset(new Row<Property>(col_));
			}
			return rows_[index].get();
		}

		constexpr int get_row_count() { return COUNT; }
    };

	template <class PropertyT>
	class DataTable
	{
		DISABLE_COPY(DataTable);

	private:
		const std::string& table_name_;
		Column<PropertyT>& col_;
		Row<PropertyT> row_;
	public:
		DataTable(const std::string& table_name, Column<PropertyT>& col)
			: table_name_(table_name), col_(col), row_(col_)
		{
		}
		Row<PropertyT>& get_row() { return row_; }
	};

    template <class PropertyT>
    class MetaTable
    {
    private:
        std::string table_name_;
        Column<PropertyT> col_;
    public:
		MetaTable() = default;
		~MetaTable() = default;
        void InitTableName(const char* table_name) { table_name_ = table_name; }
        void InitColoumn(Document& d) { col_.InitProperty(d); }

        template <int COUNT>
		MultiDataTable<PropertyT, COUNT>* CreateMultiDataTable()
		{
			static_assert(COUNT > 1, "invalid data count");
            return new MultiDataTable<PropertyT, COUNT>(table_name_, col_);
        }

		DataTable<PropertyT>* CreateDataTable()
		{
			return new DataTable<PropertyT>(table_name_, col_);
		}
    };
}  // namespace terra