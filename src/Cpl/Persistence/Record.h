#ifndef Cpl_Persistence_Record_h_
#define Cpl_Persistence_Record_h_
/*-----------------------------------------------------------------------------
* This file is part of the Colony.Core Project.  The Colony.Core Project is an
* open source project with a BSD type of licensing agreement.  See the license
* agreement (license.txt) in the top/ directory or on the Internet at
* http://integerfox.com/colony.core/license.txt
*
* Copyright (c) 2014-2020  John T. Taylor
*
* Redistributions of the source code must retain the above copyright notice.
*----------------------------------------------------------------------------*/
/** @file */

#include "Cpl/Itc/PostApi.h"
#include "Cpl/Dm/EventLoop.h"


///
namespace Cpl {
///
namespace Persistence {


/** This abstract class defines the public interface for a Record instance. 
    A Record is the atomic-unit that is managed in Persistent storage media.
 */
class Record
{
public:
    /** This method is to start/initialize the record.  It is typically only
        called once at the startup of the application.  However, start() can be
        called after a previous call to the stop() method.

        This method is called when the RecordServer is 'opened'.

        The 'myMbox' is a reference to the RecordServer's ITC mailbox, i.e. the
        mailbox for the thread that the Record executes in. The 'myEventLoop'
        is a reference to the RecordServer's Event Loop.
     */
    virtual void start( Cpl::Itc::PostApi& myMbox, Cpl::Dm::EventLoop& myEventLoop ) noexcept = 0;

    /** This method is to stop/shutdown the record.  It is typically only
        called once during an orderly shutdown of the application. However, 
        start() can be after a previous call to the stop() method.
     */
    virtual void stop() noexcept = 0;


public:
    /// Virtual destructor
    virtual ~Record() {}
};


};      // end namespaces
};
#endif  // end header latch
