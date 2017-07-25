#pragma once
/*
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include "metatable.h"
#include "file_reader.h"
#include "macro.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;
namespace terra
{
	static const char* kDataSetRootDir = ".\\data_pool_config";
	static const char* kJsonTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	
	template<class PropertyT>
	class DataSet
	{
	private:
		std::map<std::string, std::unique_ptr<MetaTable<PropertyT>>> tables_;

	public:
		DataSet() = default;
		~DataSet() = default;

		void LoadTables(const std::string& foler_path)
		{
			FileReader fr(foler_path);
			auto& files = fr.GetFileNames();
			for (const auto& val : files) {
				LoadFile(val);
			}
		}
		DataTable<PropertyT>* SpawnDataTable(const char* table_name) {
			auto& iter = tables_.find(table_name);
			if(iter != tables_.end())
			{
				return (iter->second)->CreateDataTable();
			}
			return nullptr;
		}
		template <int COUNT>
		MultiDataTable<PropertyT, COUNT>* SpawnMultiDataTable(const char* table_name)
		{
			auto& iter = tables_.find(table_name);
			if (iter != tables_.end())
			{
				return (iter->second)->CreateMultiDataTable<COUNT>();
			}
			return nullptr;
		}

	private:
		void LoadFile(const FileInfo_t& fi)
		{
			FILE* fp = fopen(fi.file_path, "rb"); // "rb", 非 Windows 平台使用 "r"
			assert(fp);
			int descriptor = fileno(fp);
			struct stat statBuf;
			if (fstat(descriptor, &statBuf) == -1) {
				fclose(fp);
				return;
			}
			std::size_t file_length = statBuf.st_size;
			char* buffer = new char[file_length + 1](); //+'\0'
			std::size_t readsize = fread(buffer, 1, file_length, fp);
			assert(readsize == file_length);
			fclose(fp);
			Document doc;
			doc.Parse(buffer);
			delete[] buffer;
			tables_[fi.file_name] = std::move(std::make_unique<MetaTable<PropertyT>>());
			tables_[fi.file_name]->InitTableName(fi.file_name);
			ParseFromDoc(doc, *tables_[fi.file_name]);
		}
		void ParseFromDoc(Document& d, MetaTable<PropertyT>& dt)
		{
			dt.InitColoumn(d);
		}
	};
}
*/