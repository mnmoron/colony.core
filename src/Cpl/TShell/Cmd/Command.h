#ifndef Cpl_TShell_Cmd_Command_h_
#define Cpl_TShell_Cmd_Command_h_
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
#include "Cpl/TShell/Command.h"
#include "Cpl/TShell/Context_.h"
#include "Cpl/Container/Map.h"
#include "Cpl/Text/String.h"


///
namespace Cpl {
///
namespace TShell {
///
namespace Cmd {

/** This partially concrete class implements infrastructure and/or common
	functionality for a  Shell command.
 */
class Command : public Cpl::TShell::Command
{
protected:
	/// Result when processing a conditional statement
	enum CondResult_T {
		eFALSE, //!< The conditional statement evaluated to false
		eTRUE,  //!< The conditional statement evaluated to true
		eERROR  //!< Error occurring during the evaluation of the conditional
	};

protected:
	/// Command 
	Cpl::Container::KeyLiteralString  m_mapKey;


protected:
	/// Constructor
	Command( Cpl::Container::Map<Cpl::TShell::Command>& commandList, const char* verb ) noexcept;


public:
	/// See Cpl::TShell::Command
	const char* getVerb() const noexcept;


protected:
	/// See Cpl::Container::Key
	const Cpl::Container::Key& getKey() const noexcept;

};

};      // end namespaces
};
};
#endif  // end header latch
