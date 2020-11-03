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
    Create_tEvent();
    Create_tEventReplacementPlan();
    Create_tCommitmentPeriod();
    Create_tTask();
    Create_tEventTasks();
    Create_tTaskMatrix();
    Create_tPerson();
    Create_tTaskAssign();
    Create_tPersonAbsent();
}


void C_Project::load(void)
{
}


void C_Project::loadTestData(void)
{
    int i = open_db();

    std::string query;
    query = "";
    query += "INSERT INTO tEvent (cEvent, cEventDetails, cFirstTime, cRepeat, cWeekdays) ";
    query += "VALUES ";
    query += "('Ev-A', '9:30 - 9:45',   '2020-10-01', 'Täglich',     'Mo, Di, Mi, Do, Fr, Sa'),";
    query += "('Ev-B', '19:15 - 21:00', '2020-10-07', 'Wöchentlich', 'Mi'),";
    query += "('Ev-C', '18:30 - 20:15', '2020-10-03', 'Wöchentlich', 'Sa');";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tEventReplacementPlan (cEventId, cPlan, cReplacement, cReason) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-B'), '21.10.2020', '20.10.2020', 'Außerplanmäßiger Grund'),";
    query += "((SELECT cId FROM tEvent WHERE cEvent='Ev-C'), '21.10.2020', '20.10.2020', 'Außerplanmäßiger Grund');";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tCommitmentPeriod (cPeriod, cDescription) ";
    query += "VALUES ";
    query += "('jedes mal',     ''),";
    query += "('täglich',       ''),";
    query += "('wöchentlich',   ''),";
    query += "('2-wöchentlich', ''),";
    query += "('monatlich',     '');";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tTask (cTask, cDescription, cPeriodId) ";
    query += "VALUES ";
    query += "('Ta-A', 'Host',    (SELECT cId FROM tCommitmentPeriod WHERE cPeriod='jedes mal')),";
    query += "('Ta-B', 'Co-Host', (SELECT cId FROM tCommitmentPeriod WHERE cPeriod='jedes mal')),";
    query += "('Ta-C', 'Vorsitz', (SELECT cId FROM tCommitmentPeriod WHERE cPeriod='jedes mal')),";
    query += "('Ta-D', 'Leser',   (SELECT cId FROM tCommitmentPeriod WHERE cPeriod='jedes mal')),";
    query += "('Ta-E', 'Host TP', (SELECT cId FROM tCommitmentPeriod WHERE cPeriod='jedes mal'));";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

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

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tTaskMatrix (cTaskId, cTaskId_atst) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-B'), (SELECT cId FROM tTask WHERE cTask='Ta-C')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-B'), (SELECT cId FROM tTask WHERE cTask='Ta-D')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-C'), (SELECT cId FROM tTask WHERE cTask='Ta-B')),";
    query += "((SELECT cId FROM tTask WHERE cTask='Ta-D'), (SELECT cId FROM tTask WHERE cTask='Ta-B'));";

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

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

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

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

    i = exec_db(&query);
    std::cout << "Query: " << i << std::endl;

    query = "";
    query += "INSERT INTO tPersonAbsent (cPersonId, cFrom, cTo) ";
    query += "VALUES ";
    query += "((SELECT cId FROM tPerson WHERE cName='Edgar'),     '2020-10-26', '2020-11-01'),";
    query += "((SELECT cId FROM tPerson WHERE cName='Braftaler'), '2020-10-31', '');";

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
    query += "cFirstTime    TEXT,";
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


void C_Project::Create_tTask(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tTask (";
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
    query += "FOREIGN KEY(cEventId) REFERENCES tEvent(cId),";
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
