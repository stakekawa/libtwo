/*!
 *  \file two.h
 *
 *  \brief This is the API header of the C++ Two library
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Personal use only - No commercial
 */


#ifndef TWO_H
#define TWO_H


/*                                                                            */
/* definition of version stuff                                                */
/*                                                                            */
#define TWO_LIBRARY_VERSION_STRING                 "0.0.1"
#define TWO_LIBRARY_VERSION_MAJOR                  0
#define TWO_LIBRARY_VERSION_MINOR                  0
#define TWO_LIBRARY_VERSION_PATCH                  1
#define TWO_LIBRARY_VERSION                        (10000 * TWO_LIBRARY_VERSION_MAJOR + \
                                                    100 * TWO_LIBRARY_VERSION_MINOR + \
                                                    TWO_LIBRARY_VERSION_PATCH )

/*                                                                            */
/* layers includes                                                            */
/*                                                                            */
#include "two/c_logger.h"
#include "two/colorizeString.h"
#include "two/common.h"


#endif // TWO_H
