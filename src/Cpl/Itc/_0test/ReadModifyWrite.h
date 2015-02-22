#ifndef ReadModifyWrite_h_
#define ReadModifyWrite_h_
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


/** This abstact class define a interface that allows a client to perform
    a read-modify-write operation on the server's (aka model) data.
 */
class ReadModifyWrite
{
public:
    /// Read the data
    virtual int get(void) throw() = 0;

    /// Write the data
    virtual void write(int newValue) throw() = 0;


public:
    /// Virtual destructor
    virtual ~ReadModifyWrite() {}
};

#endif  // end header latch
