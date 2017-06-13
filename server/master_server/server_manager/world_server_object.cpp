#include "world_server_object.h"

using namespace  terra;

WorldServerObject::WorldServerObject(int server_uid, int region_showindex, const char* region_name,
	int server_showindex, const char* server_name, int status, bool recommond_new, bool recommond_hot) :
	server_uid_(server_uid),
	region_showindex_(region_showindex),
	region_name_(region_name),
	server_showindex_(server_showindex),
	server_name_(server_name),
	status_((ServerStatus)status),
	recommond_new_(recommond_new),
	recommond_hot_(recommond_hot)
{

}