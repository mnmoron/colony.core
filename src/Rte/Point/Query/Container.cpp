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

#include "Container.h"


///
using namespace Rte::Point::Query;


///////////////////
Container::Container( Rte::Point::ContainerApi&                 myPoint, 
                      Rte::Point::Model::Api&                   modelPoint,  
                      Rte::Point::Model::QueryRequest::Option_T copyOption
                    )
:m_myPoint(myPoint)
,m_modelPoint(modelPoint)
,m_copyOption(copyOption)
    {
    m_myPoint.setAllInUseState(true);
    }


///////////////////
void Container::issueQuery( void )
    {
    // issue the query
    m_modelPoint.query( m_myPoint, m_copyOption );
    }

