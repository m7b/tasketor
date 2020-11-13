#ifndef C_PROJECT_H
#define C_PROJECT_H
/***************************************************************
 * Name:      C_Project.h
 * Purpose:   Project DB functionalities
 * Author:    m7b
 * Created:   2020-10-30
 * Copyright: m7b
 * License:
 **************************************************************/

#include "C_DbHandle.h"
#include <vector>

class C_Project : public C_DbHandle
{
public:
    C_Project(const std::string *db_file);
    ~C_Project();

    void create(void);
    void load(void);
    void insertTestData(void);
    void save(void);

    //Pass a date and get the event at this date
    std::string get_event(std::string date);

private:

    void Create_tPeriode(void);
    void Create_tEvent(void);
    void Create_tEventReplacementPlan(void);
    void Create_tTask(void);
    void Create_tEventTasks(void);
    void Create_tTaskMatrix(void);
    void Create_tPerson(void);
    void Create_tTaskAssign(void);
    void Create_tPersonAbsent(void);

    void Create_vEvent(void);
    void Create_vEventReplacementPlan(void);
    void Create_vEventTasks(void);
    void Create_vPersonAbsent(void);
    void Create_vTask(void);
    void Create_vTaskAssign(void);
    void Create_vTaskMatrix(void);

};

struct tTask
{
    bool assignable;  //Kann der Aufgabe zugewiesen werden
    bool available;   //Ist anwesend
    bool assigned;    //Schon zugeteilt
};

struct PersPlan
{
    int assign_count;
    tTask Task[5];  //Alle Aufgaben
};


struct PersList
{
    std::string datum;
    PersPlan Person[10]; //Alle Personen
};



#endif // header guard
