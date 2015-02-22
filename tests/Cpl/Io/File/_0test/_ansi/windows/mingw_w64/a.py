#!/usr/bin/python
"""
Script to run unittests (leverages NQBP python code base)

"""

import os
import sys
import shutil
import subprocess

#------------------------------------------------------------------------------
def run_test( root, subdir ):
    utils.push_dir( subdir )
    src = os.path.join( root, 'colony.core', 'src', 'Cpl', 'Io', 'File', '_0test', 'testinput.txt' )
    shutil.copy( src, '.' ); 
    print "Running unit test dir: {} ...".format( subdir )
    subprocess.call( 'b.exe', shell=True )
    utils.pop_dir()
        


#------------------------------------------------------------------------------
# Make sure the environment is properly set
NQBP_BIN = os.environ.get('NQBP_BIN')
if ( NQBP_BIN == None ):
    sys.exit( "ERROR: The environment variable NQBP_BIN is not set!" )
sys.path.append( NQBP_BIN )

# Find the Package & Workspace root
from nqbplib import utils
from nqbplib import my_globals
utils.set_pkg_and_wrkspace_roots(__file__)


#------------------------------------------------------------------------------
# MAIN ENTRY POINT....
#

if ( os.path.isdir( '_win32' ) ):
    run_test( my_globals.NQBP_WORK_ROOT(), '_win32' )
    print

if ( os.path.isdir( '_cpp11' ) ):
    run_test( my_globals.NQBP_WORK_ROOT(), '_cpp11' )
    print
    
