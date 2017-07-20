#include <iostream>
#include <fstream>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "dataset.h"
#include <memory>
#include "file_reader.h"
#include "metatable.h"
#include <array>
#include "dynamic_bitset.h"
using namespace rapidjson;
using namespace terra;


int main()
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


	std::cin.get();
	std::cin.get();
	return 0;
}