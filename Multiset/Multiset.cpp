#include "Multiset.h"

const short Multiset::BITS_IN_BYTE = 8;

Multiset::Multiset(size_t newMaxNumber, size_t newK): maxNumber(newMaxNumber)
{
	if (newK >= 1 && newK <= BITS_IN_BYTE)
	{
		k = newK;
		maxOccurrencesOfNumber = (1 << k) - 1;
		numbersInBucket = sizeof(Multiset::Bucket) * BITS_IN_BYTE / k;		

		bucketsCount = getBucket(maxNumber) + 1;
		buckets = new Bucket[bucketsCount];

		for (size_t i = 0; i < bucketsCount; i++)
		{
			buckets[i] = 0;
		}
	}
}
Multiset::Multiset(const Multiset& other)
{
	copyFrom(other);
}
Multiset& Multiset::operator=(const Multiset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Multiset::Multiset(Multiset&& other) noexcept
{
	moveFrom(std::move(other));
}
Multiset& Multiset::operator=(Multiset&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Multiset::~Multiset()
{
	free();
}

size_t Multiset::getNumberCount(size_t num) const
{
	if (num >= maxNumber) 
	{
		return 0;
	}

	return (buckets[getBucket(num)] & getMaskWithMaxCount(num)) >> getIndexInBucket(num);
}

size_t Multiset::getMaxNumber() const
{
	return maxNumber;
}

void Multiset::printNumber(size_t number, size_t numOccurrences) const
{
	while (numOccurrences--)
	{
		std::cout << number << ' ';
	}
}

void Multiset::print() const
{
	std::cout << "{ ";
	for (size_t i = 0; i < maxNumber; ++i) 
	{
		size_t numOccurrences = getNumberCount(i);
		printNumber(i, numOccurrences);		
	}
	std::cout << " }";
}

void Multiset::printBucket(size_t bucketIndex) const
{
	if (bucketIndex >= bucketsCount)
	{
		throw std::exception("Error! Invalid index!");
	}

	for (uint8_t i = 128; i >= 1; i >>= 1)
	{
		if (buckets[bucketIndex] & i)
		{
			std::cout << 1;
		}
		else
		{
			std::cout << 0;
		}
	}
}

void Multiset::memoryRepresentationPrint() const
{
	for (size_t i = 0; i < bucketsCount; i++)
	{
		printBucket(i);
		std::cout << std::endl;
	}
}

void Multiset::free()
{
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = 0;
	maxNumber = 0;
	maxOccurrencesOfNumber = 0;
	k = 0;
}

void Multiset::copyFrom(const Multiset& other)
{
	bucketsCount = other.bucketsCount;
	maxNumber = other.maxNumber;
	buckets = new Bucket[bucketsCount];
	maxOccurrencesOfNumber = other.maxOccurrencesOfNumber;
	numbersInBucket = other.numbersInBucket;
	k = other.k; 

	for (size_t i = 0; i < bucketsCount; i++)
	{
		buckets[i] = other.buckets[i];
	}
}

void Multiset::moveFrom(Multiset&& other)
{
	this->buckets = other.buckets;
	this->bucketsCount = other.bucketsCount;
	this->maxNumber = other.maxNumber;
	this->k = other.k;
	this->maxOccurrencesOfNumber = other.maxOccurrencesOfNumber;
	this->numbersInBucket = other.numbersInBucket;

	other.buckets = nullptr;
	other.bucketsCount = 0;
	other.maxNumber = 0;
	other.k = 0;
	other.maxOccurrencesOfNumber = 0;
	other.numbersInBucket = 0;
}

void Multiset::replaceNumOccurrences(size_t num, size_t numOccurrences) 
{
	size_t bucketIdex = getBucket(num);

	buckets[bucketIdex] &= ~getMaskWithMaxCount(num);
	buckets[bucketIdex] |= (numOccurrences << getIndexInBucket(num));
}


bool Multiset::addNumber(size_t newN)
{
	size_t numOccurrences = getNumberCount(newN);
	if (newN >= maxNumber || numOccurrences == maxOccurrencesOfNumber)
	{
		return false;
	}

	++numOccurrences;
	replaceNumOccurrences(newN, numOccurrences);
	return true;
}

bool Multiset::removeNumber(size_t number)
{
	int numOccurrences = getNumberCount(number);
	if (numOccurrences == 0)
	{
		return false;
	}

	--numOccurrences;
	replaceNumOccurrences(number, numOccurrences);
	return true;
}

size_t Multiset::getBucket(size_t num) const
{
	return num / numbersInBucket;
}

size_t Multiset::getMaskWithMaxCount(size_t num) const 
{
	return maxOccurrencesOfNumber << getIndexInBucket(num);
}

size_t Multiset::getIndexInBucket(size_t num) const
{
	return k * (numbersInBucket - 1 - num % numbersInBucket);
}

void Multiset::saveToBinaryFile(std::ofstream& ofs)
{
	ofs.write((const char*)&bucketsCount, sizeof(size_t));
	ofs.write((const char*)buckets, sizeof(Bucket) * bucketsCount);
	ofs.write((const char*)&maxNumber, sizeof(size_t));
	ofs.write((const char*)&k, sizeof(short));	
}

bool Multiset::saveToBinaryFile(const char* fileName)
{
	if (!fileName)
	{
		return false;
	}
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	if (!ofs.is_open())
	{
		return false;
	}
	saveToBinaryFile(ofs);
	ofs.close();
	return true;
}

bool Multiset::readFromBinaryFile(const char* fileName)
{
	if (!fileName)
	{
		return false;
	}
	std::ifstream ifs(fileName, std::ios::in|std::ios::binary);
	if (!ifs.is_open())
	{
		return false;
	}
	readFromBinaryFile(ifs);
	ifs.close();
	return true;
}

void Multiset::readFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&bucketsCount, sizeof(size_t));
	buckets = new Bucket[bucketsCount];
	ifs.read((char*)buckets, sizeof(Bucket) * bucketsCount);
	ifs.read((char*)&maxNumber, sizeof(size_t));
	ifs.read((char*)&k, sizeof(short));
	maxOccurrencesOfNumber = (1 << k) - 1;
	numbersInBucket = sizeof(Bucket) * BITS_IN_BYTE / k;
}

Multiset unionOfSets(const Multiset& lhs, const Multiset& rhs)
{
	size_t resultMaxNumber = std::max(lhs.maxNumber, rhs.maxNumber);
	short resultK = std::max(lhs.k, rhs.k);
	Multiset unitedResult(resultMaxNumber, resultK);

	for (size_t i = 0; i < resultMaxNumber; i++)
	{
		size_t lhsCount = lhs.getNumberCount(i);
		size_t rhsCount = rhs.getNumberCount(i);
		size_t sumCount = lhsCount + rhsCount;
		
		size_t resultCount = sumCount < unitedResult.maxOccurrencesOfNumber ? sumCount : unitedResult.maxOccurrencesOfNumber;
		unitedResult.replaceNumOccurrences(i, resultCount);
    }
	return unitedResult;
}

Multiset intersectionOfSets(const Multiset& lhs, const Multiset& rhs)
{
	size_t resultMaxNumber = std::min(lhs.maxNumber, rhs.maxNumber);
	short resultK = std::min(lhs.k, rhs.k);
	Multiset intersectedResult(resultMaxNumber, resultK);

	for (size_t i = 0; i < resultMaxNumber; i++)
	{
		intersectedResult.replaceNumOccurrences(i, std::min(lhs.getNumberCount(i), rhs.getNumberCount(i)));
	}
	return intersectedResult;
}

Multiset setComplement(const Multiset& set)
{
	Multiset result(set);
	for (size_t i = 0; i<set.maxNumber; i++)
	{
		size_t numCount = set.getNumberCount(i);  //p
		size_t newCount = set.maxOccurrencesOfNumber - numCount;   //2^k - 1 - p
		result.replaceNumOccurrences(i, newCount);
	}
	return result;
}

Multiset setDifference(const Multiset& lhs, const Multiset& rhs)
{
	Multiset result(lhs);
	Multiset toRemove = intersectionOfSets (lhs, rhs);

	for (size_t i = 0; i < toRemove.maxNumber; i++)
	{
		size_t lhsCount = lhs.getNumberCount(i);
		size_t toRemoveCount = toRemove.getNumberCount(i);
		result.replaceNumOccurrences(i, (lhsCount-toRemoveCount));		
	}
	return result;
}