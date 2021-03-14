#ifndef HMTIC_LOADER
#define HMTIC_LOADER

// Define lib behaviour
#define _CRT_SECURE_NO_WARNINGS

// Include external libs
#include <io.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Define O_ Macros
#define O_APPEND _O_APPEND 
#define O_BINARY _O_BINARY 
#define O_CREAT _O_CREAT
#define O_NOINHERIT _O_NOINHERIT
#define O_RANDOM _O_RANDOM
#define O_RDONLY _O_RDONLY
#define O_RDWR _O_RDWR
#define O_SEQUENTIAL _O_SEQUENTIAL
#define O_TEXT _O_TEXT
#define O_TRUNC	_O_TRUNC
#define O_WRONLY _O_WRONLY
#define O_U16TEXT _O_U16TEXT
#define O_U8TEXT _O_U8TEXT
#define O_WTEXT _O_WTEXT

// Define S_ Macros (will not work)
#define S_IRUSR 0x0400
#define S_IWUSR 0x0200
#define S_IXUSR 0x0100
#define S_IRWXU 0x0700
#define S_IRGRP 0x0040
#define S_IWGRP 0x0020
#define S_IXGRP 0x0010 
#define S_IRWXG 0x0070 
#define S_IROTH 0x0004 
#define S_IWOTH 0x0002 
#define S_IXOTH 0x0001 
#define S_IRWXO 0x0007

// Undefined float
#define FLT_EPS FLT_EPSILON
#define FLT_MAX_EPS FLT_MAX_10_EXP
#define FLT_MIN_EPS FLT_MIN_10_EXP
#define DBL_EPS DBL_EPSILON
#define DBL_MAX_EPS DBL_MAX_10_EXP
#define DBL_MIN_EPS DBL_MIN_10_EXP

// Undifined signal
#define SIG_DFT SIG_DFL

// Define change functions
#define gets(arg) gets_s(arg, _CRT_SIZE_MAX)
#define strcpy(dest, src) strcpy_s(dest, _CRT_SIZE_MAX, src)

// Pipes
#define popen(commandLine, mode) _popen(commandLine, mode)
#define pclose(filep) _pclose(filep)
#define mkfifo(path, mode) -1

// Low level IO
#define open(...) _open(__VA_ARGS__)
#define close(handle) _close(handle)
#define read(handle, buffer, count) _read(handle, buffer, count)
#define write(handle, buffer, count) _write(handle, buffer, count)
#define lseek(fh, offset, mode) _lseek(fh, offset, mode);
#define commit(fh) _commit(fh)
#define creat(filname, mode) _creat(filname, mode)
#define eof(fh) _eof(fh)
#define umsk(mode) _umask(mode)
#define tell(fh) _tell(fh)

#endif
