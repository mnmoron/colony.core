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

#include "Catch/catch.hpp"
#include "Cpl/System/_testsupport/Shutdown_TS.h"
#include "common.h"

/// This method is used as part of 'forcing' this object to being actualled 
/// linked during the NQBP link process (it is artifact of linking libraries 
/// and how CATCH auto-registers (via static objects) test case
void link_simmvc(void) {}



/// 
using namespace Cpl::Itc;

////////////////////////////////////////////////////////////////////////////////
/* The test app consists of 3 threads:
   - Two client threads, one contains a viewer, the other contains a writer
   - One model thread that 'owns' the data being viewed/written
*/

////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "simmvc", "[simmvc]" )
    {
    CPL_SYSTEM_TRACE_FUNC( SECT_ );
    Cpl::System::Shutdown_TS::clearAndUseCounter();


    MyMailboxServer   modelMbox;
    Model             myModel(modelMbox);
    ViewRequest::SAP  modelViewSAP(myModel,modelMbox);

    MailboxServer     viewerMbox;
    Viewer            myViewer( 0, viewerMbox, modelViewSAP );

    Master            masterRun( NUM_SEQ_, NUM_WRITES_, myViewer, myModel, myModel, Cpl::System::Thread::getCurrent(), true );

    Cpl::System::Thread* t1 = Cpl::System::Thread::create( viewerMbox, "Viewer" );
    Cpl::System::Thread* t2 = Cpl::System::Thread::create( modelMbox,  "Model" );
    Cpl::System::Thread* t3 = Cpl::System::Thread::create( masterRun,  "MASTER" );
    Cpl::System::Api::sleep( 50 ); // Allow time for threads to actually spin-up

    // Test the default signal handler 
    viewerMbox.signal();

    // Validate result of each sequence
    int i;
    for(i=0; i< NUM_SEQ_; i++ )
        {
        modelMbox.signal();
        CPL_SYSTEM_TRACE_MSG( SECT_, ( "@@ TICK SOURCE: Starting sequence# %d...", i+1 ));
        Cpl::System::SimTick::advance( 500 );  // Note: This method will 'time out' once the MASTER thread is blocked at the end of the each Sequence, i.e. ALL Application threads blocked for non-time/tick reasons
        CPL_SYSTEM_TRACE_MSG( SECT_, ( "  @@ TICK SOURCE: pause before checking result for seq# %d.  Seq completd at sim tick count of: %lu", i+1, Cpl::System::SimTick::current() ));
        Cpl::System::Api::sleepInRealTime( 50 );
        REQUIRE( myModel.m_value == (NUM_WRITES_ - 1) * ATOMIC_MODIFY_ );
        REQUIRE( myViewer.m_attachRspMsg.getPayload().m_value == (NUM_WRITES_ - 1 ) * ATOMIC_MODIFY_ );
        REQUIRE( myViewer.m_ownAttachMsg == true );
        REQUIRE( myViewer.m_ownDetachMsg == true );
        REQUIRE( myViewer.m_pendingCloseMsgPtr == 0 );
        REQUIRE( myViewer.m_opened == false );
        REQUIRE( modelMbox.m_sigCount == i+1 );
        t3->signal();
        }


    // Wait for all of the sequences to complete
    Cpl::System::SimTick::advance( 10 );
    Cpl::System::Thread::wait();
    
    // Shutdown threads
    viewerMbox.pleaseStop();
    modelMbox.pleaseStop();
    Cpl::System::SimTick::advance( 50 );
    Cpl::System::Api::sleep(50); // allow time for threads to stop
    REQUIRE( t1->isRunning() == false );
    REQUIRE( t2->isRunning() == false );
    REQUIRE( t3->isRunning() == false );

    Cpl::System::Thread::destroy( *t1 );
    Cpl::System::Thread::destroy( *t2 );
    Cpl::System::Thread::destroy( *t3 );
    REQUIRE( Cpl::System::Shutdown_TS::getAndClearCounter() == 0u );
    }
