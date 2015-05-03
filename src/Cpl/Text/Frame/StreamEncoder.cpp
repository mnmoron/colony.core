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


#include "StreamEncoder.h"


///
using namespace Cpl::Text::Frame;



///////////////////////////////////
StreamEncoder::StreamEncoder( Cpl::Io::Output& dst, char startOfFrame, char endOfFrame, char escapeChar, bool appendNewline )
:Encoder_(startOfFrame, endOfFrame, escapeChar, appendNewline)
,m_dst(dst)
    {
    }



///////////////////////////////////
bool StreamEncoder::start( char src ) throw()
    {
    return m_dst.write(src);
    }

bool StreamEncoder::start() throw()
    {
    // Nothing to do for stream output
    return true;
    }

bool StreamEncoder::append( char src ) throw()
    {
    return m_dst.write(src);
    }
