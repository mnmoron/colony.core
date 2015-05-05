#ifndef Cpl_TShell_Dac_Cmd_Help_h
#define Cpl_TShell_Dac_Cmd_Help_h
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

#include "Cpl/TShell/Dac/Cmd/Command_.h"


/* RULER
                                    "         1         2         3         4         5         6         7         8"
                                    "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
*/
#define CPLTSHELLDACMD_USAGE_HELP_  "help [full]"
#define CPLTSHELLDACMD_DETAIL_HELP_ "  Displays list of all supported commands and optionally their detailed help."


///
namespace Cpl { namespace TShell { namespace Dac { namespace Cmd {



/** This class implements a DAC Shell command
 */
class Help: public Command_
{
public:
    /// See Cpl::TShell::Dac::Command_
    const char* getUsage() const throw()    { return CPLTSHELLDACMD_USAGE_HELP_; }

    /// See Cpl::TShell::Dac::Command_
    const char* getHelp() const throw()     { return CPLTSHELLDACMD_DETAIL_HELP_; }
    
     
public:
    /// Constructor
    Help( Cpl::Container::Map<Cpl::TShell::Dac::Command_>& commandList ) throw();


public:
    /// See Cpl::TShell::Dac::Command_
    Cpl::TShell::Dac::Command_::Result_T execute( Cpl::TShell::Dac::Context_& context, Cpl::Text::Tokenizer::TextBlock& tokens, const char* rawInputString, Cpl::Io::Output& outfd ) throw();

};

};      // end namespaces
};
};
};
#endif  // end header latch
