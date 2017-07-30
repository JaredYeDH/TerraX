#include <iostream>
//#include "dataset2.h"
#include "dataset.h"
using namespace rapidjson;
//using namespace terra;
/*
int main1()
{
	DataSet<Property> ds;
	ds.LoadTables(kDataSetRootDir);
	auto* dt = ds.SpawnDataTable("avatar");
	auto& row = dt->get_row();
	row.SetValue<int>("Level", 11);
	int lvl = 0;
	row.GetValue<int>("Level", lvl);

	std::cout << row.ToString() << std::endl;

	auto* dt_item = ds.SpawnMultiDataTable<64>("item");
	auto* item_row = dt_item->GetRow(0, true);
	item_row->SetValue<int>("ItemID", 10001234);
	int item_id = 0;
	item_row->GetValue<int>("ItemID", item_id);

	std::cout << item_row->ToString() << std::endl;

	std::cout << std::is_pod<Property>::value << std::endl;


	std::cin.get();
	std::cin.get();
	return 0;
}
*/

static const char* kDataSetRootDir = ".\\dataset";
using namespace dataset;

int main()
{
	DataSet ds;
	ds.LoadTables(kDataSetRootDir);
	Table* tbl = ds.FindTable("account");
	std::unique_ptr<RowData> row;
	row.reset(tbl->NewRowData());
	row->SetValueString("name", "test001");
	row->SetValueString("creation_time", "2017-01-01 08:00:00");
	row->SetValue<int64_t>("avatar_guid1", 10000001);

	std::cout << row->SerilizeToString() << std::endl;
	std::string str = row->SerilizeToByte();
	std::cout << str << std::endl;
	std::cout << row->SerilizeToString(prop_save, true) << std::endl;

	row.reset(tbl->NewRowData());
	row->ParseFromByte(str.c_str(), static_cast<uint32_t>(str.length()));
	std::string sss = row->SerilizeToString();
	std::cout << sss << std::endl;
	row.reset(tbl->NewRowData());
	row->ParseFromString(sss.c_str(), static_cast<int>(sss.length()));
	std::cout << row->SerilizeToString() << std::endl;
	std::cin.get();
	return 0;
}