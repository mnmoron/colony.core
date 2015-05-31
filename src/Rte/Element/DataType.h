#ifndef Rte_Element_DataType_h_
#define Rte_Element_DataType_h_
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


///
namespace Rte { namespace Element {

/** This class defines the data type constants for the different
    element types.  The domain application can add its own data type
    by defining a series of integer constant that their starting value
    is START_APP_DEFINED. 
 */
class DataType
{
public:
    /// My Type Id
    const int m_dataTypeId;

public:
    /// Element Type ID
    static const int INTEGER8   = 1;

    /// Element Type ID
    static const int INTEGER16  = 2;

    /// Element Type ID
    static const int INTEGER32  = 3;

    /// Element Type ID
    static const int INTEGER64  = 4;

    /// Element Type ID
    static const int UINTEGER8  = 5;

    /// Element Type ID
    static const int UINTEGER16 = 6;

    /// Element Type ID
    static const int UINTEGER32 = 7;

    /// Element Type ID
    static const int UINTEGER64 = 8;

    /// Element Type ID
    static const int SIZE_T     = 9;

    /// Element Type ID
    static const int REAL32     = 10;

    /// Element Type ID
    static const int REAL64     = 11;

    /// Element Type ID
    static const int STRING     = 12;

    /// Element Type ID
    static const int BOOLEAN    = 13;

    /// Element Type ID
    static const int TOKEN4     = 14;

    /// Element Type ID
    static const int MD5        = 15;

    /// Element Type ID
    static const int SEQNUMBER  = 16;

    /// Element Type ID
    static const int TIMET      = 17;

    /// Element Type ID
    static const int BITFLAGS   = 18;

    /// Element Type ID 
    static const int CORAL_ADDR = 19;


    /// Start of APPLICATION defined Element Type IDs
    static const int START_APP_DEFINED = 0x8000;            



public:
    /// Constructor
    DataType( int dataTypeId ):m_dataTypeId(dataTypeId)
        {
        }
    
public:
    ///
    inline bool isNotEqual( DataType x ) const 
        { 
        return m_dataTypeId != x.m_dataTypeId; 
        }

};

};      // end namespaces
};
#endif  // end header latch
