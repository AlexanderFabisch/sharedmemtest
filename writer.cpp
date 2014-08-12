#include "SharedMemory.h"

#include "data.h"

int main()
{
  SharedMemory sm("mysm", sizeof(Data));

  if(!sm.success())
    return 1;

  Data data;

  sm.initializeMemory(data);

  data.c = 'a';
  data.i = 10;
  data.f = 0.32f;

  sm << data;

  sleep(2);

  sm.closeAccess();

  printf("finished\n");
}
