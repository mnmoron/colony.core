#ifndef Cpl_Rte_ModelPointBase_h_
#define Cpl_Rte_ModelPointBase_h_
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
/** @file */


#include "Cpl/Rte/ModelPoint.h"
#include "Cpl/Rte/ModelDatabase.h"
#include "Cpl/Rte/SubscriberApi.h"
#include "Cpl/Container/DList.h"
#include <stdint.h>


///
namespace Cpl {
///
namespace Rte {


/** This concrete class provide common infrastructure for a Model Point.
 */
class ModelPointCommon : public ModelPoint
{
protected:
    /// List of Active Subscribers
    Cpl::Container::DList<SubscriberApi>    m_subscribers;

    /// Pointer to the Model Point's static information
    const StaticInfo*                       m_staticInfo;

    /// Reference to the containing Model Base
    ModelDatabase&                          m_modelDatabase;

    /// Reference to my Data
    void*                                   m_dataPtr;

    /// Sequence number used for tracking changes in the Point data
    uint16_t                                m_seqNum;

    /// Locked state
    bool                                    m_locked;

    /// Internal valid/invalid state
    int8_t                                  m_validState;


protected:
    /// Constructor
    ModelPointCommon( ModelDatabase& myModelBase, void* myDataPtr, StaticInfo* staticInfo, int8_t validState = OPTION_CPL_RTE_MODEL_POINT_STATE_INVALID );

public:
    /// See Cpl::Rte::ModelPoint
    const char* getName() const throw();

    /// See Cpl::Rte::ModelPoint
    uint16_t getSequenceNumber() const throw();

    /// See Cpl::Rte::ModelPoint
    uint16_t touch() throw();

    /// See Cpl::Rte::ModelPoint
    uint16_t setInvalidState( int8_t newInvalidState ) throw();
    
    /// See Cpl::Rte::ModelPoint
    int8_t getValidState( void ) const throw();

    /// See Cpl::Rte::ModelPoint
    bool isLocked() const throw();

    /// See Cpl::Rte::ModelPoint
    void removeLock() throw();


protected:
    /// See Cpl::Rte::ModelPoint
    uint16_t read( void* dstData, size_t dstSize, int8_t& validState ) const throw();

    /// See Cpl::Rte::ModelPoint
    uint16_t write( const void* srcData, LockRequest_T lockRequest = eNO_REQUEST  ) throw();

    /// See Cpl::Rte::ModelPoint
    uint16_t readModifyWrite( GenericRmwCallback& callbackClient, LockRequest_T lockRequest = eNO_REQUEST  );

    /// See Cpl::Rte::ModelPoint
    void attach( SubscriberApi& observer, uint16_t initialSeqNumber=SEQUENCE_NUMBER_UNKNOWN ) throw();

    /// See Cpl::Rte::ModelPoint 
    void detach( SubscriberApi& observer ) throw();

    /// See Cpl::Rte::ModelPoint 
    size_t export(void* dstDataStream, uint16_t* retSequenceNumber = 0 ) const throw();

    /// See Cpl::Rte::ModelPoint 
    size_t import( const void* srcDataStream, uint16_t* retSequenceNumber = 0 ) throw();

    /// See Cpl::Rte::ModelPoint 
    size_t getExternalSize() const throw();


public:
    /// See Cpl::Container::Key
    int compareKey( const Key& key ) const;

    /// See Cpl::Container::Key
    const void* getRawKey( unsigned* returnRawKeyLenPtr = 0 ) const;


public:
    /// See Cpl::Rte::ModelPoint
    void processSubscriptionEvent_( SubscriberApi& subscriber, Event_T event ) throw();


protected:
    /** Internal helper method that completes the data update process as well
        as ensuring any change notifications get generated.  Note: This method
        ALWAYS sets the MP's state to 'valid'

        This method is NOT thread safe.
     */
    void processDataUpdated() throw();

    /** Internal helper method that handles generating change notifications
        when the Model Point's data/state has changed.

        This method is NOT thread safe.
     */
    void processChangeNotifications() throw();

    /** Internal helper method that manages testing and updating the locked
        state.
        
        Rules:
        1) If 'lockRequest' is eNO_REQUEST, the method only returns true if
           the MP is in the unlocked state
        2) If 'lockRequest' is eLOCK, the method only returns if the MP is in
           the unlocked state.  In addition, when true is returned the MP is
           put into the locked state.
        3) If 'lockRequest' is eUNLOCK, the method always returns true and
           the MP is left in the unlocked state.

        This method is NOT thread safe.
     */
    bool testAndUpdateLock( LockRequest_T lockRequest ) throw();




protected:

    /// Helper FSM method
    void transitionToNotifyPending( SubscriberApi& subscriber ) throw();

    /// Helper FSM method
    void transitionToSubscribed( SubscriberApi& subscriber ) throw();

};

};      // end namespaces
};
#endif  // end header latch
