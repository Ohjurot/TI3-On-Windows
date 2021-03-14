#define HMTIC_UNISTD_BUILD
#include "unistd.h"

char* getcwd(char* buffer, size_t size) {
	DWORD len = GetCurrentDirectoryA(size, buffer);
	return (len > 0) ? buffer : NULL;
}

int chdir(const char* path) {
	// Switch directory
	if (path) {
		if (SetCurrentDirectoryA(path)) {
			return 0;
		}
	}

	// Fail
	return -1;
}

int mkdir(const char* path, mode_t mode) {
	// Create directoy
	if (CreateDirectoryA(path, NULL)) {
		return 0;
	}

	// Fail
	return -1;
}

int rmdir(const char* path) {
	// Remove directory
	if (RemoveDirectoryA(path)) {
		return 0;
	}

	// Fail
	return -1;
}
