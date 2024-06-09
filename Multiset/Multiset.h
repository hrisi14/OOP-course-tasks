#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

class Multiset
{
    using Bucket = uint8_t;
    static const short BITS_IN_BYTE;

    short maxOccurrencesOfNumber=1;    
    short numbersInBucket= sizeof(Bucket) * BITS_IN_BYTE; 
    short k=1; //bits per number

    Bucket* buckets = nullptr;
    size_t bucketsCount = 0;
    size_t maxNumber = 0;    

    void free();
    void copyFrom(const Multiset& other);
    void moveFrom(Multiset&& other);
    bool addNumber(size_t newN);
    bool removeNumber(size_t number);
    void replaceNumOccurrences(size_t num, size_t numOccurrences);

    size_t getBucket(size_t num) const;      //these three functions are inspired by SI_OOP_Practicum/pract-06
    size_t getMaskWithMaxCount(size_t num) const; 
    size_t getIndexInBucket(size_t num) const;      
    
public:
    Multiset()=default; 
    Multiset(size_t newMaxNumber, size_t newK); 

    Multiset(const Multiset& other);
    Multiset& operator=(const Multiset& other);
    Multiset(Multiset&& other) noexcept;
    Multiset& operator=(Multiset&& other) noexcept;   
    ~Multiset();

    size_t getNumberCount(size_t num) const;
    size_t getMaxNumber() const;

    void printNumber(size_t number, size_t numOccurrences) const;
    void print() const;
    void printBucket(size_t bucketIndex) const;    
    void memoryRepresentationPrint() const;

    void saveToBinaryFile(std::ofstream& ofs);
    bool saveToBinaryFile(const char* fileName);

    bool readFromBinaryFile(const char* fileName);
    void readFromBinaryFile(std::ifstream& ifs);

    friend Multiset unionOfSets(const Multiset& lhs, const Multiset& rhs);
    friend Multiset intersectionOfSets(const Multiset& lhs, const Multiset& rhs);
    friend Multiset setComplement(const Multiset& set);    
    friend Multiset setDifference(const Multiset& lhs, const Multiset& rhs);
};



