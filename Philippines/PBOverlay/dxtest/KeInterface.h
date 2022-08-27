#include "stdafx.h"

#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _KERNEL_READ_REQUEST
{
	ULONG ProcessId;
	ULONGLONG Address;
	ULONGLONG Buffer;
	ULONGLONG Size;

} KERNEL_READ_REQUEST, *PKERNEL_READ_REQUEST;

typedef struct _KERNEL_WRITE_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	ULONG Value;
	ULONG Size;

} KERNEL_WRITE_REQUEST, *PKERNEL_WRITE_REQUEST;



// interface for our driver
class KeInterface
{
public:
	HANDLE hDriver;

	KeInterface::KeInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	template <typename T>
	T ReadVirtualMemory(ULONG ProcessId, ULONG ReadAddress)
	{
		if (hDriver != INVALID_HANDLE_VALUE)
		{
			DWORD Return, Bytes;
			T retBuffer;

			KERNEL_READ_REQUEST ReadRequest;
			ReadRequest.ProcessId = ProcessId;
			ReadRequest.Address = ReadAddress;
			ReadRequest.Buffer = (ULONGLONG)&retBuffer;
			ReadRequest.Size = sizeof(T);

			// send code to our driver with the arguments
			if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), &Bytes, 0))
				return retBuffer;
		}
	}

	bool WriteVirtualMemory(ULONG ProcessId, ULONG WriteAddress,
		ULONG WriteValue, SIZE_T WriteSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		KERNEL_WRITE_REQUEST  WriteRequest;
		WriteRequest.ProcessId = ProcessId;
		WriteRequest.Address = WriteAddress;
		WriteRequest.Value = WriteValue;
		WriteRequest.Size = WriteSize;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest), 0, 0, &Bytes, NULL))
			return true;
		else
			return false;
	}
};

extern KeInterface Driver;