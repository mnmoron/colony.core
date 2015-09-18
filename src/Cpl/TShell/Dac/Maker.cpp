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

#include "Maker.h"

///
using namespace Cpl::TShell::Dac;


////////////////////////////////
Maker::Maker( Cpl::Container::Map<Cpl::TShell::Dac::Command>& cmdlist, Cpl::System::Mutex& lock )
:m_variables()
,m_framer( 0, '\0', '\n', '\0', false )
,m_deframer( 0, ' ' )
,m_processor( cmdlist, m_variables, m_deframer, m_framer, lock, 0, 0 ) 
    {
    }


