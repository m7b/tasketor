/***************************************************************
 * Name:      main.h
 * Purpose:   main
 * Author:    m7b
 * Created:   2020-10-27
 * Copyright: m7b
 * License:
 **************************************************************/

#include "main.h"

#include <filesystem>
namespace fs = std::filesystem;

PersList PList;

int main()
{
	auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
	logger->info("Hello info!!");
	logger->error("Hello error!!");

    std::string prj_file = "todo.db";
    C_Project test(&prj_file);

    if (!fs::exists(prj_file))
    {
        test.create();
        test.insertTestData();
    }

    using namespace boost::locale;
    using namespace boost::gregorian;

    std::string from_date = "2022-10-01";
    std::string   to_date = "2022-10-31";

    date from(from_simple_string(from_date));
    date   to(from_simple_string(to_date));

    std::vector<std::string> v_events_at_date;
    std::vector<task_assign> v_tasks_at_date;

//    std::cout << std::endl;
//    std::cout << "Tätigkeiten vom " << to_iso_extended_string(from) << " ";
//    std::cout << "bis " << to_iso_extended_string(to)   << ":" << std::endl;
//    std::cout << "==========================================";
//    std::cout << std::endl << std::endl;
//
//    std::cout << "+------------+-----+---------" << std::endl;
//    std::cout << "| Datum      | Tag | Event(s)" << std::endl;
//    std::cout << "+------------+-----+---------" << std::endl;
//    for (date d = from; d <= to; d+=days(1))
//    {
//        v_events_at_date.clear();
//        v_tasks_at_date.clear();
//        std::cout << "| " << to_iso_extended_string(d) << " ";
//        std::cout << "| " << d.day_of_week().as_short_string() << " | ";
//        std::cout << test.get_event(d, &v_events_at_date) << " | ";
//        if (!v_events_at_date.empty())
//            std::cout << test.get_task(&v_events_at_date, &v_tasks_at_date) << std::endl;
//        else
//            std::cout << std::endl;
//    }
//    std::cout << "+------------+-----+---------" << std::endl;


    // ########################################################################
    // Create the plan (calendar)
    // ########################################################################
    std::vector<the_plan> vthe_plan;
    for (date d = from; d <= to; d+=days(1))
    {
        v_events_at_date.clear();
        std::string res = test.get_event(d, &v_events_at_date);
        if (res != "")
        {
            the_plan tmp;
            tmp.datum    = d;
            tmp.v_events = v_events_at_date;

            v_tasks_at_date.clear();
            test.get_task(&v_events_at_date, &v_tasks_at_date);
            tmp.v_tasks = v_tasks_at_date;
            vthe_plan.push_back(tmp);
        }
    }




    // ########################################################################
    // Draw the plan (calendar)
    // ########################################################################
    std::cout << test.create_header(&vthe_plan) << std::endl;
    std::cout << test.create_tarows(&vthe_plan) << std::endl;
    //for (const auto &row : vthe_plan)


    return 0;
}
