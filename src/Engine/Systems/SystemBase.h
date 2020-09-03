//
// Created by javier on 5/3/2020.
//

#ifndef _SYSTEMBASE_H_
#define _SYSTEMBASE_H_

/*!
 * Base for all systems. A system must derive from this class in for the system to work
 */
class SystemBase
{
 public:
  virtual void Update() = 0;
  virtual void Init(){};
  virtual void Exit(){};
};

#endif //_SYSTEMBASE_H_
