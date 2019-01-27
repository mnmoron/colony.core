/*----------------------------------------------------------------------------- 
* This file is part of the Colony.Core Project.  The Colony.Core Project is an   
* open source project with a BSD type of licensing agreement.  See the license  
* agreement (license.txt) in the top/ directory or on the Internet at           
* http://integerfox.com/colony.core/license.txt
*                                                                               
* Copyright (c) 2014-2019  John T. Taylor                                        
*                                                                               
* Redistributions of the source code must retain the above copyright notice.    
*----------------------------------------------------------------------------*/ 


#include "StringDecoder.h"
#include <string.h>


///
using namespace Cpl::Text::Frame;



////////////////////////////////////
StringDecoder::StringDecoder( char startOfFrame, char endOfFrame, char escapeChar, const char* inputSourceAsNullTerminatedString )
:Decoder_(0,0)
,m_startPtr(0)
,m_endPtr(0)
,m_srcPtr(inputSourceAsNullTerminatedString)
,m_srcLen(inputSourceAsNullTerminatedString? strlen(inputSourceAsNullTerminatedString): 0)
,m_sof(startOfFrame)
,m_eof(endOfFrame)
,m_esc(escapeChar)
    {
    } 



////////////////////////////////////
bool StringDecoder::scan( size_t maxSizeOfFrame, char* frame, size_t& frameSize ) throw()
    {
    bool result = Decoder_::scan( maxSizeOfFrame, frame, frameSize );
    m_endPtr    = m_dataPtr;
    m_startPtr  = m_endPtr;
    return result;
    }


const char* StringDecoder::getRemainder() const throw()
    {
    return m_endPtr;
    }


////////////////////////////////////
void StringDecoder::setInput( const char* inputSourceAsNullTerminatedString ) throw()
    {
    m_srcPtr = inputSourceAsNullTerminatedString;
    m_srcLen = inputSourceAsNullTerminatedString? strlen(inputSourceAsNullTerminatedString): 0;

    }


void StringDecoder::setInput( const char* inputSoruce, int sizeInBytesOfSource ) throw()
    {
    m_srcPtr = inputSoruce;
    m_srcLen = sizeInBytesOfSource;
    }



////////////////////////////////////////////
bool StringDecoder::isStartOfFrame() throw()   
    { 
    return *m_dataPtr == m_sof; 
    }

bool StringDecoder::isEofOfFrame() throw()     
    { 
    return *m_dataPtr == m_eof; 
    }

bool StringDecoder::isEscapeChar() throw()     
    { 
    return *m_dataPtr == m_esc; 
    }

bool StringDecoder::isLegalCharacter() throw() 
    { 
    return *m_dataPtr != '\0'; 
    }


////////////////////////////////////////////
bool StringDecoder::read( void* buffer, int numBytes, int& bytesRead )
    {
    // Trap missing input source
    if ( !m_srcPtr )
        {
        Cpl::System::FatalError::logf( "Cpl::Text::Frame::StringDecoder::read() - Input source has NOT be set!" );
        return false;  // Should never get here! -->but needed for unittests
        }

    // Return end-of-input if already been decoded/read
    if ( m_srcLen < 0 )
        {
        bytesRead = 0;
        return false;
        }

    // Directly update the parent's data member because I don't want to do a copy (and I didn't provide the parent class a 'work buffer' anyway)
    m_buffer   = (char*) m_srcPtr;
    bytesRead  = m_srcLen;


    // Mark the input string as 'decoded', i.e. a subsequent call to read() is return end-of-input
    m_srcLen   = -1;
    m_startPtr = m_srcPtr;     // Handle the 'remainder' case when starting with a 'fresh' string
    return true;
    }
