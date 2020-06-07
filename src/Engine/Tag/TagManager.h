//
// Created by lopea on 5/29/20.
//

#ifndef GIGAENGINE_TAGMANAGER_H
#define GIGAENGINE_TAGMANAGER_H

#include <rttr/type>
#include <unordered_map>
#include "TagList.h"

class EntityList;

class TagManager
{
public:
    template<typename T>
    static bool HasTag(Entity entity);

    template<typename T>
    static void AddTag(Entity entity);

    template<typename T>
    static void RemoveTag(Entity entity);

    template<typename T>
    static void RemoveTags(EntityList& list);

    template<typename T>
    static void  ClearAllTagsOfType();

    static void Initialize();

    static void Shutdown();

private:
    static std::unordered_map<rttr::type, GenericTagList *> tags_;

    template<typename T>
    static TagList<T> *GetList();

    friend class EntityList;

};
inline std::unordered_map<rttr::type, GenericTagList *> TagManager::tags_;
inline void TagManager::Shutdown()
{
  for (auto &list : tags_)
  {
    delete list.second;
    list.second = nullptr;
  }
}

template<typename T>
bool TagManager::HasTag(Entity entity)
{
  TagList<T>* list = GetList<T>();
  if(list)
  {
    return list->HasTag(entity);
  }
  return false;
}

template<typename T>
void TagManager::AddTag(Entity entity)
{
  TagList<T>* list = GetList<T>();
  if(!list)
  {
    list = new TagList<T>();
    tags_.insert(std::pair<rttr::type, GenericTagList*>(rttr::type::get<T>(), list));
  }
  list->AddTag(entity);
}

template<typename T>
void TagManager::RemoveTag(Entity entity)
{
  TagList<T>* list = GetList<T>();
  if(list)
  {
    list->RemoveTag(entity);
  }
}

template<typename T>
void TagManager::RemoveTags(EntityList& list)
{
  TagList<T>* l = GetList<T>();
  if(!l)
    return;

  l.RemoveTags(list);

}

template<typename T>
void TagManager::ClearAllTagsOfType()
{
  TagList<T>* list = GetList<T>();
  if(list)
  {
    list->clear();
  }
}

inline void TagManager::Initialize()
{
}

template<typename T>
TagList<T> *TagManager::GetList()
{
  auto it = tags_.find(rttr::type::get<T>());
  if(it != tags_.end())
    return static_cast<TagList<T> *>(it->second);

  return nullptr;
}


#endif //GIGAENGINE_TAGMANAGER_H
