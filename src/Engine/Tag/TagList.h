//
// Created by lopea on 5/29/20.
//

#ifndef GIGAENGINE_TAGLIST_H
#define GIGAENGINE_TAGLIST_H

#include <cstdint>
#include <vector>
#include <deque>
#include <set>

typedef uint64_t Entity;

class GenericTagList
{
public:
  virtual ~GenericTagList() = default;
};

template<typename T>
class TagList : public GenericTagList
{
public:
    void AddTag(Entity entity);

    bool HasTag(Entity entity) const;

    void RemoveTag(Entity entity);

    void RemoveTags(std::vector<Entity>& entities);

    void clear();

    bool empty() const;

    std::vector<Entity> GetOverlappingEntities(const std::vector<Entity>& reference);

    ~TagList();
private:
    std::deque<Entity> entities_;
    bool sorted_ = false;

};

template<typename T>
void TagList<T>::AddTag(Entity entity)
{
#pragma omp critical
  {
      entities_.push_back(entity);
      sorted_ = false;
  }
}


template<typename T>
TagList<T>::~TagList()
{
  clear();
}

template<typename T>
bool TagList<T>::HasTag(Entity entity) const
{
  return std::find(entities_.begin(),entities_.end(),entity) != entities_.end();
}

template<typename T>
void TagList<T>::RemoveTag(Entity entity)
{
  auto it = std::find(entities_.begin(),entities_.end(), entity);

  if (it != entities_.end())
  {
    entities_.erase(it);
  }
}

template<typename T>
void TagList<T>::clear()
{
  entities_.clear();
}

template<typename T>
bool TagList<T>::empty() const
{
  return entities_.empty();
}

template<typename T>
std::vector<Entity> TagList<T>::GetOverlappingEntities(const std::vector<Entity> &reference)
{
  std::vector<Entity> result;

  if(!sorted_)
  {
    std::sort(entities_.begin(),entities_.end());
    sorted_ = true;
  }

  std::set_intersection(entities_.begin(), entities_.end(),reference.begin(),reference.end(), std::back_inserter(result));

  return result;
}

template<typename T>
void TagList<T>::RemoveTags(std::vector<Entity> &entities)
{
  for(Entity entity : entities)
  {
    RemoveTag(entities);
  }
}




#endif //GIGAENGINE_TAGLIST_H
