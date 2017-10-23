/*!
 *  \file defines.h
 *
 *  \brief This files include the definitions of the Two library
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef TWO_DEFINES_H
#define TWO_DEFINES_H


#define TWO_NOT_IMPLEMENTED                                       assert(false);

#define TWO_DEFAULT_COPY(Class)                   Class(const Class&) = default; \
                                       Class &operator=(const Class&) = default;

#define TWO_DEFAULT_MOVE(Class)                        Class(Class&&) = default; \
                                            Class &operator=(Class&&) = default;

#define TWO_DISABLE_COPY(Class)                    Class(const Class&) = delete; \
                                        Class &operator=(const Class&) = delete;

#define TWO_DISABLE_MOVE(Class)                         Class(Class&&) = delete; \
                                             Class &operator=(Class&&) = delete;


#endif // TWO_DEFINES_H
