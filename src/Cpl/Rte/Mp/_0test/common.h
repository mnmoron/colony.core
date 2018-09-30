#ifndef common_h_
#define common_h_
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

#include "Cpl/Rte/MailboxServer.h"
#include "Cpl/Rte/SubscriberComposer.h"
#include "Cpl/Rte/RmwComposer.h"
#include "Cpl/Itc/CloseSync.h"
#include "Cpl/System/Thread.h"
#include "Cpl/System/Trace.h"
#include "Cpl/Itc/CloseSync.h"
#include "Cpl/Timer/Local.h"
#include "Cpl/Rte/Mp/Int32.h"
#include "Cpl/Rte/Mp/Uint64.h"
#include "Cpl/Rte/Mp/Int64.h"
#include "Cpl/Rte/Mp/Bool.h"

/// 
using namespace Cpl::Rte;

#define SECT_   "_0test"


/////////////////////////////////////////////////////////////////
class ViewerBase : public Cpl::Itc::CloseSync
{
public:
    ///
    volatile bool                       m_opened;
    ///
    Cpl::System::Thread&                m_masterThread;
    ///
    Cpl::Itc::OpenRequest::OpenMsg*     m_pendingOpenMsgPtr;
    ///
    uint16_t                            m_lastSeqNumber;
    ///
    int8_t                              m_lastValidState;
    ///
    bool                                m_done;
    ///
    uint32_t                            m_notif_count;

    /// Constructor
    ViewerBase( MailboxServer& myMbox, Cpl::System::Thread& masterThread )
        :Cpl::Itc::CloseSync( myMbox )
        , m_opened( false )
        , m_masterThread( masterThread )
        , m_pendingOpenMsgPtr( 0 )
        , m_lastSeqNumber( ModelPoint::SEQUENCE_NUMBER_UNKNOWN )
        , m_lastValidState( OPTION_CPL_RTE_MODEL_POINT_STATE_INVALID )
        , m_done( false )
        , m_notif_count( 0 )
    {
    }

public:
    ///
    virtual void subscribe() = 0;
    ///
    virtual void unsubscribe() = 0;
    ///
    void request( Cpl::Itc::OpenRequest::OpenMsg& msg )
    {
        if ( m_opened )
        {
            FAIL( "OPENING ViewerBase more than ONCE" );
        }

        m_notif_count       = 0;
        m_done              = false;
        m_pendingOpenMsgPtr = &msg;
        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerBase::SUBSCRIBING (%p) for Change notification.", this) );

        // Subscribe to my model point
        subscribe();

        // Note: The open message will be returned once all the model point receives its initial callback
    }

    ///
    void request( Cpl::Itc::CloseRequest::CloseMsg& msg )
    {
        if ( !m_opened )
        {
            FAIL( "CLOSING ViewerBase more than ONCE" );
        }

        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerBase(%p): Closing... ", this) );

        // Un-subscribe to my model point
        unsubscribe();
        m_opened = false;
        msg.returnToSender();
    }
};

/////////////////////////////////////////////////////////////////
class ViewerInt32 : public ViewerBase, public Mp::Int32::Observer
{
public:
    ///
    Mp::Int32&  m_mp1;

    /// Constructor
    ViewerInt32( MailboxServer& myMbox, Cpl::System::Thread& masterThread, Mp::Int32& mp1 )
        :ViewerBase( myMbox, masterThread )
        , Mp::Int32::Observer( myMbox )
        , m_mp1( mp1 )
    {
        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerInt32(%p). mp1=%s", this, mp1.getName()) );
    }

public:
    ///
    void subscribe() { m_mp1.attach( *this ); }
    ///
    void unsubscribe() { m_mp1.detach( *this ); }
    ///
    void modelPointChanged( Mp::Int32& modelPointThatChanged ) throw()
    {
        if ( m_done != true )
        {
            m_notif_count++;
            CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerInt32(%p) Changed!: count=%lu", this, (unsigned long) m_notif_count) );

            m_lastSeqNumber  = modelPointThatChanged.getSequenceNumber();
            m_lastValidState = modelPointThatChanged.getValidState();

            if ( m_pendingOpenMsgPtr != 0 && m_notif_count == 1 )
            {
                m_pendingOpenMsgPtr->returnToSender();
                m_opened            = true;
                m_pendingOpenMsgPtr = 0;
                CPL_SYSTEM_TRACE_MSG( SECT_, ("..ViewerInt32(%p) Returning Open Msg.") );
            }

            if ( m_notif_count >= 2 )
            {
                m_masterThread.signal();
                m_done = true;
            }
        }
    }
};

class RmwInt32 : public Mp::Int32::Client
{
public:
    ///
    int m_callbackCount;
    ///
    ModelPoint::RmwCallbackResult_T m_returnResult;
    ///
    int32_t                         m_incValue;

public:
    ///
    RmwInt32():m_callbackCount( 0 ), m_returnResult( ModelPoint::eNO_CHANGE ), m_incValue( 0 ) {}
    ///
    ModelPoint::RmwCallbackResult_T callback( int32_t& data, int8_t validState ) throw()
    {
        m_callbackCount++;
        if ( m_returnResult != ModelPoint::eNO_CHANGE )
        {
            data += m_incValue;
        }
        return m_returnResult;
    }
};

/////////////////////////////////////////////////////////////////
class ViewerInt64 : public ViewerBase, public Mp::Int64::Observer
{
public:
    ///
    Mp::Int64&  m_mp1;

    /// Constructor
    ViewerInt64( MailboxServer& myMbox, Cpl::System::Thread& masterThread, Mp::Int64& mp1 )
        :ViewerBase( myMbox, masterThread )
        , Mp::Int64::Observer( myMbox )
        , m_mp1( mp1 )
    {
        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerInt64(%p). mp1=%s", this, mp1.getName()) );
    }

public:
    ///
    void subscribe() { m_mp1.attach( *this ); }
    ///
    void unsubscribe() { m_mp1.detach( *this ); }
    ///
    void modelPointChanged( Mp::Int64& modelPointThatChanged ) throw()
    {
        if ( m_done != true )
        {
            m_notif_count++;
            CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerInt64(%p) Changed!: count=%lu", this, (unsigned long) m_notif_count) );

            m_lastSeqNumber  = modelPointThatChanged.getSequenceNumber();
            m_lastValidState = modelPointThatChanged.getValidState();

            if ( m_pendingOpenMsgPtr != 0 && m_notif_count == 1 )
            {
                m_pendingOpenMsgPtr->returnToSender();
                m_opened            = true;
                m_pendingOpenMsgPtr = 0;
                CPL_SYSTEM_TRACE_MSG( SECT_, ("..ViewerInt64(%p) Returning Open Msg.") );
            }

            if ( m_notif_count >= 2 )
            {
                m_masterThread.signal();
                m_done = true;
            }
        }
    }
};

class RmwInt64 : public Mp::Int64::Client
{
public:
    ///
    int m_callbackCount;
    ///
    ModelPoint::RmwCallbackResult_T m_returnResult;
    ///
    int64_t                         m_incValue;

public:
    ///
    RmwInt64():m_callbackCount( 0 ), m_returnResult( ModelPoint::eNO_CHANGE ), m_incValue( 0 ) {}
    ///
    ModelPoint::RmwCallbackResult_T callback( int64_t& data, int8_t validState ) throw()
    {
        m_callbackCount++;
        if ( m_returnResult != ModelPoint::eNO_CHANGE )
        {
            data += m_incValue;
        }
        return m_returnResult;
    }
};

/////////////////////////////////////////////////////////////////
class ViewerUint64 : public ViewerBase, public Mp::Uint64::Observer
{
public:
    ///
    Mp::Uint64&  m_mp1;

    /// Constructor
    ViewerUint64( MailboxServer& myMbox, Cpl::System::Thread& masterThread, Mp::Uint64& mp1 )
        :ViewerBase( myMbox, masterThread )
        , Mp::Uint64::Observer( myMbox )
        , m_mp1( mp1 )
    {
        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerUint64(%p). mp1=%s", this, mp1.getName()) );
    }

public:
    ///
    void subscribe() { m_mp1.attach( *this ); }
    ///
    void unsubscribe() { m_mp1.detach( *this ); }
    ///
    void modelPointChanged( Mp::Uint64& modelPointThatChanged ) throw()
    {
        if ( m_done != true )
        {
            m_notif_count++;
            CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerUint64(%p) Changed!: count=%lu", this, (unsigned long) m_notif_count) );

            m_lastSeqNumber  = modelPointThatChanged.getSequenceNumber();
            m_lastValidState = modelPointThatChanged.getValidState();

            if ( m_pendingOpenMsgPtr != 0 && m_notif_count == 1 )
            {
                m_pendingOpenMsgPtr->returnToSender();
                m_opened            = true;
                m_pendingOpenMsgPtr = 0;
                CPL_SYSTEM_TRACE_MSG( SECT_, ("..ViewerUint64(%p) Returning Open Msg.") );
            }

            if ( m_notif_count >= 2 )
            {
                m_masterThread.signal();
                m_done = true;
            }
        }
    }
};

class RmwUint64 : public Mp::Uint64::Client
{
public:
    ///
    int m_callbackCount;
    ///
    ModelPoint::RmwCallbackResult_T m_returnResult;
    ///
    uint64_t                        m_incValue;

public:
    ///
    RmwUint64():m_callbackCount( 0 ), m_returnResult( ModelPoint::eNO_CHANGE ), m_incValue( 0 ) {}
    ///
    ModelPoint::RmwCallbackResult_T callback( uint64_t& data, int8_t validState ) throw()
    {
        m_callbackCount++;
        if ( m_returnResult != ModelPoint::eNO_CHANGE )
        {
            data += m_incValue;
        }
        return m_returnResult;
    }
};

/////////////////////////////////////////////////////////////////
class ViewerBool : public ViewerBase, public Mp::Bool::Observer
{
public:
    ///
    Mp::Bool&  m_mp1;

    /// Constructor
    ViewerBool( MailboxServer& myMbox, Cpl::System::Thread& masterThread, Mp::Bool& mp1 )
        :ViewerBase( myMbox, masterThread )
        , Mp::Bool::Observer( myMbox )
        , m_mp1( mp1 )
    {
        CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerBool(%p). mp1=%s", this, mp1.getName()) );
    }

public:
    ///
    void subscribe() { m_mp1.attach( *this ); }
    ///
    void unsubscribe() { m_mp1.detach( *this ); }
    ///
    void modelPointChanged( Mp::Bool& modelPointThatChanged ) throw()
    {
        if ( m_done != true )
        {
            m_notif_count++;
            CPL_SYSTEM_TRACE_MSG( SECT_, ("ViewerBool(%p) Changed!: count=%lu", this, (unsigned long) m_notif_count) );

            m_lastSeqNumber  = modelPointThatChanged.getSequenceNumber();
            m_lastValidState = modelPointThatChanged.getValidState();

            if ( m_pendingOpenMsgPtr != 0 && m_notif_count == 1 )
            {
                m_pendingOpenMsgPtr->returnToSender();
                m_opened            = true;
                m_pendingOpenMsgPtr = 0;
                CPL_SYSTEM_TRACE_MSG( SECT_, ("..ViewerBool(%p) Returning Open Msg.") );
            }

            if ( m_notif_count >= 2 )
            {
                m_masterThread.signal();
                m_done = true;
            }
        }
    }
};

class RmwBool : public Mp::Bool::Client
{
public:
    ///
    int m_callbackCount;
    ///
    ModelPoint::RmwCallbackResult_T m_returnResult;
    ///
    bool                            m_nextValue;

public:
    ///
    RmwBool():m_callbackCount( 0 ), m_returnResult( ModelPoint::eNO_CHANGE ), m_nextValue( true ) {}
    ///
    ModelPoint::RmwCallbackResult_T callback( bool& data, int8_t validState ) throw()
    {
        m_callbackCount++;
        if ( m_returnResult != ModelPoint::eNO_CHANGE )
        {
            data = m_nextValue;
        }
        return m_returnResult;
    }
};

#endif