#ifndef Point_ViewerBar4_h_
#define Point_ViewerBar4_h_
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

#include "Rte/Point/Viewer/Composer.h"
#include "Rte/TShell/Dac/_0test/Point/bar4.h"

///
namespace Point {


/** Concrete Viewer Point: BAR4
 */
template <class CONTEXT>
class ViewerBar4: public Bar4,
                  public Rte::Point::Viewer::Composer<CONTEXT>
{
public:
    /// Constructor
    ViewerBar4( CONTEXT&                                                                    context,
                typename Rte::Point::Viewer::Composer<CONTEXT>::ChangeNotificationFunc_T    contextChangedCb,
                typename Rte::Point::Viewer::Composer<CONTEXT>::StoppedNotificationFunc_T   contextStoppedCb,
                ModelBar4&                                                                  modelPoint,
                Cpl::Itc::PostApi&                                                          viewerMbox 
              )
    :Rte::Point::Viewer::Composer<CONTEXT>::Composer(*this, context, contextChangedCb, contextStoppedCb, modelPoint, viewerMbox)
        {}
};


/** Concrete LIGHT WEIGHT Viewer Point: BAR4
 */
template <class CONTEXT>
class LWViewerBar4: public Bar4Null,
                    public Rte::Point::Viewer::Composer<CONTEXT>
{
public:
    /// Constructor
    LWViewerBar4( CONTEXT&                                                                    context,
                  typename Rte::Point::Viewer::Composer<CONTEXT>::ChangeNotificationFunc_T    contextChangedCb,
                  typename Rte::Point::Viewer::Composer<CONTEXT>::StoppedNotificationFunc_T   contextStoppedCb,
                  ModelBar4&                                                                  modelPoint,
                  Cpl::Itc::PostApi&                                                          viewerMbox 
                )
    :Rte::Point::Viewer::Composer<CONTEXT>::Composer(*this, context, contextChangedCb, contextStoppedCb, modelPoint, viewerMbox)
        {}
};

};
#endif 