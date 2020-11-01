/***************************************************************
 * Name:      C_Project.cpp
 * Purpose:   Project DB functionalities
 * Author:    m7b
 * Created:   2020-10-30
 * Copyright: m7b
 * License:
 **************************************************************/

#include <C_Project.h>


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
    Create_tTasks();
    Create_tCommitmentPeriod();
}


void C_Project::load(const std::string *db_file)
{
}


void C_Project::loadTestData(void)
{
}


void C_Project::save(void)
{
}


void C_Project::Create_tEvent(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEvents (";
    query += "cId           INTEGER   PRIMARY KEY AUTOINCREMENT,";
    query += "cEvent        TEXT NOT NULL,";
    query += "cEventDetails TEXT,";
    query += "cRepeat       TEXT,";
    query += "cWeekdays     TEXT";
    query += ");";

    i = exec_db(&query);
    close_db();
}


void C_Project::Create_tEventReplacementPlan(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tEventReplacementPlan (";
    query += "cId          INTEGER   PRIMARY KEY AUTOINCREMENT,";
    query += "cEventId     INTEGER,";
    query += "cPlan        TEXT,";
    query += "cReplacement TEXT,";
    query += "cReason      TEXT,";
    query += "FOREIGN KEY(cEventId) REFERENCES tEvents(cId)";
    query += ");";

    i = exec_db(&query);
    close_db();
}


void C_Project::Create_tTasks(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABL E IF NOT EXISTS tTasks (";
    query += "cId          INTEGER   PRIMARY KEY AUTOINCREMENT,";
    query += "cTask        TEXT,";
    query += "cDescription TEXT,";
    query += "cPeriodId    INTEGER NOT NULL,";
    query += "FOREIGN KEY(cPeriodId) REFERENCES tCommitmentPeriod(cId)";
    query += ");";

    i = exec_db(&query);
    close_db();
}


void C_Project::Create_tCommitmentPeriod(void)
{
    int i = open_db();
    std::string query = "";

    query += "CREATE TABLE IF NOT EXISTS tCommitmentPeriod (";
    query += "cId          INTEGER   PRIMARY KEY AUTOINCREMENT,";
    query += "cPeriod      TEXT,";
    query += "cDescription TEXT";
    query += ");";

    i = exec_db(&query);
    close_db();
}
