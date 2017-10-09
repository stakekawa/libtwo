/*!
 *  \file c_textfilereader.h
 *
 *  \brief This file contains the declaration of C_TextFileReader class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_C_TEXTFILEREADER_H
#define TWO_C_TEXTFILEREADER_H


#include <string>
#include "common.h"


namespace two {


/*!
 *  \brief The C_TextFileReader class is a wrapper around std::ofstream
 *         to read text files.
 */
class C_TextFileReader
{


public:

    /*!
     *  \brief Default constructor
     */
    C_TextFileReader();

    /*!
     *  \brief Destructor
     */
    virtual ~C_TextFileReader();

    /*!
     *  \brief Constructor opening a text file
     *
     *  \param p_fileName std::string with absolute path of text file to open
     */
    explicit C_TextFileReader(const std::string& p_fileName);

    /*!
     *  \brief Constructor opening a text file
     *
     *  \param p_fileName std::string with absolute path of text file to open
     */
    explicit C_TextFileReader(std::string&& p_fileName);

    /*!
     *  \brief Open a text file
     *
     *  \param p_fileName absolute path of text file to open
     *
     *  \return TwoReturnCodeEnum with status
     */
    TwoReturnCodeEnum Open(const std::string& p_fileName);

    /*!
     *  \brief Open a text file
     *
     *  \param p_fileName absolute path of text file to open
     *
     *  \return TwoReturnCodeEnum with status
     */
    TwoReturnCodeEnum Open(std::string&& p_fileName);

    /*!
     *  \brief Close current file (if open)
     */
    void Close();

    /*!
     *  \brief Get the content of next line
     *
     *  \param p_line std::string updated with content of read line
     *  \param p_lineNumber number of line just read
     *
     *  \return TwoReturnCodeEnum with status
     */
    TwoReturnCodeEnum GetLine(std::string& p_line, int& p_lineNumber);

    /*!
     *  \brief Get the size in bytes of the text file. A zero size is returned
     *         when no file is open
     *
     *  \return the size of the open file in bytes
     */
    size_t GetFileSize() const;

    /*!
     *  \brief Get the file name of current open file
     */
    std::string GetFileName() const;

    /*!
     *  \brief Query if current file is opened
     *
     *  \return true or false
     */
    bool IsOpen() const;

    /*!
     *  \brief Query if reached the end of current file
     *
     *  \return true or false
     */
    bool IsEof() const;

    /*!
     *  \brief Deleted copy constructor
     */
    C_TextFileReader(const C_TextFileReader&) = delete;

    /*!
     *  \brief Deleted copy assignment
     */
    C_TextFileReader& operator=(const C_TextFileReader&) = delete;

    /*!
     *  \brief Deleted move constructor
     */
    C_TextFileReader(C_TextFileReader&&) = delete;

    /*!
     *  \brief Delete move assignment
     */
    C_TextFileReader& operator=(C_TextFileReader&&) = delete;


};


} /* end namespace two { */


#endif // TWO_C_TEXTFILEREADER_H
