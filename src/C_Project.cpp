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
    query += "('Ev-A', '9:30 - 9:45',   '2020-10-01', (SELECT cId FROM tPeriode WHERE cPeriode='täglich'),     'Mo, Di, Mi, Do, Fr, Sa'),";
    query += "('Ev-B', '19:15 - 21:00', '2020-10-07', (SELECT cId FROM tPeriode WHERE cPeriode='wöchentlich'), 'Mi'),";
    query += "('Ev-C', '18:30 - 20:15', '2020-10-03', (SELECT cId FROM tPeriode WHERE cPeriode='wöchentlich'), 'Sa');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tEventReplacementPlan (cEventId, cPlan, cReplacement, cReason) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), '2020-10-21', '2020-10-20', 'Außerplanmäßiger Grund'),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), '2020-10-21', '2020-10-20', 'Außerplanmäßiger Grund');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tTask (cTask, cDescription, cPeriodeId) ";
    query += "VALUES ";
    query += "('Ta-A', 'Host',    (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-B', 'Co-Host', (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-C', 'Vorsitz', (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-D', 'Leser',   (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal')),";
    query += "('Ta-E', 'Host TP', (SELECT cId FROM tPeriode WHERE cPeriode='jedes mal'));";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    query = "";
    query += "INSERT INTO tEventTasks (cEventId, cTaskId) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-A'), (SELECT cId FROM tTask WHERE cTask='Ta-E')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), (SELECT cId FROM tTask WHERE cTask='Ta-A')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), (SELECT cId FROM tTask WHERE cTask='Ta-D'));";

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
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'),     '2020-10-26', '2020-11-01'),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), '2020-10-31', '');";

    rc = exec_db(&query);
    std::cout << "Query: " << rc << std::endl;

    close_db();
}


void C_Project::save(void)
{
}


std::string C_Project::get_event(std::string date)
{
    rc = open_db();

    struct t_res_events
    {
        std::string cEvent;
        std::string cEventDetail;
        std::string cFirstTime;
        std::string cPeriode;
        std::string cWeekdays;
    };

    std::vector<t_res_events> v_res;
    t_res_events res;

    std::string query = "";
    query += "SELECT * FROM vEvent";

    rc = query_db(&query);

    while (true)
    {
        rc = step_db();
        if(rc == SQLITE_ROW)
        {
            res.cEvent       = get_text(COL_0);
            res.cEventDetail = get_text(COL_1);
            res.cFirstTime   = get_text(COL_2);
            res.cPeriode     = get_text(COL_3);
            res.cWeekdays    = get_text(COL_4);
            v_res.push_back(res);
        }

        if(done_or_error(rc))
            break;
    }

    rc = close_db();

    /////////
    //Iterate over result iv event is at date

    for (const auto &el : v_res)
    {
        if (el.cPeriode == "täglich")
            ;
        if (el.cPeriode == "wöchentlich")
            ;
    }
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
    query += "           cTask ";
    query += "      FROM tEventTasks ";
    query += "           INNER JOIN ";
    query += "           tEvent ON tEvent.cId = tEventTasks.cEventId ";
    query += "           INNER JOIN ";
    query += "           tTask ON tTask.cId = tEventTasks.cTaskId; ";

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
