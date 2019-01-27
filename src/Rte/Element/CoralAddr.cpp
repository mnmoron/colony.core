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

#include "CoralAddr.h"


///
using namespace Rte::Element;


//////////////////////////////////
CoralAddr::CoralAddr( const char*  initialValue,
                      bool         inUse,
                      int8_t       validState
                    )
//:Rte::Element::String<OPTION_CORAL_SZ_ADDRESS>(DataType::CORAL_ADDR,initialValue,inUse,validState)
:Rte::Element::String<10>(DataType::CORAL_ADDR,initialValue,inUse,validState)
    {
    }

const char* CoralAddr::getTypeAsText(void) const
    {
    return "CORAL_ADDR";
    }





