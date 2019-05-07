/* Uses a memory mapping to read a file. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  char *actual = (char *) 0x10000000;
  int handle;
  mapid_t map;
  size_t i;
  msg("mmap read test0\n");
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  msg("handle: %d\n", handle);
  CHECK ((map = mmap (handle, actual)) != MAP_FAILED, "mmap \"sample.txt\"");
  msg("mmap read test00\n");
  /* Check that data is correct. */
  int ret_memcmp = memcmp (actual, sample, strlen (sample));
  msg("memcmp: %d\n", ret_memcmp);
  if (ret_memcmp)
  {
	msg("mmap bad");
    fail ("read of mmap'd file reported bad data");
  }
  msg("mmap read test000\n");
  /* Verify that data is followed by zeros. */
  for (i = strlen (sample); i < 4096; i++)
    if (actual[i] != 0)
      fail ("byte %zu of mmap'd region has value %02hhx (should be 0)",
            i, actual[i]);
  msg("mmap read test\n");
  munmap (map);
  msg("mmap read test2\n");
  close (handle);
  msg("mmap read test3\n");
}
