#include "Cpl/System/Api.h"
#include "Cpl/System/Trace.h"
#include "Cpl/Io/Socket/Posix/Listener.h"
#include "Cpl/Io/Socket/Posix/Connector.h"
#include "Cpl/Io/Socket/_0test/loopback.h"



#define CATCH_CONFIG_RUNNER  
#include "Catch/catch.hpp"


int main( int argc, char* const argv[] )
    {
    // Initialize Colony
    Cpl::System::Api::initialize();
    Cpl::System::Api::enableScheduling();

    // Platform specific listener
    Cpl::Io::Socket::Posix::Listener  listener;
    Cpl::Io::Socket::Posix::Connector connector;
    initialize_loopback( listener, connector );

    CPL_SYSTEM_TRACE_ENABLE();
    CPL_SYSTEM_TRACE_ENABLE_SECTION("_0test");
    CPL_SYSTEM_TRACE_SET_INFO_LEVEL( Cpl::System::Trace::eINFO );

    // THIS CODE DOES NOTHING.  It is needed to force the inclusion of
    // the test code due to the combination of how CATCH auto registers
    // test cases and how NQBP links by libraries.  Short version is do NOT
    // remove these call(s).

    // Run the test(s)
    int result = Catch::Session().run( argc, argv );
    return result;
    }

