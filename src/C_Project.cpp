/***************************************************************
 * Name:      C_Project.cpp
 * Purpose:   Project DB functionalities
 * Author:    m7b
 * Created:   2020-10-30
 * Copyright: m7b
 * License:
 **************************************************************/

#include <C_Project.h>
#include <iostream>


C_Project::C_Project(const std::string *db_file)
: C_DbHandle(db_file)
{
}


C_Project::~C_Project()
{
}


void C_Project::create(void)
{
    Create_tPeriode();
    Create_tEvent();
    Create_tEventReplacementPlan();
    Create_tTask();
    Create_tEventTasks();
    Create_tTaskMatrix();
    Create_tPerson();
    Create_tTaskAssign();
    Create_tPersonAbsent();

    Create_vEvent();
    Create_vEventReplacementPlan();
    Create_vEventTasks();
    Create_vPersonAbsent();
    Create_vTask();
    Create_vTaskAssign();
    Create_vTaskMatrix();
}


void C_Project::load(void)
{
}


void C_Project::insertTestData(void)
{
    rc = open_db();
    std::string query;

    query = "";
    query += "INSERT INTO tPeriode (cPeriode, cDescription) ";
    query += "VALUES ";
    query += "('einmalig',      ''),";
    query += "('jedes mal',     ''),";
    query += "('täglich',       ''),";
    query += "('wöchentlich',   ''),";
    query += "('2-wöchentlich', ''),";
    query += "('monatlich',     '');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tEvent (cEvent, cEventDetails, cFirstTime, cPeriodeId, cWeekdays) ";
    query += "VALUES ";
    query += "('Ev-A', '19:15 - 21:00', '2022-10-07', (SELECT cId FROM tPeriode WHERE cPeriode='wöchentlich'), 'Wed'),";
    query += "('Ev-B', '18:30 - 20:15', '2022-10-03', (SELECT cId FROM tPeriode WHERE cPeriode='wöchentlich'), 'Sat');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tEventReplacementPlan (cEventId, cPlan, cReplacement, cReason) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), '2022-10-21', '2022-10-20', 'Außerplanmäßiger Grund'),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), '2022-10-21', '2022-10-20', 'Außerplanmäßiger Grund');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tTask (cTask, cDescription, cPeriodeId) ";
    query += "VALUES ";
    query += "('Ta-A', 'Ordner 1',              (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-B', 'Ordner 2',              (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-C', 'Zoom-Ordner (Co-Host)', (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-D', 'Host PC',               (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-E', 'Mischpult',             (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-F', 'Mikrofon 1',            (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-G', 'Mikrofon 2',            (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-H', 'Vorsitz',               (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-I', 'WT-Leser',              (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal'));";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tEventTasks (cEventId, cTaskId) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-E')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-F')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-G')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-E')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-F')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-G')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-H')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-I'));";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tTaskMatrix (cTaskId, cTaskId_atst) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-B'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-B'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-C'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-D'), (SELECT cId FROM tTask WHERE cTask='Ta-B'));";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tPerson (cName) ";
    query += "VALUES ";
    query += "('Edgar'),";
    query += "('Eber'),";
    query += "('Braftaler'),";
    query += "('Burbs'),";
    query += "('Grumml'),";
    query += "('Eufers'),";
    query += "('Siffel');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tTaskAssign (cPersonId, cTaskId) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Eber'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Eber'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), (SELECT cId FROM tTask WHERE cTask='Ta-E')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Burbs'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Burbs'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Burbs'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Burbs'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Grumml'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Grumml'), (SELECT cId FROM tTask WHERE cTask='Ta-E')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Eufers'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Eufers'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Siffel'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tPerson WHERE cName='Siffel'), (SELECT cId FROM tTask WHERE cTask='Ta-D'));";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tPersonAbsent (cPersonId, cFrom, cTo) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'),     '2022-10-26', '2022-11-01'),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), '2022-10-31', '');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    close_db();
}


void C_Project::save(void)
{
}


//Pass a date and get the event at this date
std::string C_Project::get_event(date d, std::vector<std::string> *v_events)
{
    std::string result_list = "";
    date start_date;

    std::vector<res_events> events;

    get_all_events(&events);

    /////////
    //Iterate over result if event is at date

    for (const auto &el : events)
    {
        if (el.cPeriode == "täglich")
        {
            start_date = from_string(el.cFirstTime);
            if (d >= start_date)
            {
                result_list += el.cEvent + ", ";
                v_events->push_back(el.cEvent);
            }
        }

        if (el.cPeriode == "wöchentlich")
        {
            start_date = from_string(el.cFirstTime);
            if (d >= start_date)
            {
                // Wochentag
                std::string weekday = get_weekday(d);
                int pos = el.cWeekdays.find(weekday);
                if (pos != std::string::npos)
                {
                    result_list += el.cEvent + ", ";
                    v_events->push_back(el.cEvent);
                }
            }
        }
    }

    return result_list;
}


//Pass an event list and get the task(s) for the events
std::string C_Project::get_task(const std::vector<std::string> *v_events, std::vector<task_assign> *v_tasks)
{
    std::string result_list = "";

    std::vector<res_tasks> tasks;

    get_all_tasks(&tasks);

    for (const auto &el_ev: *v_events)
        for (const auto &el_ta : tasks)
            if (el_ta.cEvent == el_ev)
            {
                if (result_list.find(el_ta.cTask) == std::string::npos)
                {
                    result_list += el_ta.cTask + ", ";
                    task_assign tmp;
                    tmp.task.cTask = el_ta.cTask;
                    tmp.task.cPeriode = el_ta.cPeriode;
                    tmp.assignee = "none";
                    v_tasks->push_back(tmp);
                }
            }


    return result_list;
}


std::string C_Project::get_weekday(date d)
{
    return d.day_of_week().as_short_string();
}


void C_Project::Create_tPeriode(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tPeriode (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPeriode     TEXT UNIQUE,";
    query += "cDescription TEXT";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tPeriode: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tEvent(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEvent (";
    query += "cId           INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEvent        TEXT NOT NULL UNIQUE,";
    query += "cEventDetails TEXT,";
    query += "cFirstTime    DATE,";
    query += "cPeriodeId    INTEGER NOT NULL,";
    query += "cWeekdays     TEXT,";
    query += "FOREIGN KEY(cPeriodeId) REFERENCES tPeriode(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tEvent: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tEventReplacementPlan(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEventReplacementPlan (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEventId     INTEGER,";
    query += "cPlan        DATE NOT NULL,";
    query += "cReplacement DATE,";
    query += "cReason      TEXT,";
    query += "FOREIGN KEY(cEventId) REFERENCES tEvent(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tEventReplacementPlan: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tTask(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTask (";
    query += "cId           INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cTask         TEXT UNIQUE,";
    query += "cDescription  TEXT,";
    query += "cPeriodeId    INTEGER NOT NULL,";
    query += "FOREIGN KEY(cPeriodeId) REFERENCES tPeriode(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tTasks: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tEventTasks(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEventTasks (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEventId     INTEGER NOT NULL,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "FOREIGN KEY(cEventId) REFERENCES tEvent(cId),";
    query += "FOREIGN KEY(cTaskId)  REFERENCES tTask(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tEventTasks: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tTaskMatrix(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTaskMatrix (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "cTaskId_atst INTEGER,";
    query += "FOREIGN KEY(cTaskId)      REFERENCES tTask(cId),";
    query += "FOREIGN KEY(cTaskId_atst) REFERENCES tTask(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tTaskMatrix: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tPerson(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tPerson (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cName        TEXT NOT NULL";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tPerson: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tTaskAssign(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTaskAssign (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPersonId    INTEGER NOT NULL,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "FOREIGN KEY(cPersonId) REFERENCES tPerson(cId),";
    query += "FOREIGN KEY(cTaskId)   REFERENCES tTask(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tTaskAssign: " << rc << std::endl;
    close_db();
}


void C_Project::Create_tPersonAbsent(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tPersonAbsent (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPersonId    INTEGER NOT NULL,";
    query += "cFrom        DATE    NOT NULL,";
    query += "cTo          DATE,";
    query += "FOREIGN KEY(cPersonId) REFERENCES tPerson(cId)";
    query += ");";

    rc = exec_db(&query);
    std::cout << "tPersonAbsent: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vEvent(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vEvent AS ";
    query += "    SELECT cEvent, ";
    query += "           cEventDetails, ";
    query += "           cFirstTime, ";
    query += "           tPeriode.cPeriode, ";
    query += "           cWeekdays ";
    query += "      FROM tEvent ";
    query += "           INNER JOIN ";
    query += "           tPeriode ON tPeriode.cId = tEvent.cPeriodeId; ";

    rc = exec_db(&query);
    std::cout << "vEvent: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vEventReplacementPlan(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vEventReplacementPlan AS ";
    query += "    SELECT tEvent.cEvent, ";
    query += "           cPlan, ";
    query += "           cReplacement, ";
    query += "           cReason ";
    query += "      FROM tEventReplacementPlan ";
    query += "           INNER JOIN ";
    query += "           tEvent ON tEvent.cId = tEventReplacementPlan.cEventId; ";

    rc = exec_db(&query);
    std::cout << "vEventReplacementPlan: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vEventTasks(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vEventTasks AS ";
    query += "    SELECT cEventId, ";
    query += "           cEvent, ";
    query += "           cTaskId, ";
    query += "           cTask, ";
    query += "           cDescription ";
    query += "           cPeriode ";
    query += "      FROM tEventTasks ";
    query += "           INNER JOIN ";
    query += "           tEvent ON tEvent.cId = tEventTasks.cEventId ";
    query += "           INNER JOIN ";
    query += "           tTask ON tTask.cId = tEventTasks.cTaskId ";
    query += "           INNER JOIN ";
    query += "           tPeriode ON tPeriode.cId = tTask.cPeriodeId; ";

    rc = exec_db(&query);
    std::cout << "vEventTasks: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vPersonAbsent(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vPersonAbsent AS ";
    query += "    SELECT cName, ";
    query += "           cFrom, ";
    query += "           cTo ";
    query += "      FROM tPersonAbsent ";
    query += "           INNER JOIN ";
    query += "           tPerson ON tPerson.cId = tPersonAbsent.cPersonId; ";

    rc = exec_db(&query);
    std::cout << "vPersonAbsent: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vTask(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vTask AS ";
    query += "    SELECT cTask, ";
    query += "           cDescription, ";
    query += "           cPeriode ";
    query += "      FROM tTask ";
    query += "           INNER JOIN ";
    query += "           tPeriode ON tPeriode.cId = tTask.cPeriodeId; ";

    rc = exec_db(&query);
    std::cout << "vTask: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vTaskAssign(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vTaskAssign AS ";
    query += "    SELECT cPersonId, ";
    query += "           tPerson.cName, ";
    query += "           cTaskId, ";
    query += "           tTask.cTask ";
    query += "      FROM tTaskAssign ";
    query += "           INNER JOIN ";
    query += "           tPerson ON tPerson.cId = tTaskAssign.cPersonId ";
    query += "           INNER JOIN ";
    query += "           tTask ON tTask.cId = tTaskAssign.cTaskId; ";

    rc = exec_db(&query);
    std::cout << "vTaskAssign: " << rc << std::endl;
    close_db();
}


void C_Project::Create_vTaskMatrix(void)
{
    rc = open_db();
    std::string query = "";

    query += "CREATE VIEW IF NOT EXISTS vTaskMatrix AS ";
    query += "    SELECT cTaskId, ";
    query += "           T.cTask AS Task, ";
    query += "           cTaskId_atst, ";
    query += "           S.cTask AS Task_atst ";
    query += "      FROM tTaskMatrix ";
    query += "           INNER JOIN ";
    query += "           tTask AS T ON T.cId = tTaskMatrix.cTaskId ";
    query += "           INNER JOIN ";
    query += "           tTask AS S ON S.cId = tTaskMatrix.cTaskId_atst; ";

    rc = exec_db(&query);
    std::cout << "vTaskMatrix: " << rc << std::endl;
    close_db();
}



void C_Project::get_all_events(std::vector<res_events> *v_res)
{
    rc = open_db();

    std::string query = "";
    query += "SELECT * FROM vEvent";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            res_events res;
            res.cEvent       = get_text(COL_0);
            res.cEventDetail = get_text(COL_1);
            res.cFirstTime   = get_text(COL_2);
            res.cPeriode     = get_text(COL_3);
            res.cWeekdays    = get_text(COL_4);
            v_res->push_back(res);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

void C_Project::get_all_tasks(std::vector<res_tasks> *v_res)
{
    rc = open_db();

    std::string query = "";
    query += "SELECT cEvent, cTask, tTask.cDescription, cPeriode ";
    query += "FROM tEventTasks ";
    query += "INNER JOIN tEvent ON tEvent.cId = tEventTasks.cEventId ";
    query += "INNER JOIN tTask ON tTask.cId = tEventTasks.cTaskId ";
    query += "INNER JOIN tPeriode ON tPeriode.cId = tTask.cPeriodeId ";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            res_tasks res;
            res.cEvent   = get_text(COL_0);
            res.cTask    = get_text(COL_1);
            res.cPeriode = get_text(COL_3);
            v_res->push_back(res);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();
}

std::string C_Project::create_header(const std::vector<the_plan> *plan)
{
    bool first = false;
    std::string header = "";

    header += "Datum;Tag;";

    for (const auto &h_row : *plan)
        for (const auto &h_task : h_row.v_tasks)
            if (header.find(h_task.task.cTask) == std::string::npos)
            {
                if (!first)
                {
                    first = true;
                    header += h_task.task.cTask;
                }
                else
                    header += ";" + h_task.task.cTask;
            }

    return header;
}

std::string C_Project::create_tarows(const std::vector<the_plan> *plan)
{
    std::string rows = "";

    for (const auto &h_row : *plan)
    {
        rows += to_iso_extended_string(h_row.datum);                             // Datum
        rows += ";" + std::string(h_row.datum.day_of_week().as_short_string());  // Wochentag

        for (const auto &h_task : h_row.v_tasks)
            rows += ";" + h_task.assignee;

        rows += "\n";
    }

    return rows;
}


void C_Project::get_all_persons(std::vector<person> *v_pers)
{
    rc = open_db();

    std::vector<person> v_tmp_pers;

    std::string query = "";
    query += "SELECT tPerson.cName, tTask.cTask, tTask.cDescription ";
    query += "FROM tTaskAssign ";
    query += "INNER JOIN tPerson ON tPerson.cId = tTaskAssign.cPersonId ";
    query += "INNER JOIN tTask ON tTask.cId = tTaskAssign.cTaskId";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            person pers;
            pers.name             = get_text(COL_0);
            pers.assignable_tasks = get_text(COL_1);

            v_tmp_pers.push_back(pers);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();


    std::string tmp_name = "";
    std::string tmp_assignable_tasks = "";
    person tmp_pers;
    for (const auto &el : v_tmp_pers)
    {
        if (tmp_name != el.name)
        {
            if (tmp_name == "")
            {
                tmp_name             = el.name;
                tmp_assignable_tasks = el.assignable_tasks;
            }
            else
            {
                tmp_pers.name = tmp_name;
                tmp_pers.assignable_tasks = tmp_assignable_tasks;
                v_pers->push_back(tmp_pers);

                tmp_name             = el.name;
                tmp_assignable_tasks = el.assignable_tasks;
            }
        }
        else
        {
            tmp_assignable_tasks += ", " + el.assignable_tasks;
        }
    }

    if (tmp_name != "")
    {
        tmp_pers.name = tmp_name;
        tmp_pers.assignable_tasks = tmp_assignable_tasks;
        v_pers->push_back(tmp_pers);
    }

}




std::string C_Project::get_free_person_for(res_tasks task, date datum, std::vector<person> *v_pers)
{
    std::string ret_val = "";

    std::vector<person*> possibles;

    // Check if assingee's duration has reached and release them for new assignments
    for (auto &el_per : *v_pers)
    {
        if (el_per.assigned_a != "")
        {
            if (el_per.since_a + days(el_per.duration_a) <= datum){
                //release them for new assignments
                el_per.v_last_assignment.push_front(el_per.assigned_a);
                el_per.assigned_a = "";
                el_per.since_a = date(1400, 1, 1);
            }
        }
    }

    //Return already and not expired assignee
    for (auto &el_per : *v_pers)
        if (el_per.assigned_a == task.cTask)
        {
            ret_val = el_per.name;
            break;
        }

    //Search for new assignee
    if (ret_val == "")
    {
        //Search for possibilities
        for (auto &el_per : *v_pers)
            if ((el_per.assigned_a == "") &&
                (el_per.assignable_tasks.find(task.cTask) != std::string::npos) &&
                (el_per.v_last_assignment[0] != task.cTask) &&
                (el_per.v_last_assignment[1] != task.cTask))
            {
                possibles.push_back(&el_per);
            }

        if (!possibles.empty())
        {
            person *assigner = *select_randomly(possibles.begin(), possibles.end());

            ret_val              = assigner->name;
            assigner->assigned_a = task.cTask;
            assigner->since_a    = datum;
            assigner->duration_a = get_days_from_duration(task.cPeriode);
        }
        else
            ret_val = "hmpf!";
    }

    return ret_val;
}


void C_Project::do_assignments(std::vector<the_plan> *plan)
{
    std::vector<person> v_pers;
    get_all_persons(&v_pers);

    for (const auto &el : v_pers)
    {
        std::cout << el.name << ": " << el.assignable_tasks << std::endl;
    }

    for (auto &row : *plan)
        for (auto &task : row.v_tasks)
        {
            task.assignee = get_free_person_for(task.task, row.datum, &v_pers);
        }
}

int C_Project::get_days_from_duration(std::string duration)
{
    int ret_val = 1;

    if (duration == "täglich")
        ret_val = 1;

    if (duration == "jedes mal")
        ret_val = 1;

    if (duration == "wöchentlich")
        ret_val = 7;

    if (duration == "2-wöchentlich")
        ret_val = 14;

    if (duration == "monatlich")
        ret_val = 30;

    return ret_val;
}
