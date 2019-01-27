#ifndef Cpl_System_Win32_mappings_x_h_
#define Cpl_System_Win32_mappings_x_h_
/*-----------------------------------------------------------------------------
* This file is part of the Colony.Core Project.  The Colony.Core Project is an
* open source project with a BSD type of licensing agreement.  See the license
* agreement (license.txt) in the top/ directory or on the Internet at
* http://integerfox.com/colony.core/license.txt
*
* Copyright (c) 2014-2018  John T. Taylor
*
* Redistributions of the source code must retain the above copyright notice.
*----------------------------------------------------------------------------*/
/** @file

    This file provides the mappings for Platform specific types, etc. needed
    by Cpl::System

 */


#include <windows.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "colony_config.h"


/// Win32 Mapping
#define CPL_SYSTEM_ASSERT_MAP(e)                assert(e)

/// Win32 Mapping
#define Cpl_System_Thread_NativeHdl_T_MAP       HANDLE  

/// Win32 Mapping
#define Cpl_System_Mutex_T_MAP                  CRITICAL_SECTION

/// Win32 Mapping
#define Cpl_System_Sema_T_MAP                   HANDLE

/// Win32 Mapping
#define Cpl_System_TlsKey_T_MAP                 DWORD

/// Win32 Mapping
#define Cpl_System_FastLock_T_MAP               CRITICAL_SECTION

/// Allow the application to adjust the Spin Count used for the FastLock
#ifndef OPTION_CPL_SYSTEM_FASTLOCK_SPIN_COUNT
#define OPTION_CPL_SYSTEM_FASTLOCK_SPIN_COUNT   4000 // Per the MSDN documentation '4000' is the spin count value used for per-heap critical sections
#endif


/// Win32 Mapping
#define CPL_SYSTEM_SHELL_NULL_DEVICE_x_MAP      "NUL"

/// Win32 Mapping
#define CPL_SYSTEM_SHELL_SUPPORTED_x_MAP        1


/// Win32 Mapping
#define CPL_IO_NEW_LINE_NATIVE_MAP              "\015\012"

/// Win32 Mapping
#define CPL_IO_FILE_NATIVE_DIR_SEP_MAP          '\\'

/// Win32 Mapping
#define CPL_IO_FILE_MAX_NAME_MAP                _MAX_PATH


/// Thread Priorities
#define CPL_SYSTEM_THREAD_PRIORITY_HIGHEST_MAP      15

/// Thread Priorities
#define CPL_SYSTEM_THREAD_PRIORITY_NORMAL_MAP       0

/// Thread Priorities
#define CPL_SYSTEM_THREAD_PRIORITY_LOWEST_MAP       -15

/// Thread Priorities
#define CPL_SYSTEM_THREAD_PRIORITY_RAISE_MAP        (+1)

/// Thread Priorities
#define CPL_SYSTEM_THREAD_PRIORITY_LOWER_MAP        (-1)



#endif  // end header latch
