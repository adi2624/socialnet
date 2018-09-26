#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "example_main.h"
#include "User.h"

class Response 
{
private:
	char this_uuid_owner[17];
	bool is_done; // this is a flag to represent if all fulfiller uuids are imported to object
	std::vector<int> post_id_vec;

public:
	void set_this_uuid(char uuid[]) {  strncpy(this_uuid_owner,uuid + 5, 22);  }
	std::string get_this_uuid() 
	{ 
		std::string temp(this_uuid_owner);
		return temp; 
	}
	void set_is_done(bool done) { is_done = done; }
	bool get_is_done();
	void add_uuid_to_vec(int element_to_add) { post_id_vec.push_back(element_to_add); }
	int responsePublisher(int argc, char* argv[]);
	int responseSubsriber(int argc, char* argv[]);
};