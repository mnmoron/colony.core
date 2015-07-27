#ifndef Rte_Db_Record_Handler_h_
#define Rte_Db_Record_Handler_h_
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
/** @file */

#include "Rte/Db/Record/Api.h"


/// Namespace(s)
namespace Rte { namespace Db { namespace Record { 


/** This class defines the interface for Record Handler Interface.  The Record
    Handler manages the loading of ALL records and processes the write requests
    of individual records.
 */
class Handler
{
public:
    /// Starts the record layer handler
    virtual void start(void) = 0;

    /// Stops the record layer handler
    virtual void stop() = 0;


public:
    /// Initiate the write action (to non-volatile storage) for 'recordToWrite'
    virtual void write( Api& recordToWrite ) = 0;

     
public:
    /// Virtual destructor to keep the compiler happy
    virtual ~Handler(void){}


};


};      // end namespaces
};
};
#endif  // end header latch