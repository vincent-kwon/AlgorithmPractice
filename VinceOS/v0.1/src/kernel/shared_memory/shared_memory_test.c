#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main ()
{
  int segment_id;
  char* shared_memory;
  struct shmid_ds shmbuffer;
  int segment_size;
  const int shared_segment_size = 0x6400; // memo-20170812: 1024 * (1 + 16 + 25) = 25600
  // get shared memory
  segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

  // get actual memory buffer address
  shared_memory = (char*)shmat(segment_id, 0, 0);
  printf("shared memory attached at address %p\n", shared_memory);

  // get size via shmid_ds (data structure) 
  shmctl(segment_id, IPC_STAT, &shmbuffer);
  segment_size = shmbuffer.shm_segsz;
  printf("segment size: %d\n", segment_size);

  // to the shared memory address, write hello work
  sprintf(shared_memory, "Hello, world.");

  // detach
  shmdt(shared_memory);

  // can attach to different ID 0x5000000
  shared_memory = (char*) shmat(segment_id, (void*) 0x5000000, 0);
  printf("shared memory reattached at address %p\n", shared_memory);
  printf("%s\n", shared_memory);

  // detach again
  shmdt(shared_memory);

  // remove??
  shmctl(segment_id, IPC_RMID, 0);
  return 0;
}
