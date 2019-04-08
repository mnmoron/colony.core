#ifndef Cpl_Rte_Mp_Uint32_h_
#define Cpl_Rte_Mp_Uint32_h_
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
/** @file */


#include "Cpl/Dm/Mp/Basic.h"

///
namespace Cpl {
///
namespace Dm {
///
namespace Mp {


/** This class provides a concrete implementation for a Point who's data is a
    uint32_t.

    The toJSON()/fromJSON format is:
        \code

        { name="<mpname>", type="<mptypestring>", invalid=nn, seqnum=nnnn, locked=true|false, val:<numvalue> }

        where <numvalue> is decimal numeric OR a quoted HEX string (when the MP
        instance was constructed with 'decimalFormat':=false).  For example:

            val:1234  or val:"4D2"

        \endcode
 
 NOTE: All methods in this class ARE thread Safe unless explicitly
          documented otherwise.
 */
class Uint32 : public BasicNumeric<uint32_t>
{
public:
    /** Constructor. Invalid MP.  Note: the 'decimalFormat' argument applies to the 
        toString()/fromString() methods.   When set to true, the input/output
        values must be decimal numbers; else hexadecimal numbers (as defined
        by standard C library strtol() function).
     */
    Uint32( Cpl::Dm::ModelDatabase& myModelBase, Cpl::Dm::StaticInfo& staticInfo, bool decimalFormat=true );

    /// Constructor. Valid MP.  Requires an initial value
    Uint32( Cpl::Dm::ModelDatabase& myModelBase, Cpl::Dm::StaticInfo& staticInfo, uint32_t initialValue, bool decimalFormat=true );

public:
    /// Type safe read. See Cpl::Dm::ModelPoint
    virtual int8_t read( uint32_t& dstData, uint16_t* seqNumPtr=0 ) const noexcept;

    /// Type safe write. See Cpl::Dm::ModelPoint
    virtual uint16_t write( uint32_t newValue, LockRequest_T lockRequest = eNO_REQUEST ) noexcept;

    /// Type safe read-modify-write client callback interface
    typedef Cpl::Dm::ModelPointRmwCallback<uint32_t> Client;

    /** Type safe read-modify-write. See Cpl::Dm::ModelPoint

       NOTE: THE USE OF THIS METHOD IS STRONGLY DISCOURAGED because it has
             potential to lockout access to the ENTIRE Model Base for an
             indeterminate amount of time.  And alternative is to have the
             concrete Model Point leaf classes provide the application
             specific read, write, read-modify-write methods in addition or in
             lieu of the read/write methods in this interface.
     */
    virtual uint16_t readModifyWrite( Client& callbackClient, LockRequest_T lockRequest = eNO_REQUEST );


public:
    /// Type safe subscriber
    typedef Cpl::Dm::Subscriber<Uint32> Observer;

    /// Type safe register observer
    virtual void attach( Observer& observer, uint16_t initialSeqNumber=SEQUENCE_NUMBER_UNKNOWN ) noexcept;

    /// Type safe un-register observer
    virtual void detach( Observer& observer ) noexcept;


public:
    ///  See Cpl::Dm::ModelPoint.
    const char* getTypeAsText() const noexcept;
};



};      // end namespaces
};
};
#endif  // end header latch
