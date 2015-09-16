#ifndef Cpl_Text_Frame_StreamDecoder_h_
#define Cpl_Text_Frame_StreamDecoder_h_
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


#include "Cpl/Text/Frame/Decoder_.h"
#include "Cpl/Io/Input.h"


///
namespace Cpl { namespace Text { namespace Frame {



/** This partially concrete class defines an interface a Text "Decoder" that 
    has a Cpl::Io::Input stream as its input source.  See 
    Cpl::Text::Frame::Decoder for details on what is a decoder. 
 */
class StreamDecoder: public Decoder_
{
protected:
    /// Input stream
    Cpl::Io::Input* m_srcPtr;

protected:
    /** Constructor.  The 'inputSource' can optionally be specified at 
        construction time or defer till later (the default is: later).  However,
        the "input source" MUST be specified BEFORF scan() is called or a
        fatal error will be generated.  See Cpl::Text::Frame::Decoder_ for 
        details about the other constructuor arguments.  
        
        NOTE: A sub-class IS required to actual create an instance of a 
        StreamDecoder.
     */
    StreamDecoder( char rawInputBuffer[], size_t sizeOfRawInputBuffer, Cpl::Io::Input* inputSource=0 );


public:
    /** This method allows the Application/consumer to change/Set the Input
        Stream handle. 
     */
    void setInput( Cpl::Io::Input& newInFd ) throw();


protected:
    /// See Cpl::Text::Frame::Decoder_
    bool read( void* buffer, int numBytes, int& bytesRead );

};




};      // end namespaces
};
};
#endif  // end header latch
