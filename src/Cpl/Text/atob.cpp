/*----------------------------------------------------------------------------- 
* This file is part of the Colony.Core Project.  The Colony.Core Project is an   
* open source project with a BSD type of licensing agreement.  See the license  
* agreement (license.txt) in the top/ directory or on the Internet at           
* http://integerfox.com/colony.core/license.txt
*                                                                               
* Copyright (c) 2014, 2015  John T. Taylor                                        
*                                                                               
* Redistributions of the source code must retain the above copyright notice.    
*----------------------------------------------------------------------------*/ 
#include "atob.h"
#include <stdint.h>
#include <string.h>


//
using namespace Cpl::Text;

///////////////////
static bool conversionOk(const char* originalString, char* endPtr, const char* validStopChars)
    {
    // No conversion occurred
    if ( !originalString || *originalString == '\0' || endPtr == originalString ) 
        {
        return false;
        }

    // Valid conversion (stopped on End-of-String)
    if ( *endPtr == '\0' )
        {
        return true;
        }

    // At least a partial conversion occured, determine if it is OK
    while( validStopChars && *validStopChars != '\0' )
        {
        if ( *endPtr == *validStopChars )
            {
            return true;
            }
        validStopChars++;
        }

    return false;
    }


///////////////////
bool Cpl::Text::a2i(int& convertedValue, const char* string, int base, const char* validStopChars, const char** end )
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = (int)strtol(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }

bool Cpl::Text::a2ui(unsigned& convertedValue, const char* string, int base, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = (unsigned)strtoul(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }


bool Cpl::Text::a2l(long& convertedValue, const char* string, int base, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = strtol(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }

bool Cpl::Text::a2ul(unsigned long& convertedValue, const char* string, int base, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = strtoul(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }
    
bool Cpl::Text::a2ll(long long& convertedValue, const char* string, int base, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = strtoll(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }

bool Cpl::Text::a2ull(unsigned long long& convertedValue, const char* string, int base, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = strtoull(string,&endPtr,base);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }

///////////////////
bool Cpl::Text::a2d(double& convertedValue, const char* string, const char* validStopChars, const char** end)
    {
    char* endPtr;
    if ( string )
        {
        convertedValue = strtod(string,&endPtr);
        }
    if ( end ) 
        {
        *end = endPtr;
        }

    return conversionOk(string,endPtr,validStopChars); 
    }

///////////////////
bool Cpl::Text::a2b(bool& convertedValue, const char* string, const char* trueToken, const char* falseToken, const char** end )
    {
    size_t tokenSize = 0;
    bool   result    = false;

    if ( !string || !trueToken || !falseToken )
        {
        return false;
        }

    if ( strncmp(string,trueToken,strlen(trueToken)) == 0 )
        {
        convertedValue = true;
        tokenSize      = strlen(trueToken);
        result         = true;
        }
    else if ( strncmp(string,falseToken,strlen(falseToken)) == 0 )
        {
        convertedValue = false;
        tokenSize      = strlen(falseToken);
        result         = true;
        }

    if ( end )
        {
        *end = string + tokenSize;
        }

    return result;
    }

///////////////////
bool Cpl::Text::asciiHexToBuffer( void* dstBinary, const char* srcP, size_t dstMaxLen )
    {
    if ( !dstBinary || !srcP || dstMaxLen == 0 )
        {
        return false;
        }

    char        temp[3] = { '\0', };
    uint8_t*    dstP    = (uint8_t*)dstBinary;
    size_t      len     = strlen(srcP);
    unsigned    rawByte;
    size_t      i;

    // Length must be even
    if ( (len&1) == 1 )
        {
        return false;
        }

    // Walk the entire string
    for(i=0; i<len; i+=2)
        {
        // Do NOT exceed the destination buffer 
        if ( i/2 >= dstMaxLen )
            {
            return false;
            }

        // Convert the data
        temp[0] = *srcP++;
        temp[1] = *srcP++;
        if ( !a2ui(rawByte,temp,16) )
            {
            // Error -->end conversion
            return false;
            }

        *dstP++ = (uint8_t)rawByte;
        }

    return true;
    }
