#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void process(int iteration)
{
      printf("task %d started \n", iteration);

      sleep(1000*((rand() % (8 - 1 + 1)) + 1));

      printf("task %d finished \n", iteration);

}
void processTwo(int iteration)
{
      printf("task %d started \n", iteration);

      sleep(1000*((rand() % (8 - 1 + 1)) + 1));
      
      printf("task %d finished \n", iteration);

}

int main(int argc, char* argv[])
{
    int nSize = atoi(argv[1]);
    int patternChoice = atoi(argv[2]);

    pid_t *pidsArray = malloc(nSize * sizeof(pid_t));

    if(patternChoice==1)
    {
      for (int i = 0; i < nSize; i++)
      {
         pidsArray[i]=fork();
         process(i);
      }
      for (int i = 0; i < nSize; i++) {
        waitpid(pidsArray[i], NULL, 0);
    }
    }
    else
    {
{
      for (int i = 0; i < nSize; i++)
      {
         pidsArray[i]=fork();
         processTwo(i);
         waitpid(pidsArray[i], NULL, 0);

      }
    }
    free(pidsArray);
    return 0;
}}