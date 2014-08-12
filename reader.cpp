#include "SharedMemory.h"

#include "data.h"

int main()
{
  SharedMemory sm("mysm", sizeof(Data));

  if(!sm.success())
    return 1;

  Data data;

  sm >> data;

  printf("%c %d %f\n", data.c, data.i, data.f);

  sleep(1);

  sm >> data;

  printf("%c %d %f\n", data.c, data.i, data.f);
}
