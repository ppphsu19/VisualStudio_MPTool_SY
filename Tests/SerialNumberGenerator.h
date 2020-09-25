#ifndef _SERIALNUMBERGENERATOR_H_
#define _SERIALNUMBERGENERATOR_H_

class InconsistentLengthException : public std::exception
{
public:
	InconsistentLengthException()
	{
	}

	char const* what() const override
	{
		return "SerialNumberBegin and SerialNumberEnd and SerialNumberMask must have same length.";
	}
};

class OffsetOutOfRangeException : public std::exception
{
public:
	OffsetOutOfRangeException(int32_t offset, int32_t maxOffset) :
		_offset{ offset },
		_maxOffset{ maxOffset }
	{
		_message = "Offset " + std::to_string(_offset) + " is greater than total amout of available SerialNumber which is " + std::to_string(_maxOffset);
	}

	char const* what() const override
	{
		return _message.c_str();
	}

protected:
	int32_t _offset;
	int32_t _maxOffset;
	std::string _message;
};

class MaskSettingErrorException : public std::exception
{
public:
	MaskSettingErrorException() {}

	char const* what() const override
	{
		return "There is a different character between SerialNumberBegin and SerialNumberEnd, and it is not specified at SerialNumberMask.";
	}
};

class NoAvailableSerialNumberException : public std::exception
{
public:
	NoAvailableSerialNumberException() {}

	char const* what() const override
	{
		return "SerialNumber(s) are all consumed.";
	}
};

// Rule 1: Length of SerialNumberBegin and SerialNumberEnd and SerialNumberMask must be the same.

// Rule 2: When different character between SerialNumberBegin and SerialNumberEnd at some index is found,
//         the character at the same index in SerialNumberMask must be mask symbol('#').

// Rule 3: Whenever getSerialNumber is called, returned serial number is increamented.

class SerialNumberGenerator
{
public:
	SerialNumberGenerator(const std::string& begin, const std::string& end, const std::string& mask, int32_t offset = 0) :
		_begin{ begin },
		_end{ end },
		_mask{ mask },
		_offset{ offset },
		_maskSymbolCount{ 0 }
	{
		if (begin.size() != end.size() || end.size() != mask.size())
			throw InconsistentLengthException{};

		std::string beginStr, endStr;
		for (int i = 0; i < static_cast<int>(mask.size()); i++)
		{
			if (mask[i] == _maskSymbol)
			{
				beginStr += _begin[i];
				endStr += _end[i];
				_maskSymbolCount++;
			}
			else
			{
				if (_begin[i] != _end[i])
					throw MaskSettingErrorException{};
			}
		}

		_beginNum = std::stoi(beginStr);
		_endNum = std::stoi(endStr);
		_total = std::abs(_beginNum - _endNum) + 1;

		if (std::abs(_offset) > _total)
			throw OffsetOutOfRangeException(std::abs(_offset), _total);
	}

	std::string GetSerialNumber()
	{
		int32_t currentSerialNum = _beginNum + _offset;
		AdjustOffset();

		std::string serialNumberOnly = std::to_string(currentSerialNum);
		std::string serialNumberZeroPadded = std::string(_maskSymbolCount - serialNumberOnly.size(), '0') + serialNumberOnly;
		std::string finalSerialNumber;

		int index = 0;
		for (int i = 0; i < static_cast<int>(_mask.size()); i++)
		{
			if (_mask[i] == _maskSymbol)
				finalSerialNumber += serialNumberZeroPadded[index++];
			else
				finalSerialNumber += _mask[i];
		}

		return finalSerialNumber;
	}

	int GetRemainingSerialNumberCount() const
	{
		return _total - std::abs(_offset);
	}

protected:
	std::string _begin;       // SN00001
	std::string _end;         // SN00200
	std::string _mask;        // SN00###
	int32_t _offset;

	int32_t _beginNum;        // 1
	int32_t _endNum;          // 200
	int32_t _total;           // 200
	int32_t _maskSymbolCount; // 3
	const static char _maskSymbol;

	void AdjustOffset()
	{
		int32_t newOffset;
		if (_endNum > _beginNum)
			newOffset = _offset + 1;
		else
			newOffset = _offset - 1;

		if (std::abs(newOffset) > _total)
			throw NoAvailableSerialNumberException{};

		_offset = newOffset;
	}
};
const char SerialNumberGenerator::_maskSymbol{ '#' };

#endif//_SERIALNUMBERGENERATOR_H_
