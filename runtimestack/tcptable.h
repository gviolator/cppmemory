#pragma once

#ifdef _WIN32
#include <iphlpapi.h>
#include <winsock.h>
#endif


using TcpEntryHandle = MIB_TCPROW;

enum class TcpState
{
	Closed,
	Listen,
	Unknown

};

template<typename T>
inline decltype(auto) operator << (std::basic_ostream<T>& output, TcpState state)
{
	if (state == TcpState::Closed)
	{
		output << "closed";
	}
	else if (state == TcpState::Listen)
	{
		output << "listen";
	}
	else
	{
		output << "unknown";
	}

	return output;
}


struct TcpTableEntry
{
	unsigned localAddr = 0;
	unsigned localPort = 0;
	unsigned remoteAddr = 0;
	unsigned remotePort = 0;
	TcpState state = TcpState::Unknown;

	TcpTableEntry();

	TcpTableEntry(const TcpEntryHandle& handle);

};




void getTcpTableSnapshot(void (*callback)(const TcpEntryHandle* entries, size_t count, void*) noexcept, void*);
