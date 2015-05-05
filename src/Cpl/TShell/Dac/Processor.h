#ifndef Cpl_TShell_Dac_Processor_h_
#define Cpl_TShell_Dac_Processor_h_
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

#include "colony_config.h"
#include "Cpl/TShell/Dac/Context_.h"
#include "Cpl/TShell/Dac/Variable_.h"
#include "Cpl/System/Mutex.h"
#include "Cpl/System/FastLock.h"
#include "Cpl/System/Api.h"
#include "Cpl/Text/FString.h"
#include "Cpl/Text/Frame/Encoder.h"
#include "Cpl/Text/Frame/Decoder.h"
#include "Cpl/Log/Loggers.h"
#include "Cpl/Container/Stack.h"


/** This symbol defines the size, in bytes, of the maximum allowed input
    stirng/command.
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE              128
#endif

/** This symbols define the size, in bytes (not including the null termintor) of
    the common Numeric work buffer
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_WORKBUF_SIZE
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_WORKBUF_SIZE            22
#endif

/** The symbol defines the string name of the ErrorLevel shell variable
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_NAME_ERRORLEVEL
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_NAME_ERRORLEVEL         "_errno"
#endif

/** This symbols defines the maximum number of nested loops
 */
#ifndef OPTION_CPL_TSHELL_PROCESSOR_MAX_NESTED_LOOPS   
#define OPTION_CPL_TSHELL_PROCESSOR_MAX_NESTED_LOOPS            3
#endif
 
/** This symbols defines the Shell's greeting message
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_GREETING
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_GREETING                "\n--- Your friendly neighborhood DAC shell. ---\n\n\n"
#endif

/** This symbols defines the Shell's farewell message
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_FAREWELL
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_FAREWELL                "\n--- ...I am melting, am melting... ---\n\n"
#endif

/** This symbols defines the Shell's prompt string
 */
#ifndef OPTION_CPL_TSHELL_DAC_PROCESSOR_PROMPT
#define OPTION_CPL_TSHELL_DAC_PROCESSOR_PROMPT                  "$ "
#endif



///
namespace Cpl { namespace TShell { namespace Dac {

/** This concrete class provides the implementation of Command Processor for
    a DAC TShell.

    The implemeantion assumes a single threaded model, i.e. the Command
    Processor and all of its  commands run in a single thread.  It is 
    APPLICATION's responsibility to provide any desired multi-threaded 
    support. There are two caveats to the single-threaded model:
        
        o The output of the commands are mutex protected.  This allows the
          Output stream to be 'shared' with other sub-systems and/or
          threads (e.g. the shell shares the same Output stream as the 
          Cpl::System::Trace logging output).

        o The stop() method can be called safely from other threads.


    Commands have the following syntax:
        
        o A command starts with a printable ASCII character and ends with
          a newline.  

        o Non-printable ASCII characters are not allowed.
        
        o Any line that starts with a '#' is treated as comment line and
          is ignored.
          
        o Format of a command is: verb [arg]*  where the verb and arguments
          are seperated by spaces.  Arguments can contain spaces character
          buy enclosing the argument with double quote characters.  A double
          quote character can be embedded inside a quoted string by preceeding
          it the double quote character with the esacpe character.  The escape
          character can be embedded by escaping the esacpe character.
 */
class Processor: public Context_
{
public:
    /** Data type/structured used to buffer commands. 
     */
    typedef char CommandBuffer_T[OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE+1];


protected:
    /// Command list
    Cpl::Container::Map<Command_>&      m_commands;

    /// Variable list
    ActiveVariablesApi&                 m_variables;

    /// Raw input deframer
    Cpl::Text::Frame::Decoder&          m_deframer;

    /// Output framer
    Cpl::Text::Frame::Encoder&          m_framer;

    /// Buffer that the output framer is required to use
    Cpl::Text::String&                  m_outputFrameBuffer;
     
    /// Output lock
    Cpl::System::Mutex&                 m_outLock;

    /// Command buffer
    CommandBuffer_T*                    m_cmdBuffer;

    /// Size of the command buffer
    unsigned                            m_cmdBufSize;

    /// Fast lock (for protecting stop request)
    Cpl::System::FastLock               m_fast;

    /// Comment character
    char                                m_comment;

    /// Argument Escape character
    char                                m_esc;

    /// Argument delimiter
    char                                m_del;

    /// Argument quote character
    char                                m_quote;

    /// Argument terminotr character
    char                                m_term;

    /// Error level Shell variable
    Variable_                           m_errorLevel;

    /// My run state
    bool                                m_running;
    
    /// My filtering state
    bool                                m_filtering;

    /// Filter marker (i.e skip command until marker is encounter)
    const char*                         m_filterMarker;

    /// Reference counter for Replay mode
    unsigned                            m_replayCount;

    /// Reference counter for Capture mode
    unsigned                            m_captureCount;

    /// Current index into the command buffer/cache
    unsigned                            m_currentIdx;

    /// Current index into the command buffer/cache when in replay mode
    unsigned                            m_replayIdx;

    /// Stack used to remember start-index of loops for replay mode
    Cpl::Container::Stack<unsigned>     m_startIndexes;

    /// Memory for the start-indexes stack
    unsigned                            m_memStack[OPTION_CPL_TSHELL_PROCESSOR_MAX_NESTED_LOOPS];


    /// Log warning events
    Cpl::Log::Api&                      m_logger;


    /// Input Frame buffer
    char                                m_inputBuffer[OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE+1];

    /// Copy of the deframed input string (because the parser is a destructive parser)
    char                                m_inputCopy[OPTION_CPL_TSHELL_DAC_PROCESSOR_INPUT_SIZE+1];


    /// Shared work buffer
    Cpl::Text::FString<OPTION_CPL_TSHELL_DAC_PROCESSOR_WORKBUF_SIZE> m_numericWorkBuffer;



public:
    /** Constructor.

        @param commands         Set of supported commands
        @param variables        Set of available variables for the Command 
                                Processor. If the application does not use (or
                                want) shell variables, then it should created
                                an ActiveVariables instance with zero for 
                                max number of variables (i.e. use NullVariables
                                class).
                                (other than ErrorLevel) is supported.
        @param deframer         Frame decoder used to identify individual command
                                strings within the raw Input stream
        @param framer           Frame encoder used to encapsulate the output of
                                command in the Output stream.
        @param outputLock       Mutex to be used for ensuring the atomic output
                                of the commands.
        @param cmdBufferPtr     Memory to store buffered commands.  If the value
                                is zero, then capturing/replaying of commands is
                                not supported.
        @param maxBufferCmds    Number of commands that can be stored in the
                                'command buffer'
        @param commentChar      The comment character used to indicate that the
                                input string is a comment and should not be
                                executed.
        @param argEscape        Escape character to be used when escaping qouble 
                                quote characters inside a quoted argument.
        @param argDelimiter     The delimiter character used to seperate the
                                command verb and arguments.
        @param argQuote         The quote character used to 'double quote' a
                                argument string.
        @param argTerminator    The command terminator character.
        @param eventLogger      The event logger to be used.
     */
    Processor( Cpl::Container::Map<Command_>&    commands,
               ActiveVariablesApi&               variables,
               Cpl::Text::Frame::Decoder&        deframer,
               Cpl::Text::Frame::Encoder&        framer,
               Cpl::Text::String&                outputFrameBuffer,
               Cpl::System::Mutex&               outputLock,
               CommandBuffer_T*                  cmdBufferPtr=0, 
               unsigned                          maxBufferCmds=0,
               char                              commentChar='#',
               char                              argEscape='`', 
               char                              argDelimiter=' ', 
               char                              argQuote='"',
               char                              argTerminator='\n',
               Cpl::Log::Api&                    eventLogger = Cpl::Log::Loggers::console()
             );


public:
    /// See Cpl::TShell::Processor
    bool start( Cpl::Io::Input& infd, Cpl::Io::Output& outfd ) throw();

    /// See Cpl::TShell::Processor
    void requestStop() throw();


public:
    /// See Cpl::TShell::Dac::Context_
    Command_::Result_T executeCommand( const char* deframedInput, Cpl::Io::Output& outfd ) throw();


public:
    /// See Cpl::TShell::Dac::Context_
    Cpl::System::Mutex& getOutputLock() throw();

    /// See Cpl::TShell::Dac::Context_
    Cpl::Container::Map<Command_>& getCommands() throw();

    /// See Cpl::TShell::Dac::Context_
    ActiveVariablesApi& getVariables() throw();

    /// See Cpl::TShell::Dac::Context_
    VariableApi& getErrorLevel() throw();

    /// See Cpl::TShell::Dac::Context_
    Cpl::Text::String& getOutputFrameBuffer() throw();


public:
    /// See Cpl::TShell::Dac::Context_
    void startOutput() throw();

    /// See Cpl::TShell::Dac::Context_
    void appendOutput( const char* text ) throw();

    /// See Cpl::TShell::Dac::Context_
    bool commitOutput( Cpl::Io::Output& outfd ) throw();

 
public:
    /// See Cpl::TShell::Dac::Context_
    void beginCommandReplay(void) throw();

    /// See Cpl::TShell::Dac::Context_
    void endCommandReplay(void) throw();

    /// See Cpl::TShell::Dac::Context_
    void beginCommandCapture(void) throw();

    /// See Cpl::TShell::Dac::Context_
    void endCommandCapture(void) throw();

public:
    /// See Cpl::TShell::Dac::Context_
    void enableFilter( Command_& marker ) throw();

public:
    /// See Cpl::TShell::Dac::Context_
    Cpl::Text::String& getNumericBuffer() throw();


protected:
    /// Outputs the shell's start message
    virtual bool greeting( Cpl::Io::Output& outfd ) throw();

    /// Outputs the shell's end message
    virtual bool farewell( Cpl::Io::Output& outfd ) throw();

    /// Outputs the shell's prompt
    virtual bool prompt( Cpl::Io::Output& outfd ) throw();


protected:
    /// Helper method
    bool outputCommandError( Cpl::Io::Output& outfd, Command_::Result_T result, const char* deframedInput ) throw();

};


};      // end namespaces
};
};
#endif  // end header latch