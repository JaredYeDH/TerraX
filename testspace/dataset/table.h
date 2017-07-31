#pragma once


#include "rowdata.h"

namespace dataset
{
	class Table
	{
	private:
		std::string table_name_;
		Column col_;
	public:
		Table() = default;
		~Table() = default;
		void InitTableName(const char* table_name) { table_name_ = table_name; }
		void InitColoumn(Document& d) { col_.InitProperty(d); }
		//void SetValueChangeCB() { col_.SetValueChangeCB(); }
		RowData* NewRowData() { return new RowData(col_); }
	};
}