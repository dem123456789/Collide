/******************************************
 *  This is only created in RELEASE mode  *
 ******************************************/
#ifndef _DEBUG

#include <stdio.h>
#include <unistd.h>

/* Must be set on the command-line with -D */
#define ROM_NAME _ROM
#define VBA_NAME _VBA

int main()
{
  int ret;
  printf("Launching RELEASE binary...\n");
  printf("ROM: %s\n", ROM_NAME);
  printf("VBA: %s\n", VBA_NAME);
  fflush(stdout);
  if((ret = execl(VBA_NAME, VBA_NAME, ROM_NAME, NULL)))
  	fprintf(stderr, "ERROR with execl call!\n");
  return ret;
}

#endif
