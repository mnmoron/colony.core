#include "Cpl/System/Api.h"
#include "Cpl/System/Shutdown.h"
#include "Cpl/Memory/_testsupport/New_TS.h"
#include "Cpl/System/_testsupport/Shutdown_TS.h"


#define CATCH_CONFIG_RUNNER  
#include "Catch/catch.hpp"

// External references
extern void link_fstring(void);
extern void link_dstring(void);
extern void link_dfstring(void);
extern void link_string(void);
extern void link_strip(void);
extern void link_atob(void);
extern void link_format(void);
extern void link_stringItem(void);


int main( int argc, char* const argv[] )
{
    // Initialize Colony
    Cpl::System::Api::initialize();

    // THIS CODE DOES NOTHING.  It is needed to force the inclusion of
    // the test code due to the combination of how CATCH auto registers
    // test cases and how NQBP links by libraries.  Short version is do NOT
    // remove these call(s).
    link_fstring();
    link_dstring();
    link_dfstring();
    link_string();
    link_strip();
    link_atob();
    link_format();
    link_stringItem();

	// Expect EQUAL new/delete calls
    Cpl::Memory::New_TS::setNewDelete_delta( 0 );


    // Run the test(s)
    int result = Catch::Session().run( argc, argv );

	// Shutdown Cpl so my testing infra-structure cleanup/post processing gets done
    Cpl::System::Shutdown_TS::restore();
    return Cpl::System::Shutdown::failure( result );
}
