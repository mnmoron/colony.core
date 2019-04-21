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

#include "Cpl/System/GlobalLock.h"
#include "Cpl/System/Mutex.h"


static Cpl::System::Mutex  global_;


//////////////////////////////////////////////////////////////////////////////
void Cpl::System::GlobalLock::begin( void )
{
    global_.lock();
}

void Cpl::System::GlobalLock::end( void )
{
    global_.unlock();
}



