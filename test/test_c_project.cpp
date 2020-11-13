#define BOOST_TEST_MODULE c_project
#include <boost/test/unit_test.hpp>

#include "C_Project.h"

BOOST_AUTO_TEST_CASE(PassTest)
{

    std::string prj_file = "test.db";
    C_Project test(&prj_file);

    test.create();
    test.insertTestData();

    BOOST_TEST_MESSAGE("Created test DB: " << prj_file);

    std::string result = test.get_event("2020-11-14");
}
