#ifndef Cpl_Driver_Uart_Stream_Transmitter_h_
#define Cpl_Driver_Uart_Stream_Transmitter_h_
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

#include "Cpl/Driver/Uart/Hal.h"
#include "Cpl/Container/RingBuffer.h"
#include "Cpl/System/Thread.h"



/// 
namespace Cpl { namespace Driver { namespace Uart { namespace Stream {


/** This concrete class implements a blocking Transmit Stream UART driver. What
    does 'blocking Transmit Stream' mean?  'Blocking' means that the calling thread
    will block when the transmit buffer is full (and will be unblocked once there
    is free space in the transmit buffer). 'Stream' means that data is transmitted
    as a continual stream of bytes, i.e. the data is NOT broken down into frames,
    packets, etc. (think C stdout stream).

    This driver ASSUMES that at most there is only ONE client attempt to use the
    driver at any given time.  It is okay to call the start(), stop(), send() from 
    different threads - but the calls CANNOT be concurrent.  It is the applicaiton's 
    responsibility to provide additional thread-safety/concurrence protection.

    NOTE: Not all UART behave the same with respect to transmitting the 'first'
          byte (in a stream/buffer of bytes).  One method (which is the default
          for Cpl) is that a 'TX-done' interrupt is generated any time the
          TX data register is empty and the TX-done interrupt is enabled, i.e.
          the first byte in the stream/buffer is handle the same as all of the
          other bytes.  The second method is that the application/driver is
          required to expclity write the first byte to the TX Data register, 
          i.e. no interrupt for the intitial byte. 

 */
class Transmitter
{
protected:
    /// Handle to my low level hardware
    Cpl_Driver_Uart_Hal_T   m_uartHdl;

    /// Handle of the blocked client thread (if there is one)
    Cpl::System::Thread*    m_waiterPtr;

    /// Transmit buffer
    Cpl::Container::RingBuffer<uint8_t> m_buffer;

    /// Started state of the driver
    bool                    m_started;

    /// First TX behavior option
    bool                    m_manualFirstTx;


public:
    /** Constructor. Note: The driver does not being operating until start() is called. 

        @param uartHdl          The HAL layer UART Handle.  The application is required
                                to initialize the low level UART before starting this driver
        @param bufSize          The number of bytes in the supplied transmit buffer.
        @param bufMem           Array of bytes for the transmit/outbound buffer.
        @param manualFirstTx    When this flag is set to false the driver assumes that the
                                initial byte to be transmitted is interrupt driven.  When set
                                to true, the initial transmitted byte is 'manually' loaded.
     */
    Transmitter( Cpl_Driver_Uart_Hal_T uartHdl, unsigned bufSize, uint8_t bufMem[], bool manualFirstTx=false ) throw();



public:
    /** This method starts/enables the driver.  Note: The application is RESPONSIBLE for
        performing the low level initialization (Baud Rate, framing, etc.) of the UART
        BEFORE this method is called. For the application to change the Baud rate,
        framing, etc - it must first stop the driver and then restart it.
     */
    void start(void) throw();

    /** This method will stop/disable the driver.  The driver can be restarted 
        by call start() again.  The state of the contents of the outbound buffer 
        and the byte(s) 'in transmit' when the driver is stop is undetermined.
     */
    void stop(void) throw();
    

      
public:
    /** Transmits the specified number of bytes.  The method does not return until all
        bytes have been transferred to the outbound buffer. The application CANNOT 
        assume that the byte(s) have been physically transmitted on the 'wire' when
        this method returns. The method returns true if succesful; else false is return 
        When an error is encounter there is no guarenty/information-available with 
        respect to how many (if any) bytes where transmitted.
     */
    bool send( const void* data, size_t numBytesToTx ) throw();


public:
    /** This is a quasi-private method that the application should NOT call. The 
        method SHOULD only be called by the interrupt service routine (ISR) for 
        the 'TX-Done' interrupt for the UART identified by the 'uartHdl' supplied 
        in the constructor.  This requires that a reference (at a minimum) to the 
        driver instance be a global variable.  

        The method returns the result of signalling waiter (i.e. return code from
        su_signal()), or zero if no waiter was signaled.
     */
    int su_txDoneIsr_(void) throw();
 
     
private: 
    /// Prevent access to the copy constructor -->Driver can not be copied!
    Transmitter( const Transmitter& m );

    /// Prevent access to the assignment operator -->Driver can not be copied!
    const Transmitter& operator=( const Transmitter& m );

};

	

};      // end namespaces
};
};
};
#endif  // end header latch
