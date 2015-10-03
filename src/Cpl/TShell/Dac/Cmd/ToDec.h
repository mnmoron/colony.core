#ifndef Cpl_TShell_Dac_Cmd_ToDec_h
#define Cpl_TShell_Dac_Cmd_ToDec_h
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

#include "colony_config.h"
#include "Cpl/TShell/Dac/Cmd/Command.h"


/** Usage
                                         "         1         2         3         4         5         6         7         8"
                                         "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
*/
#define CPLTSHELLDACMD_USAGE_TONUM_      "todec <etext> <var> [<base>]"

/// Detailed Help text
#ifndef CPLTSHELLDACMD_DETAIL_TONUM_
#define CPLTSHELLDACMD_DETAIL_TONUM_     "  Converts the assumed unsigned hexidecimal value <etext> to a numeric decimal\n" \
                                         "  value and stores the result in <var>. An optional <base> argument can be\n" \
                                         "  provide to perform conversations other than base 16. see Set command for\n" \
                                         "  additional details about 'etext' arugments."

#endif // ifndef allows detailed help to be compacted down to a single character if FLASH/code space is an issue



///
namespace Cpl { namespace TShell { namespace Dac { namespace Cmd {



/** This class implements a DAC Shell command
 */
class ToDec: public Command
{
public:
    /// See Cpl::TShell::Dac::Command
    const char* getUsage() const throw()    { return CPLTSHELLDACMD_USAGE_TONUM_; }

    /// See Cpl::TShell::Dac::Command
    const char* getHelp() const throw()     { return CPLTSHELLDACMD_DETAIL_TONUM_; }
    
     
public:
    /// Constructor
    ToDec( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList ) throw();

    /// Constructor.  Used to create a static instance of the command
    ToDec( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList, const char* ignoreThisParameter_onlyUsedWhenCreatingAStaticInstance ) throw();


public:
    /// See Cpl::TShell::Dac::Command
    Cpl::TShell::Dac::Command::Result_T execute( Cpl::TShell::Dac::Context_& context, Cpl::Text::Tokenizer::TextBlock& tokens, const char* rawInputString, Cpl::Io::Output& outfd ) throw();

};

};      // end namespaces
};
};
};
#endif  // end header latch
