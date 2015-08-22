#include "Cpl/Io/Socket/Win32/Listener.h"
#include "Cpl/System/Api.h"
#include "Cpl/System/Trace.h"
#include "Cpl/TShell/Dac/Cmd/Threads.h"


// External references
extern void shell_test2( Cpl::Io::Socket::Listener& listener );
                                                

Cpl::Container::Map<Cpl::TShell::Dac::Command>  cmdlist("ignore_this_parameter-used to invoke the static constructor" );
Cpl::TShell::Dac::Cmd::Threads                  threadsCmd_( cmdlist );


int main( int argc, char* const argv[] )
{
    // Initialize Colony
    Cpl::System::Api::initialize();

    // Create socket listener
    Cpl::Io::Socket::Win32::Listener  listener;

    CPL_SYSTEM_TRACE_ENABLE();
    CPL_SYSTEM_TRACE_ENABLE_SECTION("_0test");
    CPL_SYSTEM_TRACE_SET_INFO_LEVEL( Cpl::System::Trace::eINFO );

	// Run the test
    shell_test2( listener );

    // do not exit
    for(;;)
        {
        Cpl::System::Api::sleep(1000);
        }

	return 0;
}
