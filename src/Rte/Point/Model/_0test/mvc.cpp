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
void link_mvc(void) {}






////////////////////////////////////////////////////////////////////////////////
/* The test app consists of 3 threads:
   - Two client threads, one contains a viewer, the other contains a writer
   - One model thread that 'owns' the data being viewed/written
*/


// Viewers
ViewerContext v1_( "V1", viewerMailbox_, modelBar1_, modelBar2_, modelBar3_, true, false, true );
ViewerContext v2_( "V2", viewerMailbox_, modelBar1_, modelBar2_, modelBar3_, true, true, false );


////////////////////////////////////////////////////////////////////////////////
TEST_CASE( "mvc", "[mvc]" )
    {
    CPL_SYSTEM_TRACE_FUNC( SECT_ );
    Cpl::System::Shutdown_TS::clearAndUseCounter();

    Cpl::System::Thread* modelThreadPtr  = Cpl::System::Thread::create( modelMailbox_,  "MODEL" );
    Cpl::System::Thread* viewerThreadPtr = Cpl::System::Thread::create( viewerMailbox_,  "Viewer" );

    // Start viewers
    v1_.open();
    v2_.open();


    // I cheat here and directly access my Viewer objects since (in theory) they only 'do something' when there is model change
    // CHECK FOR: initial state
    REQUIRE( v1_.m_changed1Count == 1 );
    REQUIRE( v1_.m_changed2Count == 1 );
    REQUIRE( v1_.m_changed3Count == 1 );
    REQUIRE( v2_.m_changed1Count == 1 );
    REQUIRE( v2_.m_changed2Count == 1 );
    REQUIRE( v2_.m_changed3Count == 1 );

    // BAR1 Query
    Point::QueryBar1 queryBar1( modelBar1_ );
    queryBar1.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar1_( queryBar1, "Bar1", "Query - model point in its initial state" );
    REQUIRE( queryBar1.m_tuple.m_name.isValid() == false );
    REQUIRE( queryBar1.m_tuple.m_enabled.isValid() == false );
    REQUIRE( queryBar1.m_tuple.m_count.isValid() == false );

    /// BAR1 Controller 
    Point::ControllerBar1 controllerBar1( modelBar1_ );
    controllerBar1.m_tuple.m_name.setInUse();
    controllerBar1.m_tuple.m_name.setValid();
    controllerBar1.m_tuple.m_name.set("bob");
    controllerBar1.m_tuple.m_enabled.setInUse();
    controllerBar1.m_tuple.m_enabled.setValid();
    controllerBar1.m_tuple.m_enabled.set(true);
    controllerBar1.m_tuple.m_count.setInUse();
    controllerBar1.m_tuple.m_count.setValid();
    controllerBar1.m_tuple.m_count.set(12);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar1.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar1.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar1_( queryBar1, "Bar1", "Query - after initial controller write" );
    REQUIRE( queryBar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( queryBar1.m_tuple.m_enabled.get() == true );
    REQUIRE( queryBar1.m_tuple.m_count.get() == 12 );
    REQUIRE( queryBar1.m_tuple.m_name.isValid() == true );
    REQUIRE( queryBar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( queryBar1.m_tuple.m_count.isValid() == true );
    REQUIRE( v1_.m_changed1Count == 2 );
    REQUIRE( v1_.m_changed2Count == 1 );
    REQUIRE( v1_.m_changed3Count == 1 );
    REQUIRE( v2_.m_changed1Count == 2 );
    REQUIRE( v2_.m_changed2Count == 1 );
    REQUIRE( v2_.m_changed3Count == 1 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.get() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.get() == 12 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.get() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.get() == 12 );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.isValid() == true );

    controllerBar1.setAllInUseState(false);
    controllerBar1.m_tuple.m_enabled.setInUse();
    controllerBar1.m_tuple.m_enabled.set(false);
    controllerBar1.m_tuple.m_name.set("bobs not here"); // Should NOT change since 'in-use' is marked as false
    controllerBar1.m_tuple.m_count.set(36);             // Should NOT change since 'in-use' is marked as false
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar1.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar1.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar1_( queryBar1, "Bar1", "Query - after update of 'm_enabled'" );
    REQUIRE( queryBar1.m_tuple.m_name.isValid() == true );
    REQUIRE( queryBar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( queryBar1.m_tuple.m_count.isValid() == true );
    REQUIRE( queryBar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( queryBar1.m_tuple.m_enabled.get() == false );
    REQUIRE( queryBar1.m_tuple.m_count.get() == 12 );
    REQUIRE( v1_.m_changed1Count == 3 );
    REQUIRE( v1_.m_changed2Count == 1 );
    REQUIRE( v1_.m_changed3Count == 1 );
    REQUIRE( v2_.m_changed1Count == 3 );
    REQUIRE( v2_.m_changed2Count == 1 );
    REQUIRE( v2_.m_changed3Count == 1 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.get() == false );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.get() == 12 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.get() == false );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.get() == 12 );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.isValid() == true );
 
    controllerBar1.m_tuple.m_count.setInUse();
    controllerBar1.m_tuple.m_count.set(6);
    controllerBar1.m_tuple.m_enabled.set(true);        // Should change since it is 'in-use' flag is still true!
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar1.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar1.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar1_( queryBar1, "Bar1", "Query - after update of 'm_count'" );
    REQUIRE( queryBar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( queryBar1.m_tuple.m_enabled.get() == true );
    REQUIRE( queryBar1.m_tuple.m_count.get() == 6 );
    REQUIRE( v1_.m_changed1Count == 4 );
    REQUIRE( v1_.m_changed2Count == 1 );
    REQUIRE( v1_.m_changed3Count == 1 );
    REQUIRE( v2_.m_changed1Count == 4 );
    REQUIRE( v2_.m_changed2Count == 1 );
    REQUIRE( v2_.m_changed3Count == 1 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.get() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.get() == 6 );
    REQUIRE( v1_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v1_.m_bar1.m_tuple.m_count.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.getString() == "bob" );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.get() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.get() == 6 );
    REQUIRE( v2_.m_bar1.m_tuple.m_name.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_enabled.isValid() == true );
    REQUIRE( v2_.m_bar1.m_tuple.m_count.isValid() == true );

    
    // BAR2 Query
    Point::QueryBar2 queryBar2( modelBar2_ );
    queryBar2.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar2_( queryBar2, "Bar2", "Query - model point in its initial state" );
    REQUIRE( queryBar2.m_foo1.m_name.isValid() == false );
    REQUIRE( queryBar2.m_foo1.m_enabled.isValid() == false );
    REQUIRE( queryBar2.m_foo1.m_count.isValid() == false );
    REQUIRE( queryBar2.m_foo2.m_enabled.isValid() == false );
    REQUIRE( queryBar2.m_foo2.m_limit.isValid() == false );

    /// BAR2 Controller 
    Point::ControllerBar2 controllerBar2( modelBar2_ );
    controllerBar2.setAllInUseState(true);
    controllerBar2.setAllValidFlagState(true);
    controllerBar2.m_foo1.m_name.set("charlie");
    controllerBar2.m_foo1.m_enabled.set(false);
    controllerBar2.m_foo1.m_count.set(42);
    controllerBar2.m_foo2.m_enabled.set(true);
    controllerBar2.m_foo2.m_limit.set(100);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar2.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar2.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar2_( queryBar2, "Bar2", "Query - after initial controller write" );
    REQUIRE( queryBar2.m_foo1.m_name.getString() == "charlie" );
    REQUIRE( queryBar2.m_foo1.m_enabled.get() == false );
    REQUIRE( queryBar2.m_foo1.m_count.get() == 42 );
    REQUIRE( queryBar2.m_foo2.m_enabled.get() == true );
    REQUIRE( queryBar2.m_foo2.m_limit.get() == 100 );
    REQUIRE( queryBar2.m_foo1.m_name.isValid() == true );
    REQUIRE( queryBar2.m_foo1.m_enabled.isValid() == true );
    REQUIRE( queryBar2.m_foo1.m_count.isValid() == true );
    REQUIRE( queryBar2.m_foo2.m_enabled.isValid() == true );
    REQUIRE( queryBar2.m_foo2.m_limit.isValid() == true );
    REQUIRE( v1_.m_changed1Count == 4 );
    REQUIRE( v1_.m_changed2Count == 1 );
    REQUIRE( v1_.m_changed3Count == 1 );
    REQUIRE( v2_.m_changed1Count == 4 );
    REQUIRE( v2_.m_changed2Count == 2 );
    REQUIRE( v2_.m_changed3Count == 1 );
    REQUIRE( v1_.m_bar2.m_foo1.m_name.isValid() == false );
    REQUIRE( v1_.m_bar2.m_foo1.m_enabled.isValid() == false );
    REQUIRE( v1_.m_bar2.m_foo1.m_count.isValid() == false );
    REQUIRE( v1_.m_bar2.m_foo2.m_enabled.isValid() == false );
    REQUIRE( v1_.m_bar2.m_foo2.m_limit.isValid() == false );
    REQUIRE( v2_.m_bar2.m_foo1.m_name.getString() == "charlie" );
    REQUIRE( v2_.m_bar2.m_foo1.m_enabled.get() == false );
    REQUIRE( v2_.m_bar2.m_foo1.m_count.get() == 42 );
    REQUIRE( v2_.m_bar2.m_foo2.m_enabled.get() == true );
    REQUIRE( v2_.m_bar2.m_foo2.m_limit.get() == 100 );
    REQUIRE( v2_.m_bar2.m_foo1.m_name.isValid() == true );
    REQUIRE( v2_.m_bar2.m_foo1.m_enabled.isValid() == true );
    REQUIRE( v2_.m_bar2.m_foo1.m_count.isValid() == true );
    REQUIRE( v2_.m_bar2.m_foo2.m_enabled.isValid() == true );
    REQUIRE( v2_.m_bar2.m_foo2.m_limit.isValid() == true );


    controllerBar2.setAllInUseState(false);
    controllerBar2.m_foo2.m_enabled.setInUse();
    controllerBar2.m_foo2.m_enabled.set(false);
    controllerBar2.m_foo1.m_name.set("bobs not here"); // Should NOT change since 'in-use' is marked as false
    controllerBar2.m_foo1.m_count.set(36);             // Should NOT change since 'in-use' is marked as false
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar2.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar2.setAllInUseState(false);
    queryBar2.m_foo1.m_count.set( 111 );    // This should not get over-written on the query since it marked as not-in-use
    queryBar2.m_foo2.m_enabled.setInUse();  // Retrieve just foo2.enabled field
    queryBar2.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar2_( queryBar2, "Bar2", "Query - after update of foo2.enabled" );
    REQUIRE( queryBar2.m_foo1.m_name.getString() == "charlie" );
    REQUIRE( queryBar2.m_foo1.m_enabled.get() == false );
    REQUIRE( queryBar2.m_foo1.m_count.get() == 111 );        // Should be Query's client value -->NOT the model value (this is a mis-use case test of the 'in-use' flag on a query)
    REQUIRE( queryBar2.m_foo2.m_enabled.get() == false );
    REQUIRE( queryBar2.m_foo2.m_limit.get() == 100 );
    REQUIRE( queryBar2.m_foo2.m_enabled.isValid() == true ); // Can only check the isValid flag for the Elements that I queried for (i.e. only for foo2.m_enabled)


    // BAR3 Query
    Point::QueryBar3 queryBar3( modelBar3_ );
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar3.issueQuery();
    traceBar3_( queryBar3, "Bar3", "Query - model point in its initial state" );
    unsigned idx;
    for(idx=0; idx<4; idx++)
        {
        REQUIRE( queryBar3.isTupleInContainer(idx) == false );
        REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == false );
        REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == false );
        REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == false );
        }

    REQUIRE( queryBar3.nextItem(0) == -1 );
    idx = 0;
    unsigned j;
    for(j=0; j<4; j++)
        {
        REQUIRE( queryBar3.nextEmptyItem(j) == j );
        }

    /// FOO3 Controller 
    Point::ControllerBar3 controllerBar3( modelBar3_ );
    idx = 2;
    controllerBar3.m_tuples[idx].m_name.set("bob2");
    controllerBar3.m_tuples[idx].m_enabled.set(true);
    controllerBar3.m_tuples[idx].m_count.set(102);
    controllerBar3.m_tuples[idx].setAllValidFlagState(true);
    controllerBar3.m_tuples[idx].setAllInUseState(true);
    controllerBar3.addItem(idx);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar3.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run

    queryBar3.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar3_( queryBar3, "Bar3", "Query - after add of tuple idx: 2" );
    REQUIRE( queryBar3.isTupleInContainer(idx) == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.getString() == "bob2" );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.get() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.get() == 102 );
    REQUIRE( queryBar3.isTupleInContainer(0) == false );
    REQUIRE( queryBar3.isTupleInContainer(1) == false );
    REQUIRE( queryBar3.isTupleInContainer(3) == false );

    REQUIRE( queryBar3.nextItem(0) == idx );
    REQUIRE( queryBar3.nextItem(idx+1) == -1 );
    REQUIRE( queryBar3.nextEmptyItem(0) == 0 );
    REQUIRE( queryBar3.nextEmptyItem(1) == 1 );
    REQUIRE( queryBar3.nextEmptyItem(2) == 3 );
    REQUIRE( queryBar3.nextEmptyItem(3) == 3 );

    controllerBar3.m_tuples[idx].setAllInUseState(false);
    controllerBar3.m_tuples[idx].m_name.set("bob33");
    controllerBar3.m_tuples[idx].m_name.setInUse();
    controllerBar3.m_tuples[idx].m_count.set(1023);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar3.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run

    queryBar3.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar3_( queryBar3, "Bar3", "Query - after update to tuple.1.m_name ONLY" );
    REQUIRE( queryBar3.isTupleInContainer(idx) == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.getString() == "bob33" );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.get() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.get() == 102 );
    REQUIRE( queryBar3.isTupleInContainer(0) == false );
    REQUIRE( queryBar3.isTupleInContainer(1) == false );
    REQUIRE( queryBar3.isTupleInContainer(3) == false );


    idx = 1;
    controllerBar3.m_tuples[idx].setAllInUseState(true);
    controllerBar3.m_tuples[idx].m_name.set("bob1");
    controllerBar3.m_tuples[idx].m_enabled.set(true);
    controllerBar3.m_tuples[idx].m_count.set(101);
    controllerBar3.m_tuples[idx].setAllValidFlagState(true);
    controllerBar3.m_tuples[idx].setAllInUseState(true);
    controllerBar3.addItem(idx);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar3.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run

    queryBar3.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar3_( queryBar3, "Bar3", "Query - after add of tuple idx: 2, 1" );
    REQUIRE( queryBar3.isTupleInContainer(idx) == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.getString() == "bob1" );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.get() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.get() == 101 );
    REQUIRE( queryBar3.isTupleInContainer(0) == false );
    REQUIRE( queryBar3.isTupleInContainer(3) == false );
    idx = 2;
    REQUIRE( queryBar3.isTupleInContainer(idx) == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.getString() == "bob33" );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.get() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.get() == 102 );

    idx = 2;
    controllerBar3.removeItem(idx);
    CPL_SYSTEM_TRACE_MSG( SECT_, ("Updating Model...."));
    controllerBar3.updateModel();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    queryBar3.issueQuery();
    Cpl::System::Api::sleep(50); // Pause to allow other threads to run
    traceBar3_( queryBar3, "Bar3", "Query - after remove of tuple idx: 2" );
    REQUIRE( queryBar3.isTupleInContainer(idx) == false );
    idx = 1;
    REQUIRE( queryBar3.isTupleInContainer(idx) == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.isValid() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_name.getString() == "bob1" );
    REQUIRE( queryBar3.m_tuples[idx].m_enabled.get() == true );
    REQUIRE( queryBar3.m_tuples[idx].m_count.get() == 101 );
    REQUIRE( queryBar3.isTupleInContainer(0) == false );
    REQUIRE( queryBar3.isTupleInContainer(3) == false );


    // Stop viewers
    v1_.close();
    v2_.close();

    // Shutdown threads
    viewerMailbox_.pleaseStop();
    modelMailbox_.pleaseStop();
    Cpl::System::Api::sleep(50); // allow time for threads to stop
    REQUIRE( modelThreadPtr->isRunning() == false );
    REQUIRE( viewerThreadPtr->isRunning() == false );

    Cpl::System::Thread::destroy( *modelThreadPtr );
    Cpl::System::Thread::destroy( *viewerThreadPtr );
    REQUIRE( Cpl::System::Shutdown_TS::getAndClearCounter() == 0 );
    }
