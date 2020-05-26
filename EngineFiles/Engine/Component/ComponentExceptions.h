//
// Created by javier on 5/4/2020.
//

#ifndef GIGAENGINE_COMPONENTEXCEPTIONS_H
#define GIGAENGINE_COMPONENTEXCEPTIONS_H

#include <exception>
#include <rttr/type>

/*!
 * Custom Exception that gets thrown when the component cannot find component with the entity given.
 */
class ComponentNotFoundException : public std::exception
{
public:
    inline explicit ComponentNotFoundException(const rttr::type& type) : std::exception(), type_(type){} //!< constructor for the exception
    rttr::type type_; //!< the type of component that caused the exeption
    ComponentNotFoundException() = delete;
};

/*!
 * Custom Exception that gets thrown when the type given is not derived from component
 */
class TypeNotComponentException : public std::exception
{
public:
    inline explicit TypeNotComponentException(const rttr::type& type) : std::exception(), type_(type){} //!< constructor for the exception
    rttr::type type_; //!< the type of component that caused the exeption
    TypeNotComponentException() = delete;
};
#endif //GIGAENGINE_COMPONENTEXCEPTIONS_H
