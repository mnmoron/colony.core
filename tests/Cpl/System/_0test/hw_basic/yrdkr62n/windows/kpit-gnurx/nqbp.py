#!/usr/bin/python
"""
Invokes NQBP's mk.py script. This script must be executed in the individual
projects/ directories.  This means that you must COPY this script to each
project directory you plan on using NQBP.

"""

import os
import sys

# Make sure the environment is properly set
NQBP_BIN = os.environ.get('NQBP_BIN')
if ( NQBP_BIN == None ):
    sys.exit( "ERROR: The environment variable NQBP_BIN is not set!" )
sys.path.append( NQBP_BIN )

# Find the Package & Workspace root
from nqbplib import utils
utils.set_pkg_and_wrkspace_roots(__file__)

# Call into core/common scripts
import mytoolchain
from nqbplib import mk
mk.build( sys.argv, mytoolchain.create() )
