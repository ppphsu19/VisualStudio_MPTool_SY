#ifndef _FLASHID_H_
#define _FLASHID_H_

#include <exception>
#include <cstdint>
#include <vector>

class FlashIdTooLongExpection : public std::exception
{

};

class FlashId
{
public:
	FlashId(std::initializer_list<uint8_t> list) :
		_id{ list }
	{
		if (static_cast<int32_t>(list.size()) > _maxIdLength)
			throw FlashIdTooLongExpection{};

		if (static_cast<int32_t>(_id.size()) < _maxIdLength)
			PadZeros(&_id, _maxIdLength - _id.size());
	}

	int32_t Size() const { return _id.size(); }

	bool Equals(const FlashId& another) const { return _id == another._id; }

protected:
	const static int32_t _maxIdLength;
	std::vector<uint8_t> _id;

	void PadZeros(std::vector<uint8_t>* vec, int numberOfZero)
	{
		vec->insert(vec->end(), numberOfZero, 0);
	}
};
const int32_t FlashId::_maxIdLength{ 8 };

#endif//_FLASHID_H_
