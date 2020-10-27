#ifndef DB_TABLES_H
#define DB_TABLES_H
/***************************************************************
 * Name:      db_tables.h
 * Purpose:   Defines database tables
 * Author:    m7b
 * Created:   2020-10-27
 * Copyright: m7b
 * License:
 **************************************************************/

#include <sqlite3.h>
#include <string>

int int_type = SQLITE_INTEGER;
int float_type = SQLITE_FLOAT;
int blob_type = SQLITE_BLOB;
int null_type = SQLITE_NULL;
int text_type = SQLITE_TEXT;


//forward declarations
struct t_col_type;

struct A {
    std::string name;
    t_col_type *col;
};

struct t_col_type
{
    int col_type;
    bool primary;
    std::string db_type_name;
};

struct A_col {
    t_col_type col;
    std::string caption;
    A_col *next;
};

A_col zwei = {{SQLITE_INTEGER, false, "t_name"}, "Bezeichnung", 0};
A_col eins = {{SQLITE_INTEGER,  true, "row_id"}, "Reihe",       &zwei};


enum cols{
    job = 0,
    job_bez,
    job_dur,
    per = 20,
    per_name,
    per_was
};

#endif // header guard
