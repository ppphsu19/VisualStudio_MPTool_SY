#ifndef _MPDISK_H_
#define _MPDISK_H_

#include <string>

class MPDisk
{
public:
	std::string GetType() const;
	int GetCapacityInGB() const;
	std::string GetFWMode() const;
	int GetPhysicalIndex() const;
	std::string GetBridgeSerialNumber() const;

protected:

};

#endif//_MPDISK_H_
