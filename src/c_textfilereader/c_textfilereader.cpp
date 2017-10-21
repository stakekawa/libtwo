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


struct C_TextFileReader::FileReaderData_t
{
    std::ifstream file;
    size_t        fileSize;
    std::string   fileName;
    int           lineNumber;

    FileReaderData_t() :
        file(),
        fileSize(k_fileSizeDefault),
        fileName(),
        lineNumber(k_lineNumberDefault)
    { /* empty */ }
};



/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_TextFileReader::C_TextFileReader() :
    m_data(new FileReaderData_t())
{

}


/* virtual */
C_TextFileReader::~C_TextFileReader()
{
    Close();

    delete m_data;
}


/* explicit */
C_TextFileReader::C_TextFileReader(const std::string& p_fileName) :
    m_data(new FileReaderData_t())
{
    Open(p_fileName);
}


/* explicit */
C_TextFileReader::C_TextFileReader(std::string&& p_fileName) :
    m_data(new FileReaderData_t())
{
    Open(std::forward<std::string>(p_fileName));
}


TwoReturnCodeEnum C_TextFileReader::Open(const std::string& p_fileName)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;

    Close(); /* close previous file */

    m_data->file.open(p_fileName, std::fstream::in | std::fstream::ate); /* open the file read-only and move to the end of file */

    if (true == m_data->file.is_open())
    {
        m_data->fileSize = static_cast<size_t>(m_data->file.tellg()); /* get the position - aka size in byte */
        m_data->fileName = p_fileName;

        m_data->file.seekg(std::ios_base::beg); /* set the position at beginning of file */

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


TwoReturnCodeEnum C_TextFileReader::Open(std::string&& p_fileName)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;

    Close(); /* close previous file */

    m_data->file.open(p_fileName, std::fstream::in | std::fstream::ate); /* open the file read-only and move to the end of file */

    if (true == m_data->file.is_open())
    {
        m_data->fileSize = static_cast<size_t>(m_data->file.tellg()); /* get the position - aka size in byte */
        std::swap(m_data->fileName, p_fileName);

        m_data->file.seekg(std::ios_base::beg); /* set the position at beginning of file */

        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;
    }

    return l_returnCode;
}


void C_TextFileReader::Close()
{
    /* close file if it is open */

    if (true == m_data->file.is_open())
    {
        m_data->file.close();
    }

    m_data->fileSize   = k_fileSizeDefault;
    m_data->fileName.clear();
    m_data->lineNumber = k_lineNumberDefault;
}


TwoReturnCodeEnum C_TextFileReader::GetLine(std::string& p_line, int& p_lineNumber)
{
    TwoReturnCodeEnum l_returnCode = TwoReturnCodeEnum::TwoReturnCodeSuccess;

    p_line.clear();
    p_lineNumber = 0;

    if (false == m_data->file.is_open())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileError;
    }
    else if (true == m_data->file.eof())
    {
        l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileEnd;
    }
    else
    {
        std::getline(m_data->file, p_line);

        ++m_data->lineNumber;

        p_lineNumber = m_data->lineNumber;

        if (true == m_data->file.eof())
        {
            l_returnCode = TwoReturnCodeEnum::TwoReturnCodeFileEnd;
        }
    }

    return l_returnCode;
}


size_t C_TextFileReader::GetFileSize() const
{
    return m_data->fileSize;
}


std::string C_TextFileReader::GetFileName() const
{
    return m_data->fileName;
}


bool C_TextFileReader::IsOpen() const
{
    return m_data->file.is_open();
}


bool C_TextFileReader::IsEof() const
{
    return ((true == m_data->file.is_open()) ? m_data->file.eof() : true); /* return m_data->file.eof() if file is open, return true if it is close */
}


} /* namespace two { */
