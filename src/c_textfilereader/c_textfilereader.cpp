/*!
 *  \file c_textfilereader.cpp
 *
 *  \brief This file contains the implementation of C_TextFileReader class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <fstream>
#include "c_textfilereader.h"


namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr size_t k_fileSizeDefault   = 0;
static constexpr int    k_lineNumberDefault = 0;
static std::ifstream    g_file;
static size_t           g_fileSize;
static std::string      g_fileName;
static int              g_lineNumber;


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_TextFileReader::C_TextFileReader()
{

}


/* virtual */
C_TextFileReader::~C_TextFileReader()
{
    Close();
}


/* explicit */
C_TextFileReader::C_TextFileReader(const std::string& p_fileName)
{
    Open(p_fileName);
}


/* explicit */
C_TextFileReader::C_TextFileReader(std::string&& p_fileName)
{
    Open(std::forward<std::string>(p_fileName));
}


TwoReturnCodeEnum C_TextFileReader::Open(const std::string& p_fileName)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;

    Close(); /* close previous file */

    g_file.open(p_fileName, std::fstream::in | std::fstream::ate); /* open the file read-only and move to the end of file */

    if (true == g_file.is_open())
    {
        g_fileSize = static_cast<size_t>(g_file.tellg()); /* get the position - aka size in byte */
        g_fileName = p_fileName;

        g_file.seekg(std::ios_base::beg); /* set the position at beginning of file */

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


TwoReturnCodeEnum C_TextFileReader::Open(std::string&& p_fileName)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;

    Close(); /* close previous file */

    g_file.open(p_fileName, std::fstream::in | std::fstream::ate); /* open the file read-only and move to the end of file */

    if (true == g_file.is_open())
    {
        g_fileSize = static_cast<size_t>(g_file.tellg()); /* get the position - aka size in byte */
        std::swap(g_fileName, p_fileName);

        g_file.seekg(std::ios_base::beg); /* set the position at beginning of file */

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


void C_TextFileReader::Close()
{
    /* close file if it is open */

    if (true == g_file.is_open())
    {
        g_file.close();
    }

    g_fileSize   = k_fileSizeDefault;
    g_fileName.clear();
    g_lineNumber = k_lineNumberDefault;
}


TwoReturnCodeEnum C_TextFileReader::GetLine(std::string& p_line, int& p_lineNumber)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    p_line.clear();
    p_lineNumber = 0;

    if (false == g_file.is_open())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;
    }
    else if (true == g_file.eof())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileEnd;
    }
    else
    {
        std::getline(g_file, p_line);

        ++g_lineNumber;

        p_lineNumber = g_lineNumber;

        if (true == g_file.eof())
        {
            l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileEnd;
        }
    }

    return l_returnCode;
}


size_t C_TextFileReader::GetFileSize() const
{
    return g_fileSize;
}


std::string C_TextFileReader::GetFileName() const
{
    return g_fileName;
}


bool C_TextFileReader::IsOpen() const
{
    return g_file.is_open();
}


bool C_TextFileReader::IsEof() const
{
    return ((true == g_file.is_open()) ? g_file.eof() : true); /* return g_file.eof() if file is open, return true if it is close */
}


} /* end namespace two { */
