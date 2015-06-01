#ifndef Rte_Tuple_Basic_h_
#define Rte_Tuple_Basic_h_
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


#include "Rte/Tuple/Base.h"
#include "Cpl/System/FatalError.h"



///
namespace Rte { namespace Tuple {


/** This template class provides the infrastructure managing the N Elements
    in the Tuple (and managing them as abstract Element Type). The template 
    parameter 'N' is the number of Elements in the concrete Tuple.
 */
template<int N>
class Basic: public Base
{
protected:
    /// Pointers to all of my contained Elements
    Rte::Element::Api*  m_elementPtrs[N];


protected:
    /// Constructor
    Basic( void );


protected:
    /** This method attaches/registers the element into the array of elements at
        the specified index.
     */
    virtual void setElementIndex( Rte::Element::Api& element, unsigned idx );


public: 
    /// See Rte::Tuple::Api
    unsigned getNumElements(void) const;

    /// See Rte::Tuple::Api
    Rte::Element::Api& getElement( unsigned elementIdx ) const;
};


/////////////////////////////////////////////////////////////////////////////
//                  INLINE IMPLEMENTAION
/////////////////////////////////////////////////////////////////////////////
template<int N>
Rte::Tuple::Basic<N>::Basic( void )
:Base()
    {
    // Initialize element array (for error trapping)
    unsigned i;
    for(i=0; i<N; i++)
        {
        m_elementPtrs[i] = 0;
        }
    }

/////////////////
template<int N>
void Rte::Tuple::Basic<N>::setElementIndex( Rte::Element::Api& element, unsigned idx )
    {
    if ( idx >= N )
        {
        Cpl::System::FatalError::logf( "Rte::Tuple::Basic::setElementIndex - out-of-range index (maxIdx=%u, requestIdx=%u)", N, idx );
        }

    m_elementPtrs[idx] = &element;
    }

/////////////////
template<int N>
unsigned Rte::Tuple::Basic<N>::getNumElements( void ) const
    {
    return N;
    }

template<int N>
Rte::Element::Api& Rte::Tuple::Basic<N>::getElement( unsigned elementIdx ) const
    {
    if ( elementIdx >= N )
        {
        Cpl::System::FatalError::logf( "Rte::Tuple::Basic::getElement - out-of-range index (maxIdx=%u, requestIdx=%u)", N, elementIdx );
        }

    Rte::Element::Api* ptr = m_elementPtrs[elementIdx];
    if ( !ptr )
        {
        Cpl::System::FatalError::logf( "Rte::Tuple::Basic::getElement - un-initialized element index (%u)", elementIdx );
        }

    return *ptr;
    }


};      // end namespaces
};
#endif  // end header latch