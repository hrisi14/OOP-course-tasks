#include "PFOperation.h"

void PFOperation::free()
{
    for (size_t i = 0; i < size; i++)
    {
        delete functions[i];
   }
    delete[] functions;
    size = 0;
    capacity = 0;
}

void PFOperation::copyFrom(const PFOperation& other)
{
    this->size = other.size;
    this->capacity = other.capacity;

    for (size_t i = 0; i < other.size; i++)
    {
        functions[i] = other.functions[i]->clone();
    }
}

void PFOperation::moveFrom(PFOperation&& other)
{
    functions = other.functions;
    size = other.size;
    capacity = other.capacity;

    other.functions = nullptr;
    other.capacity = 0;
    other.size = 0;
}

void PFOperation::resize(size_t newCapacity)
{
    capacity = newCapacity;
    PartialFunction** newData = new PartialFunction * [capacity];

    for (size_t i = 0; i < size; i++)
    {
        newData[i] = functions[i];
    }
    delete[] functions;
    functions = newData;
}

PFOperation::PFOperation(const PartialFunction** newFunctions, uint16_t size)
    {
    this->size = size;
    this->capacity = size;

    functions = new PartialFunction * [capacity];

    for (size_t i = 0; i < size; i++)
    {
        functions[i] = newFunctions[i]->clone();
    }
    }

PFOperation::PFOperation(PartialFunction**&& newFunctions, uint16_t size) //just data stealing
{
    functions = newFunctions;
    size = size;
}

PFOperation::PFOperation(const PFOperation& other)
    {
    copyFrom(other);
    }
    PFOperation& PFOperation::operator=(const PFOperation& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
    }
    PFOperation::PFOperation(PFOperation&& other) noexcept
    {
        moveFrom(std::move(other));
    }
    PFOperation& PFOperation::operator=(PFOperation&& other)  noexcept
    {
        if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }
    PFOperation::~PFOperation()
    {
        free();
    }
