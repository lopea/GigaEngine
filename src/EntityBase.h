//
// Created by javier on 5/3/2020.
//

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <rttr/type>


class Entity
{
public:
    Entity();

    explicit Entity(unsigned int id);


    bool HasType(rttr::type &type) const;

    template<typename T>
    T& GetComponent();

    template<typename T>
    T &AddComponent();

    [[nodiscard]] unsigned int getID() const;

    bool operator==(unsigned int id) const;
    bool operator==(const Entity& entity);
    bool operator< (const Entity& entity) const;
    friend bool operator==(unsigned int id_, const Entity& entity);
private:
    std::vector<rttr::type> types_; //!< store all types of components that pertain to this entity
    unsigned int id_;               //!< identifier for the type
};



#endif //_ENTITY_H_
