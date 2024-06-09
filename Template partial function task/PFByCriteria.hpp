#include "PartialFunction.h"

template <typename T>
class PFByCriteria: public PartialFunction 
{
public:
	PFByCriteria(const T& initCriteria);
	PFByCriteria(T&& cr);
	bool isDefined(int x) const override;
	int evaluate(int x) const override;
	PartialFunction* clone() const override;

private:
	T criteria;
};


template <typename T>
PFByCriteria<T>::PFByCriteria(const T& initCriteria): criteria(initCriteria)
{}

template <typename T>
PFByCriteria<T>::PFByCriteria(T&& initCriteria) : criteria(std::move(initCriteria))
{}

template <typename T>
bool PFByCriteria<T>::isDefined(int x) const 
{
	return criteria(x).getFirst();
}

template <typename T>
int PFByCriteria<T>::evaluate(int x) const
{
	if (!isDefined(x))
	{
		throw std::exception("Error! The function is not defined in this point!");
	}
	return criteria(x).getSecond();
}

template <typename T>
PartialFunction* PFByCriteria<T>::clone() const
{
	return new PFByCriteria(*this);
}