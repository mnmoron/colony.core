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

#include "Text.h"

using namespace Rte::Point::Query;


///////////////////
Text::Text( Cpl::Text::String&       storageForResults,
            Rte::Point::Model::Api&  modelPoint,
            int                      tupleIndex 
            )
:m_results(storageForResults)
,m_modelPoint(modelPoint)
,m_tupleIdx(tupleIndex)
    {
    }


///////////////////
bool Text::issueQuery( void )
    {
    // issue the query
    return m_modelPoint.query(m_results, m_tupleIdx);
    }
