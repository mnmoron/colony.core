/*-----------------------------------------------------------------------------
* This file is part of the Colony.Core Project.  The Colony.Core Project is an
* open source project with a BSD type of licensing agreement.  See the license
* agreement (license.txt) in the top/ directory or on the Internet at
* http://integerfox.com/colony.core/license.txt
*
* Copyright (c) 2014-2018  John T. Taylor
*
* Redistributions of the source code must retain the above copyright notice.
*----------------------------------------------------------------------------*/

#include "ServiceMessage.h"

//
using namespace Cpl::Itc;


/////////////////////////////////////
ServiceMessage::ServiceMessage( ReturnHandler& rh ) throw()
    :m_rh( rh )
{
}

void ServiceMessage::returnToSender() throw()
{
    m_rh.rts();
}

