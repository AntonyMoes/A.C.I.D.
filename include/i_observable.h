#ifndef ACID_INCLUDE_I_OBSERVABLE_H_
#define ACID_INCLUDE_I_OBSERVABLE_H_


#include <vector>
#include <i_observer.h>

template <class T>
class IObservable {
  public:
	IObservable();
	virtual ~IObservable();
	virtual void update() = 0;
	void add_observer(IObserver<T>* observer);
  private:
    std::vector<IObserver<T>*> observers;
};

#endif  // ACID_INCLUDE_I_OBSERVABLE_H_
