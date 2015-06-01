#ifndef Cpl_TShell_Dac_Maker_h_
#define Cpl_TShell_Dac_Maker_h_
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

#include "Cpl/TShell/Dac/Processor.h"
#include "Cpl/TShell/Dac/NullVariables.h"
#include "Cpl/Text/Frame/LineDecoder.h"
#include "Cpl/System/Private_.h"

///
namespace Cpl { namespace TShell { namespace Dac {


/** This concrete class is a "Maker" that assembles the objects needed
    for a 'basic' DAC Shell Processor engine. 
 */
class Maker
{
protected:    
    /// Shell variables
    NullVariables                   m_variables;

    /// Framer for the output
    Cpl::Text::Frame::StreamEncoder m_framer;

    /// Deframer for the input stream
    Cpl::Text::Frame::LineDecoder<OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE> m_deframer; 

    /// Command Processor
    Processor                       m_processor;


public:
    /** Constructor.  The application is responsible for supplying the set of commands and the mutex to ensure atomic
        output.
     */
    Maker( Cpl::Container::Map<Cpl::TShell::Dac::Command>& cmdlist, Cpl::System::Mutex& lock=Cpl::System::Locks_::tracing() );

         


public:
    /// Returns a reference to the Command processor
    Processor& getCommandProcessor(void) throw() { return m_processor; }

    /// Cast-operator: Short-hand for getCommandProcessor()
    operator Processor& ()                       { return m_processor; }

};




};      // end namespaces
};
};
#endif  // end header latch