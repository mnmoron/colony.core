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

#include "CloseSync.h"
#include "SyncReturnHandler.h"

///
using namespace Cpl::Itc;


///////////////////
CloseSync::CloseSync(PostApi& myMbox)
:OpenSync(myMbox)
    {
    }


///////////////////
void CloseSync::close( void )
    {
	ClosePayload        payload;
    SyncReturnHandler   srh;
    CloseMsg 	        msg(*this,payload,srh);
    m_mbox.postSync(msg);
    }
