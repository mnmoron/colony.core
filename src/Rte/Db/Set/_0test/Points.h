#ifndef Points_h_
#define Points_h_
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

#include "Rte/Point/Basic.h"
#include "Rte/Point/Container.h"
#include "Rte/Point/Model/Base.h"
#include "Rte/Point/Controller/Base.h"
#include "Rte/Point/Controller/Container.h"
#include "Rte/Point/Viewer/Composer.h"
#include "Rte/Point/Viewer/Container.h"
#include "Tuples.h"


/*------------------------- POINTS ------------------------------------------*/
/** Concrete Point: BAR1
 */
class PointBar1: public Rte::Point::Basic<2>
{
public:
    ///
    TupleFoo1   m_fields1;
    ///
    TupleFoo3   m_fields2;

public:
    /// Constructor
    PointBar1( void )
        {
        registerTuple( 0, m_fields1 );
        registerTuple( 1, m_fields2 );
        }

};
        
/** Concrete Point: BAR2 (Container Point that hold 4 instances of the Foo2 tuple)
 */
class PointBar2: public Rte::Point::Container<TupleFoo2,4>
{
public:
    /// Constructor
    PointBar2( void ){}

};


/*------------------------- MODEL POINTS ------------------------------------*/
/** Concrete Model Point: BAR1
 */
class ModelBar1: public PointBar1,
                 public Rte::Point::Model::Base
{
public:
    /// Constructor
    ModelBar1( Cpl::Itc::PostApi& myMbox )
        :Rte::Point::Model::Base(*this, myMbox)
            {
            }
};


/** Concrete Model Point: BAR2
 */
class ModelBar2: public PointBar2,
                 public Rte::Point::Model::Base
{
public:
    /// Constructor
    ModelBar2( Cpl::Itc::PostApi& myMbox )
        :Rte::Point::Model::Base(*this,myMbox)
            {
            }
};



/*------------------------- CONTROLLER POINTS -------------------------------*/
/** Concrete Controller Point: BAR1
 */
class ControllerBar1: public PointBar1,
                      public Rte::Point::Controller::Base
{
public:
    /// Constructor
    ControllerBar1( ModelBar1& modelPoint )
        :Rte::Point::Controller::Base(*this, modelPoint)
            {
            }

};


/** Concrete Controller Point: BAR2
 */
class ControllerBar2: public PointBar2,
                      public Rte::Point::Controller::Container
{
public:
    /// Constructor
    ControllerBar2( ModelBar2& modelPoint )
        :Rte::Point::Controller::Container(*this, modelPoint)
            {
            }

};


/*------------------------- VIEWER POINTS -----------------------------------*/
/** Concrete Viewer Point: BAR1
 */
template <class CONTEXT>
class ViewerBar1: public PointBar1,
                  public Rte::Point::Viewer::Composer<CONTEXT>
{
public:
    /// Constructor
    ViewerBar1( CONTEXT&                                                                    context,
                typename Rte::Point::Viewer::Composer<CONTEXT>::ChangeNotificationFunc_T    contextChangedCb,
                typename Rte::Point::Viewer::Composer<CONTEXT>::StoppedNotificationFunc_T   contextStoppedCb,
                ModelBar1&                                                                  modelPoint,
                Cpl::Itc::PostApi&                                                          viewerMbox 
              )
    :Rte::Point::Viewer::Composer<CONTEXT>::Composer(*this, context, contextChangedCb, contextStoppedCb, modelPoint, viewerMbox)
        {}
};


/** Concrete Viewer Point: BAR2
 */
template <class CONTEXT>
class ViewerBar2: public PointBar2,
                  public Rte::Point::Viewer::Container<CONTEXT>
{
public:
    /// Constructor
    ViewerBar2( CONTEXT&                                                                    context,
                typename Rte::Point::Viewer::Container<CONTEXT>::ChangeNotificationFunc_T   contextChangedCb,
                typename Rte::Point::Viewer::Container<CONTEXT>::StoppedNotificationFunc_T  contextStoppedCb,
                ModelBar2&                                                                  modelPoint,
                Cpl::Itc::PostApi&                                                          viewerMbox 
              )
    :Rte::Point::Viewer::Container<CONTEXT>::Container(*this, context, contextChangedCb, contextStoppedCb, modelPoint, viewerMbox)
        {}
};


#endif 