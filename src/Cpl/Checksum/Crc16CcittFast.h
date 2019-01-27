#ifndef Cpl_Checksum_Crc16CcittFast_h_
#define Cpl_Checksum_Crc16CcittFast_h_
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

#include "Cpl/Checksum/Api16.h"



///
namespace Cpl { namespace Checksum {


/** This class provides an implementation for the 16 Bit CRC-CCITT
    standard.  The CRC has following characteristics (aka CRC-CCITT(0xFFFF):
        o The poloynomal is x16 + x12 + x5 + 1
        o The Data bytes are NOT refelected
        o The remainder is NOT reflected.
        o The final remainder is NOT XOR'd
 */

class Crc16CcittFast: public Api16
{
private:
    /// Calcualted CRC value
    uint16_t    m_crc;


public:
    /// Constructor
    Crc16CcittFast() throw();


public:
    /// See Cpl::Checksum::Ap16
    void reset(void) throw();

    /// See Cpl::Checksum::Ap16
    void accumulate( void* bytes, unsigned numbytes=1 ) throw();

    /// See Cpl::Checksum::Ap16
    uint16_t finalize( void* destBuffer=0 ) throw();

    /// See Cpl::Checksum::Ap16
    bool isOkay(void) throw();
};


};      // end namespaces
};
#endif  // end header latch

