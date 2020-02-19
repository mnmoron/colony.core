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

#include "colony_config.h"
#include "Cpl/TShell/_0test/statics.h"
#include "Cpl/TShell/Cmd/Tick.h"
#include "Cpl/TShell/Cmd/Threads.h"
#include "Cpl/Dm/MailboxServer.h"
#include "Cpl/System/Thread.h"

#include "Cpl/TShell/Stdio.h"

/// 
extern void shell_test( Cpl::Io::Input& infd, Cpl::Io::Output& outfd );


////////////////////////////////////////////////////////////////////////////////
static Cpl::TShell::Stdio shell_( cmdProcessor_ );

static Cpl::TShell::Cmd::Tick	    tick_( cmdlist );
static Cpl::TShell::Cmd::Threads	threads_( cmdlist );

// Dummy 'timing' runnable object required by SimTick implementation
static Cpl::Dm::MailboxServer appMailbox;

void shell_test( Cpl::Io::Input& infd, Cpl::Io::Output& outfd )
{
    // Start the shell
    shell_.launch( infd, outfd );

    // Create my 'dummy' thread
    Cpl::System::Thread::create( appMailbox, "AppThread", CPL_SYSTEM_THREAD_PRIORITY_NORMAL + CPL_SYSTEM_THREAD_PRIORITY_RAISE );

    // Start the scheduler
    Cpl::System::Api::enableScheduling();
}


