/***************************************************************
 * Name:      main.h
 * Purpose:   main
 * Author:    m7b
 * Created:   2020-10-27
 * Copyright: m7b
 * License:
 **************************************************************/


#include "C_Project.h"

int main()
{
    std::string prj_file = "todo.db";

    C_Project test(&prj_file);

    test.create();
    test.loadTestData();

    std::string from_date = "2020-10-01";
    std::string   to_date = "2020-10-31";

    return 0;
}
