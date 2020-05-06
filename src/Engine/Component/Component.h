//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTBASE_H_
#define _COMPONENTBASE_H_
#include <rttr/type>

#define SET_AS_COMPONENT RTTR_ENABLE(Component)

/*!
 * Component base for all component types.
 * All Component must derive from this class
 */
struct Component {RTTR_ENABLE()};

#endif //_COMPONENTBASE_H_
