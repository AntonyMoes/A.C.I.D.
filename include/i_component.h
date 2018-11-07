#ifndef ACID_INCLUDE_I_COMPONENT_H_
#define ACID_INCLUDE_I_COMPONENT_H_


#include <i_observable.h>

class IComponent : public IObservable<IComponent> {
  public:
    explicit IComponent();
    virtual ~IComponent();
    void set_parent_id(size_t _parent_id);
    size_t get_parent_id();
  protected:
    size_t parent_id;
};

#endif  // ACID_INCLUDE_I_COMPONENT_H_
