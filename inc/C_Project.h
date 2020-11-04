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

class C_Project : public C_DbHandle
{
public:
    C_Project(const std::string *db_file);
    ~C_Project();

    void create(void);
    void load(void);
    void loadTestData(void);
    void save(void);

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
    void Create_vTaskAssign(void);
    void Create_vTaskMatrix(void);

};


#endif // header guard
