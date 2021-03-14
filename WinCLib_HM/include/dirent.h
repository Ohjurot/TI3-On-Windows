/*
* dirent.h - Lightweight replacement for header for MSVC and Windows
* 
* Copyright 2021 by Ludwig Fuechsl
* Licensed under the MIT Licenese (see LICENCE file)
*/
#ifndef HMTIC_DIRENT
#define HMTIC_DIRENT

#include <sys/types.h>

#ifdef HMTIC_DIRENT_BUILD
#include <Windows.h>
#include <malloc.h>
#endif

#include <WinCLib_PreLoad.h>

// Max file name length
#define NAME_MAX 255
#define INVALID_DIR_HANLDE 0

/// <summary>
/// Directory handle
/// </summary>
typedef void DIR;

/// <summary>
/// Directory 
/// </summary>
struct dirent {
	/// <summary>
	/// Inode nummer
	/// </summary>
	long d_ino;

	/// <summary>
	/// Offset zum nächsten eintrag
	/// </summary>
	off_t d_off;

	/// <summary>
	/// Länge dieses eintrags
	/// </summary>
	unsigned short d_reclen;

	/// <summary>
	/// Dateiname
	/// </summary>
	char d_name[NAME_MAX + 1];
};


/// <summary>
/// Close a open directory handle
/// </summary>
/// <param name="dir">Input handle</param>
/// <returns>0 on succeed -1 on error</returns>
int closedir(DIR* dir);

/// <summary>
/// Open a directory
/// </summary>
/// <param name="dirPath">Path to directory</param>
/// <returns>DIR Handle</returns>
DIR* opendir(const char* dirPath);

/// <summary>
/// Read directory
/// </summary>
/// <param name="dir">Directory hanlde</param>
/// <returns>Pointer to dirent</returns>
struct dirent* readdir(DIR* dir);

/// <summary>
/// NOT SUPPORTED
/// </summary>
/// <returns>-1</returns>
int readdir_r(DIR** dir, struct dirent*, struct dirent**);

/// <summary>
/// Reset directory stream
/// </summary>
/// <param name="dir">Directory handle</param>
void rewinddir(DIR* dir);

/// <summary>
/// Seek to position in stream
/// </summary>
/// <param name="dir">Directory handle</param>
/// <param name="pos">New position</param>
void seekdir(DIR* dir, long int pos);

/// <summary>
/// Get position of stream
/// </summary>
/// <param name="dir">Directory index</param>
/// <returns>Current file index</returns>
long int telldir(DIR* dir);

#ifdef HMTIC_DIRENT_BUILD
/// <summary>
/// Internal directory data struct
/// </summary>
typedef struct ___DIR_DATA {
	/// <summary>
	/// Directory path / name
	/// </summary>
	CHAR directoryName[MAX_PATH];

	/// <summary>
	/// Search hadle
	/// </summary>
	HANDLE searchHandle;

	/// <summary>
	/// Current file index
	/// </summary>
	long int fileIndex;

	/// <summary>
	/// Find data handle
	/// </summary>
	WIN32_FIND_DATAA findData;

	/// <summary>
	/// Current directrly listing
	/// </summary>
	struct dirent currentInfo;
} __DIR_DATA;
#endif
#endif
