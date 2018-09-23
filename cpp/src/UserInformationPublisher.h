#ifndef PUBLISHER_H
#define PUBLISHER_H
#endif
#include "DDSEntityManager.h"
#include "ccpp_tsn.h"
#include "os.h"
#include "Post.h"
#include "example_main.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>  
#include <boost/lexical_cast.hpp>

int user_informationPublisher(int argc, char *argv[]);