/*-----------------------------------------------------------------------------
* Blah..
*----------------------------------------------------------------------------*/
/** @file */

/* Command line options: -p CADIFRA -doxygen -o Fsm -l cppx -Trace Fsm.cdd   */
/* This file is generated from Fsm.cdd - do not edit manually  */
/* Generated on:  version 3.7 */


/* Include default headers (no header definition in UML state-chart provided) */
/* Define a header comment in your statediagram.model to define own includes here. */
#include "Cpl/Rte/Persistence/Record/Fsm_ext_.h"
#include "Cpl/Rte/Persistence/Record/Fsm_.h"
#include "Cpl/Rte/Persistence/Record/Fsm_trace_.h"

namespace Cpl { namespace Rte { namespace Persistence { namespace Record  {

    Fsm::Fsm(void)
    {
        m_initialized=0U;
    }



    /* State names */
    const char states[]=
        "Clean\0DelayingWrite\0Writing\0WaitingOnRead\0Initialized\0WriteDefaulting\0WritingRecord\0ReadDefaulting\0Idle\0Starting\0Defaulting\0Stopping\0Active\0";

    const unsigned short state_idx[]={
        0,6,20,28,42,54,70,84,99,104,113,124,133,140};

    /* Event names */
    const char events[]=
        "Fsm_evLoadDone\0Fsm_evDisconnected\0Fsm_evDefault\0Fsm_evTimerExpired\0Fsm_evStart\0Fsm_evDataModified\0Fsm_evReadDone\0Fsm_evStop\0Fsm_evWriteDone\0NO_MSG\0";

    const unsigned short evt_idx[]={
        0,15,34,48,67,79,98,113,124,140};

    const char* Fsm::getNameByState(unsigned short state) const {
        return states+state_idx[state];
    }

    const char* Fsm::getNameByEvent(FSM_EVENT_T evt) const {
        return events+evt_idx[evt];
    }


    // Helper(s) to reset history
    void Fsm::resetHistoryStarting(void){
        stateVars.stateVarStarting=WaitingOnRead;
    }

    void Fsm::resetHistoryActive(void){
        stateVars.stateVarActive=Clean;
    }


    // Helper(s) to find out if the machine is in a certain state

    bool Fsm::isInClean(void) const {return(((stateVars.stateVarActive== Clean)&&(stateVars.stateVar== Active)) ? (true) : (false));}
    bool Fsm::isInDelayingWrite(void) const {return(((stateVars.stateVarActive== DelayingWrite)&&(stateVars.stateVar== Active)) ? (true) : (false));}
    bool Fsm::isInWriting(void) const {return(((stateVars.stateVarActive== Writing)&&(stateVars.stateVar== Active)) ? (true) : (false));}
    bool Fsm::isInWaitingOnRead(void) const {return(((stateVars.stateVarStarting== WaitingOnRead)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInInitialized(void) const {return(((stateVars.stateVarStarting== Initialized)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInWriteDefaulting(void) const {return(((stateVars.stateVarStarting== WriteDefaulting)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInWritingRecord(void) const {return(((stateVars.stateVarStarting== WritingRecord)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInReadDefaulting(void) const {return(((stateVars.stateVarStarting== ReadDefaulting)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInIdle(void) const {return(((stateVars.stateVar== Idle)) ? (true) : (false));}
    bool Fsm::isInStarting(void) const {return(((stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInDefaulting(void) const {return(((stateVars.stateVarStarting== Defaulting)&&(stateVars.stateVar== Starting)) ? (true) : (false));}
    bool Fsm::isInStopping(void) const {return(((stateVars.stateVar== Stopping)) ? (true) : (false));}
    bool Fsm::isInActive(void) const {return(((stateVars.stateVar== Active)) ? (true) : (false));}

    // Helper to get id of innermost active state

    unsigned short Fsm::getInnermostActiveState(void) const {
        if(isInDefaulting()){
            return Defaulting;
        }else if(isInReadDefaulting()){
            return ReadDefaulting;
        }else if(isInWritingRecord()){
            return WritingRecord;
        }else if(isInWriteDefaulting()){
            return WriteDefaulting;
        }else if(isInInitialized()){
            return Initialized;
        }else if(isInWaitingOnRead()){
            return WaitingOnRead;
        }else if(isInWriting()){
            return Writing;
        }else if(isInDelayingWrite()){
            return DelayingWrite;
        }else if(isInClean()){
            return Clean;
        }else if(isInStopping()){
            return Stopping;
        }else if(isInIdle()){
            return Idle;
        }else{
            return NUM_STATES;
        }
    }
    // Initialize method. Must be called once to init the machine
    void Fsm::initialize(){
        //call on entry code of default states
        if(m_initialized==0U){
            m_initialized=1U;

            //Create copy of statevar
            stateVarsCopy = stateVars;

            // Set state vars to default states

            stateVarsCopy.stateVar = Idle; /* set init state of top state */
            stateVarsCopy.stateVarStarting = WaitingOnRead; /* set init state of Starting */
            stateVarsCopy.stateVarActive = Clean; /* set init state of Active */

        // Copy state variables back
        stateVars = stateVarsCopy;

        }



    }

    // State machine event handler
    int Fsm::processEvent(FSM_EVENT_T msg){

        int evConsumed = 0U;

    

        if(m_initialized==0U) return 0;

        //Create copy of statevar
        stateVarsCopy = stateVars;


        switch (stateVars.stateVar) {

            case Idle:
                if(msg==Fsm_evStart){
                    /* Transition from Idle to Starting */
                    evConsumed=1;

                    /* Action code for transition  */
                    tellStarting();
                    defaultData();

                    stateVarsCopy.stateVar = Starting;/* Default in entry chain  */
                    stateVarsCopy.stateVarStarting = WaitingOnRead;/* Default in entry chain  */

                    FsmTraceEvent(0);
                }else{
                    /* Intentionally left blank */
                } /*end of event selection */
            break; /* end of case Idle  */

            case Starting:

                switch (stateVars.stateVarStarting) {

                    case WaitingOnRead:
                        if(msg==Fsm_evDefault){
                            /* Transition from WaitingOnRead to ReadDefaulting */
                            evConsumed=1;


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = ReadDefaulting;
                            FsmTraceEvent(5);
                        }else if(msg==Fsm_evLoadDone){
                            /* Transition from WaitingOnRead to WritingRecord */
                            evConsumed=1;

                            /* Action code for transition  */
                            
                            issueWrite();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WritingRecord;
                            FsmTraceEvent(4);
                        }else if(msg==Fsm_evReadDone){
                            /* Transition from WaitingOnRead to Initialized */
                            evConsumed=1;

                            /* Action code for transition  */
                            tellInitialized();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = Initialized;
                            FsmTraceEvent(2);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case WaitingOnRead  */

                    case Initialized:
                        if(msg==Fsm_evDefault){
                            /* Transition from Initialized to Defaulting */
                            evConsumed=1;


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = Defaulting;
                            FsmTraceEvent(5);
                        }else if(msg==Fsm_evLoadDone){
                            if(isLoadGood()){
                                /* Transition from Initialized to Active */
                                evConsumed=1;


                                /* Action code for transition  */
                                
                                connectToModel();
                                markClean();
                                tellStartCompleted();

                                stateVarsCopy.stateVar = Active;/* entry chain  */

                                /* adjust state variables  */
                                stateVarsCopy.stateVarStarting = WaitingOnRead;
                                FsmTraceEvent(9);
                            }else{
                                /* Transition from Initialized to WritingRecord */
                                evConsumed=1;

                                /* Action code for transition  */
                                
                                issueWrite();


                                /* adjust state variables  */
                                stateVarsCopy.stateVarStarting = WritingRecord;
                                FsmTraceEvent(10);
                            } /*end of event selection */
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case Initialized  */

                    case WritingRecord:
                        if(msg==Fsm_evDefault){
                            /* Transition from WritingRecord to WriteDefaulting */
                            evConsumed=1;


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WriteDefaulting;
                            FsmTraceEvent(5);
                        }else if(msg==Fsm_evWriteDone){
                            /* Transition from WritingRecord to Active */
                            evConsumed=1;


                            /* Action code for transition  */
                            connectToModel();
                            markClean();
                            tellStartCompleted();

                            stateVarsCopy.stateVar = Active;/* entry chain  */

                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WaitingOnRead;
                            FsmTraceEvent(6);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case WritingRecord  */

                    case ReadDefaulting:
                        if(msg==Fsm_evLoadDone){
                            /* Transition from ReadDefaulting to WritingRecord */
                            evConsumed=1;

                            /* Action code for transition  */
                            
                            issueWrite();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WritingRecord;
                            FsmTraceEvent(4);
                        }else if(msg==Fsm_evReadDone){
                            /* Transition from ReadDefaulting to Defaulting */
                            evConsumed=1;

                            /* Action code for transition  */
                            tellInitialized();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = Defaulting;
                            FsmTraceEvent(2);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case ReadDefaulting  */

                    case Defaulting:
                        if(msg==Fsm_evLoadDone){
                            /* Transition from Defaulting to WritingRecord */
                            evConsumed=1;

                            /* Action code for transition  */
                            defaultData();
                            issueWrite();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WritingRecord;
                            FsmTraceEvent(4);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case Defaulting  */

                    case WriteDefaulting:
                        if(msg==Fsm_evWriteDone){
                            /* Transition from WriteDefaulting to WritingRecord */
                            evConsumed=1;

                            /* Action code for transition  */
                            defaultData();
                            issueWrite();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarStarting = WritingRecord;
                            FsmTraceEvent(6);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case WriteDefaulting  */

                    default:
                        /* Intentionally left blank */
                    break;
                } /* end switch Starting */

                /* Check if event was already processed  */
                if(evConsumed==0){

                    if(msg==Fsm_evStop){
                        /* Transition from Starting to Idle */
                        evConsumed=1;
                        
                        /* Action code for transition  */
                        tellStopped();


                        /* adjust state variables  */
                        stateVarsCopy.stateVar = Idle;
                        FsmTraceEvent(1);
                    }else{
                        /* Intentionally left blank */
                    } /*end of event selection */
                }
            break; /* end of case Starting  */

            case Stopping:
                if(msg==Fsm_evDisconnected){
                    /* Transition from Stopping to Idle */
                    evConsumed=1;

                    /* Action code for transition  */
                    tellStopped();


                    /* adjust state variables  */
                    stateVarsCopy.stateVar = Idle;
                    FsmTraceEvent(3);
                }else{
                    /* Intentionally left blank */
                } /*end of event selection */
            break; /* end of case Stopping  */

            case Active:

                switch (stateVars.stateVarActive) {

                    case Clean:
                        if(msg==Fsm_evDataModified){
                            /* Transition from Clean to DelayingWrite */
                            evConsumed=1;

                            /* Action code for transition  */
                            startTimer();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarActive = DelayingWrite;
                            FsmTraceEvent(7);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case Clean  */

                    case DelayingWrite:
                        if(msg==Fsm_evDataModified){
                            /* Transition from DelayingWrite to DelayingWrite */
                            evConsumed=1;


                            /* adjust state variables  */
                            stateVarsCopy.stateVarActive = DelayingWrite;
                            FsmTraceEvent(7);
                        }else if(msg==Fsm_evTimerExpired){
                            /* Transition from DelayingWrite to Writing */
                            evConsumed=1;

                            /* Action code for transition  */
                            issueWrite();
                            markClean();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarActive = Writing;
                            FsmTraceEvent(8);
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case DelayingWrite  */

                    case Writing:
                        if(msg==Fsm_evDataModified){
                            /* Transition from Writing to Writing */
                            evConsumed=1;

                            /* Action code for transition  */
                            markDirty();


                            /* adjust state variables  */
                            stateVarsCopy.stateVarActive = Writing;
                            FsmTraceEvent(7);
                        }else if(msg==Fsm_evWriteDone){
                            if(isDirty()){
                                /* Transition from Writing to DelayingWrite */
                                evConsumed=1;

                                /* Action code for transition  */
                                
                                startTimer();


                                /* adjust state variables  */
                                stateVarsCopy.stateVarActive = DelayingWrite;
                                FsmTraceEvent(11);
                            }else{
                                /* Transition from Writing to Clean */
                                evConsumed=1;


                                /* adjust state variables  */
                                stateVarsCopy.stateVarActive = Clean;
                                FsmTraceEvent(12);
                            } /*end of event selection */
                        }else{
                            /* Intentionally left blank */
                        } /*end of event selection */
                    break; /* end of case Writing  */

                    default:
                        /* Intentionally left blank */
                    break;
                } /* end switch Active */

                /* Check if event was already processed  */
                if(evConsumed==0){

                    if(msg==Fsm_evDefault){
                        /* Transition from Active to Active */
                        evConsumed=1;
                        
                        /* Action code for transition  */
                        defaultData();

                        stateVarsCopy.stateVar = Active;/* entry chain  */

                        FsmTraceEvent(5);
                    }else if(msg==Fsm_evStop){
                        /* Transition from Active to Stopping */
                        evConsumed=1;
                        
                        /* Action code for transition  */
                        disconnectFromModel();
                        stopTimer();


                        /* adjust state variables  */
                        stateVarsCopy.stateVar = Stopping;
                        FsmTraceEvent(1);
                    }else{
                        /* Intentionally left blank */
                    } /*end of event selection */
                }
            break; /* end of case Active  */

            default:
                /* Intentionally left blank */
            break;
        } /* end switch stateVar_root */
    // Copy state variables back
    stateVars = stateVarsCopy;
    CPL_SYSTEM_TRACE_MSG( SECT_, ( "New State=%s", getNameByState(getInnermostActiveState()) ));

        return evConsumed;
    } // end processEvent







};};};}; //namespace Cpl { namespace Rte { namespace Persistence { namespace Record 

