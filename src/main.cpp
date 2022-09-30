/***************************************************************
 * Name:      main.h
 * Purpose:   main
 * Author:    m7b
 * Created:   2020-10-27
 * Copyright: m7b
 * License:
 **************************************************************/

#include "main.h"

PersList PList;

int main()
{
	auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
	logger->info("Hello info!!");
	logger->error("Hello error!!");

    std::string prj_file = "todo.db";
    C_Project test(&prj_file);

    test.create();
    test.insertTestData();

    using namespace boost::locale;
    using namespace boost::gregorian;

    std::string from_date = "2022-10-01";
    std::string   to_date = "2022-10-31";

    date from(from_simple_string(from_date));
    date   to(from_simple_string(to_date));

    std::cout << std::endl;
    std::cout << "Tätigkeiten vom " << to_iso_extended_string(from) << " ";
    std::cout << "bis " << to_iso_extended_string(to)   << ":" << std::endl;
    std::cout << "==========================================";
    std::cout << std::endl << std::endl;

    std::cout << "| Datum      | Tag | Event(s)" << std::endl;
    std::cout << "|------------|-----|---------" << std::endl;
    for (date d = from; d <= to; d+=days(1))
    {
        std::cout << "| " << to_iso_extended_string(d) << " ";
        std::cout << "| " << d.day_of_week().as_short_string() << " | ";
        std::cout << test.get_event(to_iso_extended_string(d))  << std::endl;
    }

    return 0;
}
