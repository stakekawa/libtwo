/*!
 *  \file sqlite3.cpp
 *  \brief Main source of sqlite3 test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("sqlite3");


void testFunction1()
{
    const std::string l_fileName1("test.sqlite");
    std::string l_stringEnum;

    two::C_Sqlite3 l_sqlite3;

    two::TwoReturnCodeEnum l_returnCode = l_sqlite3.Open(l_fileName1, true, false, true);

    std::cout << " " << __func__ << " Opening " << l_fileName1 << " returned " << two::enumToStdString(l_returnCode) << " .\n";

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
    {
        const std::string l_sql("SELECT * FROM 'TestTable1';");

        l_returnCode = l_sqlite3.ExecuteSql(l_sql);

        if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
        {
            std::list<std::string>               l_columnNames;
            std::list<std::vector<std::string> > l_values;

            l_returnCode = l_sqlite3.GetSqlAnswer(l_columnNames, l_values);

            if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
            {
                std::cout << "| ";

                for (const std::string& l_columnName : l_columnNames)
                {
                    std::cout << l_columnName << " | ";
                }

                std::cout << "\n";

                for (const std::vector<std::string>& l_row : l_values)
                {
                    std::cout << "| ";

                    for (const std::string& l_value : l_row)
                    {
                        std::cout << l_value << " | ";
                    }

                    std::cout << "\n";
                }
            }
        }
    }

    std::cout << "\n";
}


void testFunction2()
{
    const std::string l_fileName1("doesnotexist.sqlite");
    const std::string l_fileName2("test.sqlite");

    std::string l_stringEnum;

    two::C_Sqlite3 l_sqlite3;

    two::TwoReturnCodeEnum l_returnCode = l_sqlite3.Open(l_fileName1, true, false, true);

    std::cout << " " << __func__ << " Opening " << l_fileName1 << " returned " << two::enumToStdString(l_returnCode) << " .\n";

    l_returnCode = l_sqlite3.Open(l_fileName2, true, false, true);

    std::cout << " " << __func__ << " Opening " << l_fileName2 << " returned " << two::enumToStdString(l_returnCode) << " .\n";

    if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
    {
        const std::string l_sql("SELECT * FROM 'WrongSyntax");

        l_returnCode = l_sqlite3.ExecuteSql(l_sql);

        if (two::TwoReturnCodeEnum::TwoReturnCodeSuccess == l_returnCode)
        {
            std::cout << " " << __func__ << " Unexpected return value\n";
        }
        else
        {
            std::string l_error;

            (void)l_sqlite3.GetSqlError(l_error);

            std::cout << " " << __func__ << " " << l_sql << " returned " << two::enumToStdString(l_returnCode) << "\n";
        }

    }

}


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();

    testFunction2();

    std::cout << std::endl;

    return l_exitValue;
}
