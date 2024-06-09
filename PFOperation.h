#pragma once
#include "PartialFunction.h"


class PFOperation: public PartialFunction   //does not override evaluate, clone and so on; only collection management
{
public:
    PFOperation() = default;  
    PFOperation(const PartialFunction** newFunctions, uint16_t size);
    PFOperation(PartialFunction**&& newFunctions, uint16_t size);  //just data stealing
    PFOperation(const PFOperation& other);
    PFOperation& operator=(const PFOperation& other);
    PFOperation(PFOperation&& other) noexcept;
    PFOperation& operator=(PFOperation&& other) noexcept;
    ~PFOperation();

protected:
    PartialFunction** functions = nullptr;
    size_t size = 0;
    size_t capacity = 0;

private:
    void free();
    void copyFrom(const PFOperation& other);
    void moveFrom(PFOperation&& other);
    void resize(size_t newCapacity);
};

