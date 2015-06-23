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

#include "Token4.h"


///
using namespace Rte::Element;

//////////////////////////////////
Rte::Element::Token4::Token4( const char*  initialValue,
                              bool         inUse,
                              int8_t       validFlag
                            )
:Rte::Element::String<4>(Rte::Element::DataType::TOKEN4,initialValue,inUse,validFlag)
    {
    }



