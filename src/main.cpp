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

    test.create(&prj_file);
    test.loadTestData();

    return 0;
}
