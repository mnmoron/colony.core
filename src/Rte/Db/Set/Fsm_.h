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

/* Command line options: -p CADIFRA -doxygen -o Fsm -l cppx -Trace Fsm.cdd   */
/* This file is generated from Fsm.cdd - do not edit manually  */
/* Generated on:  version 3.6.9 */


#ifndef __FSM_RTE_DB_SET_H__
#define __FSM_RTE_DB_SET_H__

/** \class Rte::Db::Set::Fsm
Here is the graph that shows the state machine this class implements
\dot
digraph G {
rankdir=TB;
bgcolor=transparent;
node[fontsize=8 shape=box];
edge[fontsize=8, arrowsize=0.5];
compound=true;
remincross=true;
nodesep=0.3;
ranksep=.4;
"Idle"->"defaultStarting"[labeldistance = 2.0, taillabel=<evStart / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>tellStarting();<br ALIGN="LEFT"/>defaultSetConten...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black lhead=clusterStarting];//Idle Starting
"defaultStarting"->"Idle"[labeldistance=2.0, headlabel=<evStop / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>tellStopped();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black ltail=clusterStarting];//Starting Idle
"WaitingOnRead"->"Initialized"[label=<evReadDone / <br ALIGN="LEFT"/>tellInitialized();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WaitingOnRead Initialized
"Stopping"->"Idle"[label=<evDisconnected / <br ALIGN="LEFT"/>tellStopped();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Stopping Idle
"WaitingOnRead"->"WritingRecord"[label=<evLoadDone / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>issueWrite();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WaitingOnRead WritingRecord
"WaitingOnRead"->"ReadDefaulting"[label=<evDefaultContent<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WaitingOnRead ReadDefaulting
"ReadDefaulting"->"Defaulting"[label=<evReadDone / <br ALIGN="LEFT"/>tellInitialized();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //ReadDefaulting Defaulting
"defaultroot"->"Idle"[label=<  > style=dotted];
"Defaulting"->"WritingRecord"[label=<evLoadDone / <br ALIGN="LEFT"/>defaultSetContents();<br ALIGN="LEFT"/>issueWrite...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Defaulting WritingRecord
"__C0"->"WritingRecord"[label=<[else] / issueWrite();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //__C0 WritingRecord
"Disconnecting"->"Idle"[label=<evStop<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Disconnecting Idle
"Initialized"->"Defaulting"[label=<evDefault<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Initialized Defaulting
"ReadDefaulting"->"WritingRecord"[label=<evLoadDone / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>issueWrite();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //ReadDefaulting WritingRecord
"__C0"->"defaultActive "[labeldistance = 2.0, taillabel=<[isLoadGood()] / <br ALIGN="LEFT"/>connectToModel();<br ALIGN="LEFT"/>markClean();<br ALIGN="LEFT"/>t...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black lhead=clusterActive ];//__C0 Active 
"defaultStarting"->"WaitingOnRead"[label=<  > style=dotted];
"WritingRecord"->"defaultActive "[labeldistance = 2.0, taillabel=<evWriteDone / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>connectToModel();<br ALIGN="LEFT"/>markClean();<br ALIGN="LEFT"/>t...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black lhead=clusterActive ];//WritingRecord Active 
"WritingDefaults"->"Idle"[label=<evStop<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WritingDefaults Idle
"defaultActive "->"Stopping"[labeldistance=2.0, headlabel=<evStop / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>disconnectFromModel();<br ALIGN="LEFT"/>stopTimer...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black ltail=clusterActive ];//Active  Stopping
"Clean"->"DelayingWrite"[label=<evDataModified / <br ALIGN="LEFT"/>startTimer();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Clean DelayingWrite
"DelayingWrite"->"DelayingWrite"[label=<evDataModified<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //DelayingWrite DelayingWrite
"DelayingWrite"->"Writing"[label=<evTimerExpired / <br ALIGN="LEFT"/>issueWrite();<br ALIGN="LEFT"/>markClean();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //DelayingWrite Writing
"Writing"->"__C1"[label=<evWriteDone<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Writing __C1
"__C1"->"Clean"[label=<[else]>  color=black, fontname=arial, fontcolor=black]; //__C1 Clean
"__C1"->"DelayingWrite"[label=<[isDirty()] / startTimer();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //__C1 DelayingWrite
"Writing"->"Writing"[label=<evDataModified / <br ALIGN="LEFT"/>markDirty();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Writing Writing
"defaultActive "->"Clean"[label=<  > style=dotted];
"defaultActive "->"Disconnecting"[labeldistance=2.0, headlabel=<evDefaultContent / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>disconnectFromModel();<br ALIGN="LEFT"/>stopTimer...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black ltail=clusterActive ];//Active  Disconnecting
"Disconnecting"->"WritingDefaults"[label=<evDisconnected / <br ALIGN="LEFT"/>defaultSetContents();<br ALIGN="LEFT"/>issueWrite...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Disconnecting WritingDefaults
"Initialized"->"__C0"[label=<evLoadDone<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //Initialized __C0
"WritingRecord"->"WriteDefaulting"[label=<evDefault<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WritingRecord WriteDefaulting
"WritingDefaults"->"defaultActive "[labeldistance = 2.0, taillabel=<evWriteDone / <br ALIGN="LEFT"/><br ALIGN="LEFT"/>connectToModel();<br ALIGN="LEFT"/>markClean();<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black lhead=clusterActive ];//WritingDefaults Active 
"WriteDefaulting"->"WritingRecord"[label=<evWriteDone / <br ALIGN="LEFT"/>defaultSetContents();<br ALIGN="LEFT"/>issueWrite...<br ALIGN="LEFT"/>>  color=black, fontname=arial, fontcolor=black]; //WriteDefaulting WritingRecord
"Idle"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Idle</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];subgraph "clusterStarting"{fontname=arial; fontsize=8
color=black; style="rounded";
label=<Starting<br ALIGN="LEFT"/><br ALIGN="LEFT"/>>;
"WaitingOnRead"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>WaitingOnRead</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"Initialized"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Initialized</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"WritingRecord"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>WritingRecord</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"ReadDefaulting"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>ReadDefaulting</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"Defaulting"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Defaulting</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"defaultStarting"[label=< >,shape=circle, fontsize=8, fixedsize=true, height=0.2, width=0.2, fillcolor=black, style=filled];
"WriteDefaulting"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>WriteDefaulting</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];};
"Stopping"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Stopping</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"defaultroot"[label=< >,shape=circle, fontsize=8, fixedsize=true, height=0.2, width=0.2, fillcolor=black, style=filled];
"Disconnecting"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Disconnecting</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"WritingDefaults"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>WritingDefaults</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];subgraph "clusterActive "{fontname=arial; fontsize=8
color=black; style="rounded";
label=<Active <br ALIGN="LEFT"/><br ALIGN="LEFT"/>>;
"Clean"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Clean</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"DelayingWrite"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>DelayingWrite</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];"defaultActive "[label=< >,shape=circle, fontsize=8, fixedsize=true, height=0.2, width=0.2, fillcolor=black, style=filled];
"Writing"[shape=record, color=black, fontname=arial, style=rounded, label=<{<B>Writing</B><br ALIGN="LEFT"/>|<br ALIGN="LEFT"/>}>];};
"__C0" [label=<  > shape=diamond, fixedsize=true, height=0.2, width=0.2, fontname=arial color=black];
"__C1" [label=<  > shape=diamond, fixedsize=true, height=0.2, width=0.2, fontname=arial color=black];
}
\enddot
*/

#include "Rte/Db/Set/Fsm_ext_.h"
#include "Rte/Db/Set/FsmContext_.h"

namespace Rte { namespace Db { namespace Set  {

    class Fsm: public FsmContext_
    {
        public:
            Fsm(void);

            int processEvent(FSM_EVENT_T msg);

            void initialize();

            // Helper(s) to reset history
            void resetHistoryStarting(void);
            void resetHistoryActive (void);

            // Helper(s) to find out if the machine is in a certain state
            bool isInClean(void) const;
            bool isInDelayingWrite(void) const;
            bool isInWriting(void) const;
            bool isInWaitingOnRead(void) const;
            bool isInInitialized(void) const;
            bool isInWriteDefaulting(void) const;
            bool isInWritingRecord(void) const;
            bool isInReadDefaulting(void) const;
            bool isInIdle(void) const;
            bool isInStarting(void) const;
            bool isInDefaulting(void) const;
            bool isInStopping(void) const;
            bool isInDisconnecting(void) const;
            bool isInWritingDefaults(void) const;
            bool isInActive (void) const;


            // Helper returning the innermost active state id.
            unsigned short getInnermostActiveState(void) const;


            // Returns the state name as string
            const char* getNameByState(unsigned short state) const;

            // Returns the event as string
            const char* getNameByEvent(FSM_EVENT_T evt) const;

            enum States{
                Clean,
                DelayingWrite,
                Writing,
                WaitingOnRead,
                Initialized,
                WriteDefaulting,
                WritingRecord,
                ReadDefaulting,
                Idle,
                Starting,
                Defaulting,
                Stopping,
                Disconnecting,
                WritingDefaults,
                Active ,
                NUM_STATES  // number of states in the machine
            };

        protected:
            int m_initialized;



        protected:
            // State variables
            struct stateVarsT{
                States stateVar;
                States stateVarStarting;
                States stateVarActive ;
            };
            stateVarsT stateVars;
            stateVarsT stateVarsCopy;



            /* Region handler prototypes  */
    };

};};}; //namespace Rte { namespace Db { namespace Set 


#endif // __FSM_RTE_DB_SET_H__