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


void C_Project::create(const std::string *db_file)
{
    Create_tEvent();
    Create_tEventReplacementPlan();
    Create_tCommitmentPeriod();
    Create_tTasks();
    Create_tEventTasks();
    Create_tTaskMatrix();
    Create_tPerson();
    Create_tTaskAssign();
    Create_tPersonAbsent();
}


void C_Project::load(const std::string *db_file)
{
}


void C_Project::loadTestData(void)
{
//    INSERT INTO bar (description, foo_id) VALUES
//    ( 'testing',     (SELECT id from foo WHERE type='blue') ),
//    ( 'another row', (SELECT id from foo WHERE type='red' ) );


    int i = open_db();

    std::string query;
    query = "";
    query += "INSERT INTO tEvent (cEvent, cEventDetails, cRepeat, cWeekdays) ";
    query += "VALUES ";
    query += "('Ev-A', '9:30 - 9:45', 'Täglich', 'Mo, Di, Mi, Do, Fr, Sa'),";
    query += "('Ev-B', '19:15 - 21:00', 'Wöchentlich', 'Mi'),";
    query += "('Ev-C', '18:30 - 20:15', 'Wöchentlich', 'Sa');";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tEventReplacementPlan (cEventId, cPlan, cReplacement, cReason) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), '21.10.2020', '20.10.2020', 'Außerplanmäßiger Grund'),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), '21.10.2020', '20.10.2020', 'Außerplanmäßiger Grund');";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    close_db();
}


void C_Project::save(void)
{
}


void C_Project::Create_tEvent(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEvent (";
    query += "cId           INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEvent        TEXT NOT NULL UNIQUE,";
    query += "cEventDetails TEXT,";
    query += "cRepeat       TEXT,";
    query += "cWeekdays     TEXT";
    query += ");";

    i = exec_db(&query);
    std::cout << "tEvent: " << i << std::endl;
    close_db();
}


void C_Project::Create_tEventReplacementPlan(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEventReplacementPlan (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEventId     INTEGER,";
    query += "cPlan        TEXT,";
    query += "cReplacement TEXT,";
    query += "cReason      TEXT,";
    query += "FOREIGN KEY(cEventId) REFERENCES tEvent(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tEventReplacementPlan: " << i << std::endl;
    close_db();
}


void C_Project::Create_tTasks(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTasks (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cTask        TEXT UNIQUE,";
    query += "cDescription TEXT,";
    query += "cPeriodId    INTEGER NOT NULL,";
    query += "FOREIGN KEY(cPeriodId) REFERENCES tCommitmentPeriod(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tTasks: " << i << std::endl;
    close_db();
}


void C_Project::Create_tCommitmentPeriod(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tCommitmentPeriod (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPeriod      TEXT UNIQUE,";
    query += "cDescription TEXT";
    query += ");";

    i = exec_db(&query);
    std::cout << "tCommitmentPeriod: " << i << std::endl;
    close_db();
}


void C_Project::Create_tEventTasks(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEventTasks (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cEventId     INTEGER NOT NULL,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "FOREIGN KEY(cEventId) REFERENCES tEvents(cId),";
    query += "FOREIGN KEY(cTaskId)  REFERENCES tTasks(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tEventTasks: " << i << std::endl;
    close_db();
}


void C_Project::Create_tTaskMatrix(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTaskMatrix (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "cTaskId_atst INTEGER,";
    query += "FOREIGN KEY(cTaskId)      REFERENCES tTasks(cId),";
    query += "FOREIGN KEY(cTaskId_atst) REFERENCES tTasks(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tTaskMatrix: " << i << std::endl;
    close_db();
}


void C_Project::Create_tPerson(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tPerson (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cName        TEXT NOT NULL";
    query += ");";

    i = exec_db(&query);
    std::cout << "tPerson: " << i << std::endl;
    close_db();
}


void C_Project::Create_tTaskAssign(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTaskAssign (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPersonId    INTEGER NOT NULL,";
    query += "cTaskId      INTEGER NOT NULL,";
    query += "FOREIGN KEY(cPersonId) REFERENCES tPerson(cId),";
    query += "FOREIGN KEY(cTaskId)   REFERENCES tTasks(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tTaskAssign: " << i << std::endl;
    close_db();
}


void C_Project::Create_tPersonAbsent(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tPersonAbsent (";
    query += "cId          INTEGER PRIMARY KEY AUTOINCREMENT,";
    query += "cPersonId    INTEGER NOT NULL,";
    query += "cFrom        TEXT    NOT NULL,";
    query += "cTo          TEXT,";
    query += "FOREIGN KEY(cPersonId) REFERENCES tPerson(cId)";
    query += ");";

    i = exec_db(&query);
    std::cout << "tPersonAbsent: " << i << std::endl;
    close_db();
}
