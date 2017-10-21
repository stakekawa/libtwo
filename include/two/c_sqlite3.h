/*!
 *  \file c_sqlite3.h
 *
 *  \brief This file contains the declaration of the C_Sqlite3 class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_SQLITE3_H
#define TWO_C_SQLITE3_H


#include <list>
#include <string>
#include <vector>
#include "common.h"


namespace two {


class C_Sqlite3
{


public:

    /*!
     *  \brief Constructor
     */
    C_Sqlite3();

    /*!
     *  \brief Destructor
     */
    ~C_Sqlite3();

    /*!
     *  \brief Deleted copy constructor
     */
    C_Sqlite3(const C_Sqlite3&) = delete;

    /*!
     *  \brief Deleted copy assigment.
     */
    C_Sqlite3& operator=(const C_Sqlite3&) = delete;

    /*!
     *  \brief Deleted move constructor
     */
    C_Sqlite3(C_Sqlite3&&) = delete;

    /*!
     *  \brief Delete move assignment
     */
    C_Sqlite3& operator=(C_Sqlite3&&) = delete;

    /*!
     *  \brief Open a database
     *
     *  \param p_databasePath path to database file
     *  \param p_readOnly set if database has to be open read only
     *  \param p_createIfNeeded set if the database should be created if it does not exists
     *  \param p_openInRam set if the database should be open in ram
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum Open(const std::string& p_databasePath,
                           const bool p_readOnly,
                           const bool p_createIfNeeded,
                           const bool p_openInRam);

    /*!
     *  \brief Close current open database
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum Close();

    /*!
     *  \brief Query whether the database is open or not
     */
    bool IsOpen() const;

    /*!
     *  \brief Execute an Sql
     *
     *  \param p_sql pointer to UTF-8 char array with Sql command
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum ExecuteSql(const char* p_sql);

    /*!
     *  \brief Execute an Sql
     *
     *  \param p_sql reference to std::string with Sql command
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum ExecuteSql(const std::string& p_sql);

    /*!
     *  \brief Get the answer from last Sql query
     */
    TwoReturnCodeEnum GetSqlAnswer(std::list<std::string>& p_columnNames, std::list<std::vector<std::string> >& p_values);

    /*!
     *  \brief Get the last Sql error
     *
     *  \param p_error reference to std::string updated with error string
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum GetSqlError(std::string& p_error);

    /*!
     *  \brief Get the last Sql error
     *
     *  \param p_error reference to integer updated with Sqlite3 error code
     *
     *  \return TwoReturnCodeEnum
     */
    TwoReturnCodeEnum GetSqlError(int& p_error);

    /*!
     *  \brief The Sqlite3Data_t is a structure used in the private implementation
     */
    struct Sqlite3Data_t;


private:


    Sqlite3Data_t* m_data;


};


} /* namespace two { */



#endif // TWO_C_SQLITE3_H
