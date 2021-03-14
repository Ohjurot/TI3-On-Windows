/*
* dirent.h - Lightweight replacement for header for MSVC and Windows
*
* Copyright 2021 by Ludwig Fuechsl
* Licensed under the MIT Licenese (see LICENCE file)
*/
#ifndef HMTIC_UNISTD
#define HMTIC_UNISTD

#ifdef HMTIC_UNISTD_BUILD
#include <Windows.h>
#endif

typedef unsigned short mode_t;

/// <summary>
/// Retrive the working directory
/// </summary>
/// <param name="buffer">Buffer that recives data</param>
/// <param name="size">Maximum size of buffer</param>
/// <returns>buffer or null</returns>
char* getcwd(char* buffer, size_t size);

/// <summary>
/// Switch working directory
/// </summary>
/// <param name="path">path to new directory</param>
/// <returns>0 on succees -1 on fail</returns>
int chdir(const char* path);

/// <summary>
/// Create a directory
/// </summary>
/// <param name="path">Path to directory</param>
/// <param name="mode">Directory mode (internal ignored)</param>
/// <returns>0 on succees -1 on fail</returns>
int mkdir(const char* path, mode_t mode);

/// <summary>
/// Removes a directory
/// </summary>
/// <param name="path">Path to directory</param>
/// <returns>0 on succees -1 on fail</returns>
int rmdir(const char* path);

#endif