#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "resource.h"
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "MinHook.h"
#include <shlwapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <ntddkbd.h>
#include <fileapi.h>

#include <ntifs.h>
#include <ntddk.h>
#include <fileinfo.h>
#include <wdm.h>

#if defined _M_X64
#pragma comment(lib, "libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "libMinHook.x86.lib")
#endif

#define NT_SUCCESS(Status) ((NTSTATUS)(Status)>=0)

typedef LONG NTSTATUS;
#define STATUS_SUCCESS   ((NTSTATUS)0x00000000L)


typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation, ObjectNameInformation, ObjectTypeInformation, ObjectAllInformation, ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

typedef struct _OBJECT_NAME_INFORMATION {

	UNICODE_STRING Name;
	WCHAR NameBuffer[1];

} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;


typedef struct _IO_STATUS_BLOCK
{
	NTSTATUS Status;
	ULONG Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PCHAR  Buffer;
} ANSI_STRING, *PANSI_STRING;


typedef VOID(NTAPI *PIO_APC_ROUTINE)(IN PVOID ApcContext, IN PIO_STATUS_BLOCK   IoStatusBlock, IN ULONG Reserved);


typedef struct _FILE_BOTH_DIR_INFORMATION {
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	ULONG         EaSize;
	CCHAR         ShortNameLength;
	WCHAR         ShortName[12];
	WCHAR         FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;


typedef struct _FILE_DIRECTORY_INFORMATION
{
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	WCHAR         FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;


typedef struct _FILE_FULL_DIR_INFORMATION
{
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	ULONG         EaSize;
	WCHAR         FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_FULL_DIR_INFORMATION
{
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	ULONG         EaSize;
	LARGE_INTEGER FileId;
	WCHAR         FileName[1];
} FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIR_INFORMATION {
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	ULONG         EaSize;
	CCHAR         ShortNameLength;
	WCHAR         ShortName[12];
	CHAR           Reserver[2];
	LARGE_INTEGER FileId;
	WCHAR         FileName[1];
} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

//typedef struct _FILE_ID_BOTH_DIR_INFORMATION
//{
//	ULONG         NextEntryOffset;
//	ULONG         FileIndex;
//	LARGE_INTEGER CreationTime;
//	LARGE_INTEGER LastAccessTime;
//	LARGE_INTEGER LastWriteTime;
//	LARGE_INTEGER ChangeTime;
//	LARGE_INTEGER EndOfFile;
//	LARGE_INTEGER AllocationSize;
//	ULONG         FileAttributes;
//	ULONG         FileNameLength;
//	ULONG         EaSize;
//	CCHAR         ShortNameLength;
//	WCHAR         ShortName[12];
//	LARGE_INTEGER FileId;
//	WCHAR         FileName[1];
//} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG FileIndex;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;


extern "C" NTSYSAPI NTSTATUS NTAPI RtlUnicodeStringToAnsiString(PANSI_STRING  DestinationString, PUNICODE_STRING SourceString,
	BOOLEAN AllocateDestinationString);

extern "C" NTSYSAPI VOID NTAPI RtlFreeAnsiString(PANSI_STRING AnsiString);

extern "C" NTSYSAPI NTSTATUS NTAPI NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext,
	PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass,
	BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);


typedef NTSTATUS(WINAPI *NtQueryDirectoryFileNext)(HANDLE hFile, HANDLE hEvent, PIO_APC_ROUTINE IoApcRoutine, PVOID IoApcContext,
	PIO_STATUS_BLOCK pIoStatusBlock, PVOID FileInformationBuffer, ULONG FileInformationBufferLength, FILE_INFORMATION_CLASS FileInfoClass,
	BOOLEAN bReturnOnlyOneEntry, PUNICODE_STRING PathMask, BOOLEAN bRestartQuery);

NtQueryDirectoryFileNext Real_NtQueryDirectoryFile = NULL;