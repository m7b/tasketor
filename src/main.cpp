/***************************************************************
 * Name:      main.h
 * Purpose:   main
 * Author:    m7b
 * Created:   2020-10-27
 * Copyright: m7b
 * License:
 **************************************************************/


#include "C_Project.h"
#include <boost/locale.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

int main()
{
    std::string prj_file = "todo.db";
    C_Project test(&prj_file);

//    test.create();
//    test.loadTestData();

    using namespace boost::locale;
    using namespace boost::gregorian;

    generator gen;
    std::locale::global(gen(""));
    std::cout.imbue(std::locale());

    std::string from_date = "2020-10-01";
    std::string   to_date = "2020-10-31";

    date from(from_simple_string(from_date));
    date   to(from_simple_string(to_date));

    std::cout << "Tätigkeiten vom " << to_iso_extended_string(from) << " ";
    std::cout << "bis " << to_iso_extended_string(to)   << ":" << std::endl;
    std::cout << "==========================================";
    std::cout << std::endl << std::endl;

    std::cout << "|Datum     | ... |" << std::endl;
    std::cout << "|----------|-----|" << std::endl;
    for (date d = from; d <= to; d+=days(1))
    {
        std::cout << "|" << to_iso_extended_string(d) << "|     |" << std::endl;
    }

    return 0;
}
