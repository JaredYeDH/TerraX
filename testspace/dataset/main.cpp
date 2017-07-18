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
	int n = row.GetValue<int>("Level");

	auto* dt_item = ds.SpawnMultiDataTable<64>("item");
	auto* item_row = dt_item->GetRow(0, true);
	item_row->SetValue<int>("ItemID", 10001234);
	int item_id = item_row->GetValue<int>("ItemID");
	std::cin.get();

	return 0;
}