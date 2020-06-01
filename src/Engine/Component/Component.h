//
// Created by javier on 5/3/2020.
//

#ifndef _COMPONENTBASE_H_
#define _COMPONENTBASE_H_

#include <rttr/type>

typedef uint64_t Entity;

/*!
 * Macro that tells Reflection System (RTTR) to detect that the derived class is a Component.
 */
#define SET_AS_COMPONENT(Type) explicit Type(Entity t) : Component(t){} \
                               Type() = default; \
                               RTTR_ENABLE(Component)\
                               public:

/*!
 * Macro that tells Reflection System (RTTR) to detect that the derived class is derived from component.
 */
#define SET_AS_DERIVED_COMPONENT(Type, DerivedType) explicit Type(Entity t) : Component(t){} \
                               RTTR_ENABLE(DerivedType)

#define ALLOW_COMPONENT_WRITE(WriteComponentType)

/*!
 * Component base for all component types.
 * All Component must derive from this class
 */
struct Component
{
    explicit Component(Entity entity) : entity_(entity){}
    Component() = default;
    Entity GetEntity() const { return entity_; }
RTTR_ENABLE()
private:
    Entity entity_;
};





#endif //_COMPONENTBASE_H_
