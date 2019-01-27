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

#include "Cpl/TShell/Dac/Cmd/Bye.h"
#include "Cpl/Text/atob.h"
#include "Cpl/System/Shutdown.h"
#include <string.h>         


///
using namespace Cpl::TShell::Dac::Cmd;

///////////////////////////
Bye::Bye( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList ) throw()
:Command(commandList, "bye")
    {
    }

Bye::Bye( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList, const char* ignoreThisParameter_onlyUsedWhenCreatingAStaticInstance ) throw()
:Command(commandList, "bye", ignoreThisParameter_onlyUsedWhenCreatingAStaticInstance)
    {
    }


///////////////////////////
Cpl::TShell::Dac::Command::Result_T Bye::execute( Cpl::TShell::Dac::Context_& context, Cpl::Text::Tokenizer::TextBlock& tokens, const char* rawInputString, Cpl::Io::Output& outfd ) throw()
    {
    // Error checking
    if ( tokens.numParameters() > 3 )
        {
        return Cpl::TShell::Dac::Command::eERROR_EXTRA_ARGS;
        }

    // Bye just the command shell
    if ( tokens.numParameters() == 1 )
        {
        // Request the Command Processor to stop
        context.requestStop();
        return Cpl::TShell::Dac::Command::eSUCCESS;
        }

    // Bye the application
    if ( strcmp( tokens.getParameter(1), "app" ) == 0 )
        {
        int exitCode = OPTION_CPL_SYSTEM_SHUTDOWN_SUCCESS_ERROR_CODE;
        if ( tokens.numParameters() > 2 )
            {
            Cpl::Text::a2i( exitCode, tokens.getParameter(2) );
            }

        Cpl::System::Shutdown::failure( exitCode );
        return Cpl::TShell::Dac::Command::eSUCCESS;
        }

    // If I get here -->the argument(s) where bad
    return Cpl::TShell::Dac::Command::eERROR_INVALID_ARGS;
    }

