#include "dataset.h"

using namespace dataset;




void DataSet::LoadTables(const std::string& foler_path)
{
	FileReader fr(foler_path);
	auto& files = fr.GetFileNames();
	for (const auto& val : files) {
		LoadFile(val);
	}
}

Table* DataSet::FindTable(const char* table_name)
{
	auto& iter = tables_.find(table_name);
	if (iter != tables_.end())
	{
		return (iter->second).get();
	}
	return nullptr;
}

void DataSet::LoadFile(const FileInfo_t& fi)
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
	tables_[fi.file_name] = std::move(std::make_unique<Table>());
	tables_[fi.file_name]->InitTableName(fi.file_name);
	ParseFromDoc(doc, *tables_[fi.file_name]);
}

void DataSet::ParseFromDoc(Document& d, Table& dt)
{
	dt.InitColoumn(d);
}