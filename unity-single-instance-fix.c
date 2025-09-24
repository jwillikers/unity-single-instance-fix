// This code is licensed under the CC BY-NC-SA:
// https://creativecommons.org/licenses/by-nc-sa/3.0/ Code by Eike Sauer and
// from this blog post
// https://ein-eike.de/2025/06/05/fix-for-old-unity-games-for-linux-not-starting-anymore/
#define _GNU_SOURCE
#undef _FILE_OFFSET_BITS // Prevent defining fopen64 through
                         // _FILE_OFFSET_BITS=64
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

static FILE *opened_file = NULL;

FILE *fopen(const char *pathname, const char *mode) {
  static FILE *(*real_fopen)(const char *, const char *) = NULL;
  if (!real_fopen) {
    printf("Intercepting fopen() calls! \n");
    real_fopen = dlsym(RTLD_NEXT, "fopen");
  }
  opened_file = NULL;

  FILE *ret_val = real_fopen(pathname, mode);

  if (strncmp(pathname, "/proc/", 6) == 0) {
    // remember fopen() calls to /proc...
    opened_file = ret_val;
  }

  return ret_val;
}

FILE *fopen64(const char *pathname, const char *mode) {
  static FILE *(*real_fopen64)(const char *, const char *) = NULL;
  if (!real_fopen64) {
    printf("Intercepting fopen64() calls! \n");
    real_fopen64 = dlsym(RTLD_NEXT, "fopen64");
  }
  opened_file = NULL;

  FILE *ret_val = real_fopen64(pathname, mode);

  if (strncmp(pathname, "/proc/", 6) == 0) {
    // remember fopen() calls to /proc...
    opened_file = ret_val;
  }

  return ret_val;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  static size_t (*real_fread)(void *, size_t, size_t, FILE *) = NULL;
  if (!real_fread) {
    printf("Intercepting fread() calls! \n");
    real_fread = dlsym(RTLD_NEXT, "fread");
  }

  size_t ret_val = real_fread(ptr, size, nmemb, stream);

  if (stream == opened_file && strncmp(ptr, "/proc/self/exe", 14) == 0) {
    printf("Faking fread() return value! \n");
    memcpy(ptr, "/wutevawutevawuteva", 14);
  }

  return ret_val;
}
