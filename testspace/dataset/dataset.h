#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include "file_reader.h"
#include "macro.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"
#include "table.h"

using namespace rapidjson;
namespace dataset
{
	static const char* kJsonTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

	class DataSet
	{
	private:
		std::map<std::string, std::unique_ptr<Table>> tables_;

	public:
		DataSet() = default;
		~DataSet() = default;

		void LoadTables(const std::string& foler_path);
		Table* FindTable(const char* table_name);

	private:
		void LoadFile(const FileInfo_t& fi);
		void ParseFromDoc(Document& d, Table& dt);
	};
}