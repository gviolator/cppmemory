#include "pch.h"
#include "tcptable.h"
#include <cppmem/rtstack.h>

#include <iphlpapi.h>


namespace {

TcpState makeTcpState(MIB_TCP_STATE value)
{
	if (value == MIB_TCP_STATE_CLOSED)
	{
		return TcpState::Closed;
	}
	else if (value == MIB_TCP_STATE_LISTEN)
	{
		return TcpState::Listen;
	}

	return TcpState::Unknown;
}

}


void getTcpTableSnapshot(void (*callback)(const MIB_TCPROW*, size_t, void*) noexcept, void* callbackData)
{
	constexpr size_t InitialEntriesSize = 100;
	ULONG size = sizeof(MIB_TCPTABLE) + sizeof(MIB_TCPROW) * InitialEntriesSize;

	do
	{
		rtstack();

		MIB_TCPTABLE* table = reinterpret_cast<MIB_TCPTABLE*>(RtStackGuard::allocator()->alloc(static_cast<size_t>(size), alignof(MIB_TCPTABLE)));

		const auto err = GetTcpTable(table, &size, TRUE);
		if (err == NO_ERROR)
		{
			callback(table->table, static_cast<size_t>(table->dwNumEntries), callbackData);
			break;
		}
		else if (err != ERROR_INSUFFICIENT_BUFFER)
		{
			callback(nullptr, 0, callbackData);
			break;
		}
	} while (true);
}


//-----------------------------------------------------------------------------

TcpTableEntry::TcpTableEntry() = default;

TcpTableEntry::TcpTableEntry(const MIB_TCPROW & handle)
	: localAddr(static_cast<unsigned>(handle.dwLocalAddr))
	, localPort(static_cast<unsigned>(htons(LOWORD(handle.dwLocalPort))))
	, remoteAddr(static_cast<unsigned>(handle.dwRemoteAddr))
	, remotePort(static_cast<unsigned>(htons(LOWORD(handle.dwRemotePort))))
	, state(makeTcpState(handle.State))
{
}



