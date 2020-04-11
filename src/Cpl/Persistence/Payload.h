#ifndef Cpl_Persistence_Payload_h_
#define Cpl_Persistence_Payload_h_
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


#include <stdlib.h>


///
namespace Cpl {
///
namespace Persistence {


/** This abstract class defines the interface accessing the 'data payload' of
    an individual Record instance.
 */
class Payload
{
public:
    /** This method returns a Record's data payload contents.  The Record
        is responsible for NOT over-running the 'dst' buffer.  The method
        returns the number of bytes copied to 'dst'.  
        
        Note: If the Record returns less data than 'maxDstLen' - the remaining
              bytes will be zero filled before the record data is written to
              the media.
     */
    virtual size_t getData( void* dst, size_t maxDstLen ) noexcept = 0;

    /** This method us to transfer persistently stored data into a Record.  
     */
    virtual void putData( const void* src, size_t srcLen ) noexcept = 0;


public:
    /// Virtual destructor
    virtual ~Payload() {}
};


};      // end namespaces
};
#endif  // end header latch
