#ifndef Cpl_Rte_Persistence_Chunk_Null_h_
#define Cpl_Rte_Persistence_Chunk_Null_h_
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


#include "Cpl/Dm/Persistence/Chunk/Media.h"
#include "Cpl/Io/File/Null.h"


///
namespace Cpl {
namespace Dm {
namespace Persistence {
namespace Chunk {


/** This concrete class implements the Media interface using a 'Null File'.
    The typical use case for this class is as a 'stub' for when the platform's
    actual persistent storage driver/class/file-interface has not been
    implemented.
 */
class Null : public Media, public Cpl::Io::File::Null
{
public:
    /// Constructor
    Null();


public:
    /// See Dm::Db::Chunk::Media
    Cpl::Io::File::InputOutputApi* openFile( bool& newfile ) noexcept;

    /// See Dm::Db::Chunk::Media
    void closeFile() noexcept;

    /// See Dm::Db::Chunk::Media
    bool deleteFile() noexcept;

};


};      // end namespaces
};
};
};
#endif  // end header latch
