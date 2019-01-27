/*-----------------------------------------------------------------------------
 * * This file is part of the Colony.Core Project.  The Colony.Core Project is an
 * * open source project with a BSD type of licensing agreement.  See the license
 * * agreement (license.txt) in the top/ directory or on the Internet at
 * * http://integerfox.com/colony.core/license.txt
 * *
 * * Copyright (c) 2014 John T. Taylor
 * *
 * * Redistributions of the source code must retain the above copyright notice.
 * *----------------------------------------------------------------------------*/

#include "Cpl/System/ElapsedTime.h"


 /// 
using namespace Cpl::System;



/////////////////////////////////////////////////////////////////
unsigned long ElapsedTime::milliseconds( void ) throw()
{
    return millisecondsInRealTime();
}

unsigned long ElapsedTime::seconds( void ) throw()
{
    return secondsInRealTime();
}

ElapsedTime::Precision_T ElapsedTime::precision( void ) throw()
{
    return precisionInRealTime();
}
