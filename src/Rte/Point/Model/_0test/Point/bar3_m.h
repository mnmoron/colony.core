#ifndef Point_ModelBar3_h_
#define Point_ModelBar3_h_
/*----------------------------------------------------------------------------- 
* This file is part of the Shift-Right Open Repository.  The Repository is an   
* open source project with a BSD type of licensing agreement.  See the license  
* agreement (license.txt) in the root directory or on the Internet at           
* http://www.shift-right.com/openrepo/license.htm                               
*                                                                               
* Copyright (c) 2001-2011 John T. Taylor                                        
*                                                                               
* Redistributions of the source code must retain the above copyright notice.    
*----------------------------------------------------------------------------*/ 

#include "Rte/Point/Model/Base.h"
#include "Rte/Point/Model/_0test/Point/Bar3.h"

///
namespace Point {


/** Concrete Model Point: BAR3
 */
class ModelBar3: public Bar3,
                 public Rte::Point::Model::Base
{
public:
    /// Constructor
    ModelBar3( Cpl::Itc::PostApi& myMbox ):Rte::Point::Model::Base(*this,myMbox){}
};


};
#endif 