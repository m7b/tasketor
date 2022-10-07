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

#include "utils.h"


#include <boost/locale.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::locale;
using namespace boost::gregorian;


typedef struct _task_assign
{
    std::string task;
    std::string assignee;
    int duration;
} task_assign;

typedef struct _res_events
{
    std::string cEvent;
    std::string cEventDetail;
    std::string cFirstTime;
    std::string cPeriode;
    std::string cWeekdays;
} res_events;

typedef struct _res_tasks
{
    std::string cEvent;
    std::string cTask;
    std::string cPeriode;
} res_tasks;

typedef struct _the_plan
{
    date datum;
    std::vector<std::string> v_events;
    std::vector<task_assign> v_tasks;
} the_plan;

typedef struct _person
{
    std::string name;
    std::string assignable_tasks;
    std::string assigned_a;
    date since_a;
    int duration_a;
    std::string assigned_b;
    date since_b;
    int duration_b;
    std::deque<std::string> v_last_assignment;
} person;


class C_Project : public C_DbHandle
{
public:
    C_Project(const std::string *db_file);
    ~C_Project();

    void create(void);
    void load(void);
    void insertTestData(void);
    void save(void);

    //Pass a date and get the event(s) at this date
    std::string get_event(date d, std::vector<std::string> *v_events);

    //Pass a date and get the weekday at this date
    std::string get_weekday(date d);

    //Pass an event list and get the task(s) for the events
    std::string get_task(const std::vector<std::string> *v_events, std::vector<task_assign> *v_tasks);

    std::string create_header(const std::vector<the_plan> *plan);
    std::string create_tarows(const std::vector<the_plan> *plan);
    void do_assignments(std::vector<the_plan> *plan);

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

    void get_all_events(std::vector<res_events> *v_res);
    void get_all_tasks(std::vector<res_tasks> *v_res);
    void get_all_persons(std::vector<person> *v_pers);

    std::string get_free_person_for(std::string task, date datum, std::vector<person> *v_pers);
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
