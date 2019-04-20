#ifndef Cpl_Dm_TShell_Dac_Dm_h
#define Cpl_Dm_TShell_Dac_Dm_h
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
/** @file */

#include "colony_config.h"
#include "Cpl/TShell/Dac/Cmd/Command.h"
#include "Cpl/Dm/ModelDatabaseApi.h"



/** Usage
										"         1         2         3         4         5         6         7         8"
										"12345678901234567890123456789012345678901234567890123456789012345678901234567890"
*/
#define CPLDMTSHELLDAC_USAGE_DM_		"dmN ls [<filter>]\n" \
                                        "dmN write {<mp-json>}\n" \
                                        "dmN read <mpname>\n" 

/// Detailed Help text
#ifndef CPLDMTSHELLDAC_DETAIL_DM_
#define CPLDMTSHELLDAC_DETAIL_DM_       "  Lists, updates, and displays Model Points contained in Model Database 'N'.\n" \
										"  When 'ls' is used a list of model point names is returned.  The <filter>\n" \
										"  argument will only list points that contain <filter>.  Updating a Model Point\n" \
										"  is done by specifing a JSON object. See the concrete class definition of the\n" \
										"  Model Point being updated for the JSON format.  When displaying a Model Point\n" \
										"  <mpname> is the string name of the Model Point instance to be displayed."

#endif // ifndef allows detailed help to be compacted down to a single character if FLASH/code space is an issue



///
namespace Cpl {
///
namespace Dm {
///
namespace TShell {
///
namespace Dac {



/** This class implements a DAC Shell command.  Note: Up to 10 different
	instance of this command can be instantiated - but each instance MUST
	have a different database number.  The database number specified by
	specifying the actual command name, e.g. 'dm0' is database number 0,
	'dm1' is database number 1, etc.
 */
class Dm : public Cpl::TShell::Dac::Command
{
protected:
	/// Model Point Database to access
	Cpl::Dm::ModelDatabaseApi& m_database;

	/// Dynamic 
public:
	/// See Cpl::TShell::Dac::Command                                                               `
	const char* getUsage() const noexcept { return CPLDMTSHELLDAC_USAGE_DM_; }

	/// See Cpl::TShell::Dac::Command
	const char* getHelp() const noexcept { return CPLDMTSHELLDAC_DETAIL_DM_; }


public:
	/// Constructor
	Dm( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList, Cpl::Dm::ModelDatabaseApi& modelDatabase, const char* cmdNameAndDatabaseNumber = "dm0" ) noexcept;

	/// Constructor.  Used to create a static instance of the command
	Dm( Cpl::Container::Map<Cpl::TShell::Dac::Command>& commandList, Cpl::Dm::ModelDatabaseApi& modelDatabase, const char* ignoreThisParameter_onlyUsedWhenCreatingAStaticInstance, const char* cmdNameAndDatabaseNumber = "dm0" ) noexcept;


public:
	/// See Cpl::TShell::Dac::Command
	Cpl::TShell::Dac::Command::Result_T execute( Cpl::TShell::Dac::Context_& context, Cpl::Text::Tokenizer::TextBlock& tokens, Cpl::Io::Output& outfd ) noexcept;

};

};      // end namespaces
};
};
};
#endif  // end header latch
