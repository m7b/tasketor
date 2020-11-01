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

    void create(const std::string *db_file);
    void load(const std::string *db_file);
    void loadTestData(void);
    void save(void);

private:

    void Create_tEvent(void);
    void Create_tEventReplacementPlan(void);
    void Create_tTasks(void);
    void Create_tCommitmentPeriod(void);
    void Create_tEventTasks(void);
    void Create_tTaskMatrix(void);
    void Create_tPerson(void);
    void Create_tTaskAssign(void);
    void Create_tPersonAbsent(void);

};


#endif // header guard
