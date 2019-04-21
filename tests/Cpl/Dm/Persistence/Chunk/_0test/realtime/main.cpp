#include "Cpl/System/Api.h"
#include "Cpl/System/Trace.h"

#define CATCH_CONFIG_RUNNER  
#include "Catch/catch.hpp"


int main( int argc, char* argv[] )
{
    // Initialize Colony
    Cpl::System::Api::initialize();

    CPL_SYSTEM_TRACE_ENABLE();
    CPL_SYSTEM_TRACE_ENABLE_SECTION("_0test");
    CPL_SYSTEM_TRACE_ENABLE_SECTION("Dm::Point");
    CPL_SYSTEM_TRACE_ENABLE_SECTION("Dm::Point::Model");
    CPL_SYSTEM_TRACE_ENABLE_SECTION("Dm::Tuple");
    CPL_SYSTEM_TRACE_ENABLE_SECTION("Dm::Element");
    CPL_SYSTEM_TRACE_ENABLE_SECTION("Dm::Point::Viewer");
    CPL_SYSTEM_TRACE_SET_INFO_LEVEL( Cpl::System::Trace::eINFO );

    // Run the test(s)
    int result = Catch::Session().run( argc, argv );
    return result;
}
