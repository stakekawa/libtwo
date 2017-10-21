/*!
 *  \file c_sqlite3.cpp
 *
 *  \brief This file contains the implementation of the C_Sqlite3 class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#define TWO_SQLITE3_DEBUG

#ifdef TWO_SQLITE3_DEBUG
#include <iostream>
#endif //TWO_SQLITE3_DEBUG
#include <fstream>
#include <list>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "c_sqlite3.h"




namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr int k_sqlite3Timeout = 1000; /* microseconds */


struct C_Sqlite3::Sqlite3Data_t
{
    std::string                         databasePath;
    sqlite3*                            database;
    int                                 error;
    std::string                         errorString;
    std::vector<std::string>            columnNames;
    std::list<std::vector<std::string>> values;

    Sqlite3Data_t() :
        databasePath(),
        database(nullptr),
        error(SQLITE_OK),
        errorString(),
        columnNames(),
        values()
    { /* empty */ }

    /*!
     *  \brief Deleted copy constructor
     */
    Sqlite3Data_t(const Sqlite3Data_t&) = delete;

    /*!
     *  \brief Deleted copy assigment.
     */
    Sqlite3Data_t& operator=(const Sqlite3Data_t&) = delete;

    /*!
     *  \brief Deleted move constructor
     */
    Sqlite3Data_t(Sqlite3Data_t&&) = delete;

    /*!
     *  \brief Delete move assignment
     */
    Sqlite3Data_t& operator=(Sqlite3Data_t&&) = delete;

    void ReadError()
    {
        if (nullptr != database)
        {
            error       = sqlite3_errcode(database);
            errorString = std::string(sqlite3_errmsg(database));
        }
    }

    void ClearError()
    {
        error = SQLITE_OK;
        errorString.clear();
    }

    void Finalize()
    {
        if (nullptr != database)
        {
            sqlite3_stmt* l_statement = nullptr;

            do
            {
                l_statement = sqlite3_next_stmt(database, nullptr);

                const int l_return = sqlite3_finalize(l_statement);

                if (SQLITE_MISUSE == l_return)
                {
                    break;
                }

                if (0 != usleep(k_sqlite3Timeout))
                {
                    /* complain */
                }
            }
            while (nullptr != l_statement);
        }
    }

    bool AddColumnNames(const int p_nColumns, char* p_columnNames[])
    {
        bool l_added = true;

        const size_t l_nColumnsOld = columnNames.size();
        const size_t l_nColumnsNew = static_cast<size_t>(p_nColumns);

        if (0 == p_nColumns)
        {
            columnNames.clear();
        }
        else if (nullptr == p_columnNames)
        {
            l_added = false;
        }
        else if (0 == l_nColumnsOld)
        {
            for (size_t i = 0; i < l_nColumnsNew; ++i)
            {
                std::string l_columnName;

                if (nullptr != p_columnNames[i])
                {
                    l_columnName = std::string(p_columnNames[i]);
                }

                columnNames.emplace_back(std::move(l_columnName));
            }
        }
        else
        {
            l_added = l_nColumnsNew == l_nColumnsOld;
        }

        return l_added;
    }

    bool AddValues(const int p_nColumns, char* p_values[])
    {
        bool l_added = true;

        const size_t l_nColumns = static_cast<size_t>(p_nColumns);

        if (nullptr == p_values)
        {
            l_added = false;
        }
        else
        {

            std::vector<std::string> l_values;

            l_values.resize(l_nColumns);

            for (size_t i = 0; i < l_nColumns; ++i)
            {

                if (nullptr != p_values[i])
                {
                    l_values[i] = std::string(p_values[i]);
                }
            }

            values.emplace_back(std::move(l_values));
        }

        return l_added;
    }

    void ClearData()
    {
        columnNames.clear();
        values.clear();
    }

    int GetRowsNumber() const
    {
        return static_cast<int>(values.size());
    }

};



/*                                                                            */
/* Private data                                                               */
/*                                                                            */


int sqlite3_exec_callback(void* p_arg, int p_nColumns, char* p_values[], char* p_columnNames[])
{
#ifdef TWO_SQLITE3_DEBUG
    std::cout << " " << __func__ << " with " << p_nColumns << " columns\n";
#endif // TWO_SQLITE3_DEBUG

    int l_returnValue = SQLITE_OK; /* SQLITE_OK    == keep going */
                                   /* SQLITE_ABORT == stop       */

    if (nullptr == p_arg)
    {
        l_returnValue = SQLITE_ABORT;
    }
    else
    {
        C_Sqlite3::Sqlite3Data_t* l_data = reinterpret_cast<C_Sqlite3::Sqlite3Data_t*>(p_arg);

        bool l_return = true;

        l_return = l_return && l_data->AddValues(p_nColumns, p_values);
        l_return = l_return && l_data->AddColumnNames(p_nColumns, p_columnNames);

        if (false == l_return)
        {
            l_returnValue = SQLITE_ABORT;
        }

#ifdef TWO_SQLITE3_DEBUG
        const int l_nRows = l_data->GetRowsNumber();

        std::cout << " " << __func__ << " Row : " << l_nRows << "\n";

        if (0 < l_nRows)
        {
            std::list<std::vector<std::string> >::iterator it_row = l_data->values.begin();

            if (1 < l_nRows)
            {
                std::advance(it_row, l_nRows - 1);
            }

            for (size_t i = 0; i < static_cast<size_t>(p_nColumns) && i < l_data->columnNames.size(); ++i)
            {
                std::cout << " " << __func__ << " Column " << i << " : " << l_data->columnNames[i] << " | " << (*it_row)[i] << "\n";
            }
        }
#endif // TWO_SQLITE3_DEBUG

    }

#ifdef TWO_SQLITE3_DEBUG
    std::cout << " " << __func__ << " Return value: " << l_returnValue << "\n";
#endif // TWO_SQLITE3_DEBUG

    return l_returnValue;
}


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_Sqlite3::C_Sqlite3() :
    m_data(new Sqlite3Data_t())
{

}


C_Sqlite3::~C_Sqlite3()
{
    Close();
}


TwoReturnCodeEnum C_Sqlite3::Open(const std::string& p_databasePath,
                                  const bool p_readOnly,
                                  const bool p_createIfNeeded,
                                  const bool p_openInRam)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    Close();

    int l_flags = 0;

    l_flags |= (true == p_readOnly) ? SQLITE_OPEN_READONLY : SQLITE_OPEN_READWRITE;

    /* add SQLITE_OPEN_CREATE only if not in read only */
    /* because create a database is a write operation  */

    if ((true  == p_createIfNeeded) &&
        (false == p_readOnly))
    {
        l_flags |= SQLITE_OPEN_CREATE;
    }

    l_flags |= SQLITE_OPEN_FULLMUTEX;

    if (true == p_databasePath.empty())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else if (false == std::fstream(p_databasePath.c_str()).good())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileNotFound;
    }
    else if (SQLITE_OK != sqlite3_open_v2(p_databasePath.c_str(), &m_data->database, l_flags, NULL))
    {
        m_data->ReadError();

        int l_return = SQLITE_OK;

        do
        {
            l_return = sqlite3_close_v2(m_data->database);

            switch (l_return)
            {
                case SQLITE_MISUSE:
                    l_return = SQLITE_OK; /* so it exits loop */
                    break;
                case SQLITE_BUSY:
                    if (0 != usleep(k_sqlite3Timeout))
                    {
                        /* complain */
                    }
                    break;
                default:
                    m_data->Finalize();
                    break;
            }
        }
        while (SQLITE_OK != l_return);

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeError;
    }
    else
    {

    } /* end if (true == p_databasePath.empty()) else */

    return l_returnCode;
}


TwoReturnCodeEnum C_Sqlite3::Close()
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    m_data->Finalize();

    int l_return = SQLITE_OK;

    do
    {
        l_return = sqlite3_close_v2(m_data->database);

        switch (l_return)
        {
            case SQLITE_MISUSE:
                l_return = SQLITE_OK; /* so it exits loop */
                break;
            case SQLITE_BUSY:
                if (0 != usleep(k_sqlite3Timeout))
                {
                    /* complain */
                }
                break;
            default:
                break;
        }
    }
    while (SQLITE_OK != l_return);

    m_data->ClearError();

    m_data->databasePath.clear();
    m_data->database = nullptr;

    return l_returnCode;
}


bool C_Sqlite3::IsOpen() const
{
    return (nullptr != m_data->database);
}


TwoReturnCodeEnum C_Sqlite3::ExecuteSql(const char* p_sql)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    if (nullptr == p_sql)
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeInvalidParameters;
    }
    else
    {
        m_data->Finalize();

        int   l_return  = SQLITE_OK;
        char* l_errMsg = NULL;

        do
        {
            l_return = sqlite3_exec(m_data->database, p_sql, &sqlite3_exec_callback, m_data, &l_errMsg);

            if (SQLITE_BUSY == l_return)
            {
                if (0 != usleep(k_sqlite3Timeout))
                {
                    /* complain */
                }

                continue;
            }

            if (SQLITE_OK != l_return)
            {
                m_data->error       = SQLITE_ERROR;
                m_data->errorString = std::string(l_errMsg);
                l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSqliteError;
            }

            sqlite3_free(l_errMsg);

        } while (SQLITE_BUSY == l_return);

        m_data->Finalize();
    }

    return l_returnCode;
}


TwoReturnCodeEnum C_Sqlite3::ExecuteSql(const std::string& p_sql)
{
    return ExecuteSql(p_sql.c_str());
}


TwoReturnCodeEnum C_Sqlite3::GetSqlAnswer(std::list<std::string>& p_columnNames, std::list<std::vector<std::string> >& p_values)
{
    p_columnNames.assign(m_data->columnNames.begin(), m_data->columnNames.end());
    p_values.assign(m_data->values.begin(), m_data->values.end());
}


TwoReturnCodeEnum C_Sqlite3::GetSqlError(std::string& p_error)
{
    p_error = m_data->errorString;
}


TwoReturnCodeEnum C_Sqlite3::GetSqlError(int& p_error)
{
    p_error = m_data->error;
}


} /* namespace two { */
