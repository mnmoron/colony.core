#ifndef Cpl_System_ElaspedTime_h_
#define Cpl_System_ElaspedTime_h_
/*----------------------------------------------------------------------------- 
* This file is part of the Colony.Core Project.  The Colony.Core Project is an   
* open source project with a BSD type of licensing agreement.  See the license  
* agreement (license.txt) in the top/ directory or on the Internet at           
* http://integerfox.com/colony.core/license.txt
*                                                                               
* Copyright (c) 2014, 2015  John T. Taylor                                        
*                                                                               
* Redistributions of the source code must retain the above copyright notice.    
*----------------------------------------------------------------------------*/ 
/** @file */

#include <stdint.h>


/// 
namespace Cpl { namespace System { 

/** This class defines the interface for accessing the elasped time since
    power up and/or reset of the platform.  Elasped time in provided in
    three different formats:milliseconds, seconds, and seconds with 
    milliseconds precision.  All time formats are guarentied to be
    synchronized with each other.
 */
class ElaspedTime
{
public:
    /// Datatype for time in seconds with a 'fractional' millisecond precision
    typedef struct Precision_Tag
        {
        unsigned long  m_seconds;      //!< Total number of elasped seconds
        uint16_t       m_thousandths;  //!< fractional number of milliseconds (i.e. a value between 0 and 999)
        } Precision_T;


public:
    /** This method returns the elasped time, in seconds, since the system
        was powered on and/or reset.  The elapsed time is free running counter
        that will roll over once the range of the data type is exceeded.
     */
    static unsigned long    seconds() throw();


    /** This method returns the elasped time, in milliseconds, since the system
        was powered on and/or reset.  The elapsed time is free running counter
        that will roll over once the range of the data type is exceeded.
     */
    static unsigned long    milliseconds() throw();


    /** This method returns the elasped time, in seconds with milliseconds
        prceission, since the system was powered on and/or reset.  The elapsed 
        second time is free running counter that will roll over once the range 
        of the data type is exceeded.
     */
    static Precision_T  precision() throw();


public:
    /** This method returns the delta time, in millseconds, between the 
        specified 'startTime' and 'endTime'.  'endTime' is defaulted to
        NOW (i.e. a call to milliseconds(). The calculation properly
        handles the scenario of when the has been 'roll over' between the
        two times. 
     */
    inline static unsigned long deltaMilliseconds( unsigned long startTime, unsigned long endTime = milliseconds() ) throw()
        {
        return endTime - startTime;
        }


    /** This method returns the delta time, in seconds, between the 
        specified 'startTime' and 'endTime'.  'endTime' is defaulted to
        NOW (i.e. a call to seconds(). The calculation properly
        handles the scenario of when the has been 'roll over' between the
        two times.
     */
    inline static unsigned long deltaSeconds( unsigned long startTime, unsigned long endTime = seconds() ) throw()
        {
        return endTime - startTime;
        }

    /** This method returns the delta time, in Precision time, between the 
        specified 'startTime' and 'endTime'.  'endTime' is defaulted to
        NOW (i.e. a call to precision(). The calculation properly
        handles the scenario of when the has been 'roll over' between the
        two times.
     */
    static Precision_T deltaPrecision( Precision_T startTime, Precision_T endTime = precision() ) throw();


public:
    /** This method returns true if the specified amount of time has elasped 
        since the 'timeMarker'.  The calculation properly handles the scenario 
        of when the has been 'roll over' between the 'timeMarker' and NOW.
     */
    inline static bool expiredMilliseconds( unsigned long timeMarker, unsigned long duration, unsigned long currentTime = milliseconds() ) throw()
        {
        return deltaMilliseconds( timeMarker, currentTime ) >= duration;
        }

    /** This method returns true if the specified amount of time has elasped 
        since the 'timeMarker'.  The calculation properly handles the scenario 
        of when the has been 'roll over' between the 'timeMarker' and NOW.
     */
    inline static bool expiredSeconds( unsigned long timeMarker, unsigned long duration, unsigned long currentTime = seconds() ) throw()
        {
        return deltaSeconds( timeMarker, currentTime ) >= duration;
        }


    /** This method returns true if the specified amount of time has elasped 
        since the 'timeMarker'.  The calculation properly handles the scenario 
        of when the has been 'roll over' between the 'timeMarker' and NOW.
     */
    static bool expiredPrecision( Precision_T timeMarker, Precision_T duration, Precision_T currentTime = precision() ) throw();


    
public:
    /** This method is the same as seconds(), EXCEPT that is ALWAYS guaranteed
        to return elasped time in 'real time'.  See the Cpl::System::SimTick for
        more details about real time vs. simulated time.  It is recommended
        the application NOT CALL this method because then that code can NOT
        be simulated using the SimTick interface.
     */
    static unsigned long    secondsInRealTime() throw();


    /** This method is the same as milliseconds(), EXCEPT that is ALWAYS 
        guaranteed to return elasped time in 'real time'.  See the 
        Cpl::System::SimTick for more details about real time vs. simulated 
        time.  It is recommended the application NOT CALL this method because 
        then that code can NOT be simulated using the SimTick interface.
     */
    static unsigned long    millisecondsInRealTime() throw();


    /** This method is the same as precision(), EXCEPT that is ALWAYS guaranteed
        to return elasped time in 'real time'.  See the Cpl::System::SimTick for
        more details about real time vs. simulated time.  It is recommended
        the application NOT CALL this method because then that code can NOT
        be simulated using the SimTick interface.
     */
    static Precision_T      precisionInRealTime() throw();



};

        
};      // end namespaces
};
#endif  // end header latch

