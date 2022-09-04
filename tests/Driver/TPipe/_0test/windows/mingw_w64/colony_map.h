#ifndef COLONY_MAP_H_
#define COLONY_MAP_H_

/// Button Unit Test mappings
#include "Driver/Button/_0test/mappings_.h"


// Cpl::System mappings
#ifdef BUILD_VARIANT_CPP11
#include "Cpl/System/Cpp11/_win32/mappings_.h"

#else
#include "Cpl/System/Win32/mappings_.h"
#endif

// strapi mapping
#include "Cpl/Text/_mappings/_mingw/strapi.h"


#endif
