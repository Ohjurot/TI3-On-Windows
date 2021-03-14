#define HMTIC_DIRENT_BUILD
#include "dirent.h"

int closedir(DIR* dir) {
	// Check hanlde
	__DIR_DATA* ptrData = (__DIR_DATA*)dir;
	if (ptrData) {
		// Close handle
		if (ptrData->searchHandle) {
			FindClose(ptrData->searchHandle);
		}

		// Free, unset and return
		free(ptrData);
		return 0;
	}

	// Fallback -1
	return -1;
}

DIR* opendir(const char* dirPath){
	// Create data on stack
	__DIR_DATA ddData;

	// Copy path
	strcpy_s(ddData.directoryName, MAX_PATH, dirPath);
	size_t len = strlen(ddData.directoryName);

	// Append slash
	if (ddData.directoryName[len - 1] != '\\' && len < MAX_PATH - 3) {
		ddData.directoryName[len] = '\\';
		ddData.directoryName[len + 1] = '*';
		ddData.directoryName[len + 2] = '\0';
	}
	else if (len < MAX_PATH - 2) {
		ddData.directoryName[len] = '*';
		ddData.directoryName[len + 1] = '\0';
	}

	// Find first file
	ddData.searchHandle = FindFirstFileA(ddData.directoryName, &ddData.findData);
	if (ddData.searchHandle != INVALID_HANDLE_VALUE) {
		ddData.fileIndex = 0;

		// Allocate memory and copy
		__DIR_DATA* ptrData = malloc(sizeof(__DIR_DATA));
		if (ptrData) {
			memcpy(ptrData, &ddData, sizeof(__DIR_DATA));
			// Return data pointer
			return ptrData;
		}
	}
	
	// Fallback nullpointer
	return 0;
}

struct dirent* readdir(DIR* dir) {
	// Cast and check pointer
	__DIR_DATA* ptrData = (__DIR_DATA*)dir;
	if (ptrData && (ptrData->searchHandle != INVALID_HANDLE_VALUE)) {
		// Extract dirinfo
		ptrData->currentInfo.d_ino = 0;
		strcpy_s(ptrData->currentInfo.d_name, NAME_MAX + 1, ptrData->findData.cFileName);
		ptrData->currentInfo.d_off = 0;
		ptrData->currentInfo.d_reclen = 0;

		// Move to next file
		if (FindNextFileA(ptrData->searchHandle, &ptrData->findData) == 0) {
			FindClose(ptrData->searchHandle);
			ptrData->searchHandle = INVALID_HANDLE_VALUE;
			return &ptrData->currentInfo;
		}

		// Increment counter
		ptrData->fileIndex++;

		// Return pointer
		return &ptrData->currentInfo;
	}
	
	return NULL;
}

int readdir_r(DIR** dir, struct dirent* drp, struct dirent** drpp){
	return -1;
}

void rewinddir(DIR* dir){
	// Cast and check pointer
	__DIR_DATA* ptrData = (__DIR_DATA*)dir;
	if (ptrData) {
		// Close hanlde
		if (ptrData->searchHandle != INVALID_HANDLE_VALUE) {
			FindClose(ptrData->searchHandle);
		}

		// Find first file
		ptrData->searchHandle = FindFirstFileA(ptrData->directoryName, &ptrData->findData);
		if (ptrData->searchHandle != INVALID_HANDLE_VALUE) {
			// Move until real file is found
			while ((ptrData->findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && FindNextFileA(ptrData->searchHandle, &ptrData->findData));
			ptrData->fileIndex = 0;
		}
	}
}

void seekdir(DIR* dir, long int pos) {
	// Check dir
	if (dir) {
		// Rewind and seek
		rewinddir(dir);
		for (long int i = 0; i < pos; i++) {
			readdir(dir);
		}
	}
}

long int telldir(DIR* dir) {
	// Cast and check pointer
	__DIR_DATA* ptrData = (__DIR_DATA*)dir;
	if (ptrData) {
		return ptrData->fileIndex;
	}

	// Return zero
	return 0;
}
