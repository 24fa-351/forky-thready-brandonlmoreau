#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>   
#include <time.h>       

int getRandTime(int min, int max)
{
    int sleepTime = rand() % max + min;
    return sleepTime;
}

int main(int argc, char *argv[]) {
    int pattern;
    int n;
    pid_t codePID;
    FILE* file ;

    file= fopen("console.txt","w");
    n = atoi(argv[1]);
    pattern = atoi(argv[2]);

    if (pattern == 1) {
        pid_t child[n];

        for (int i = 1; i <= n; i++) {

             codePID = fork();
            
             int processIteration = i; 

            if ( codePID == 0) {
                fprintf(file,"starting process #%d  PID#%d\n", processIteration, getpid());
                sleep(getRandTime(1,8));

                fprintf(file,"ending process #%d  PID#%d\n", processIteration, getpid());
                fclose(file);
                return 0;
            }
             else 
            {
                child[i-1] =  codePID;
            }
        }

        for (int i = 0; i < n; i++) 
        {

            waitpid(child[i], NULL,0);
        }

    } else if (pattern == 2) {
        int currentProcess = 1;
        while (currentProcess <= n) 
        {

            if (currentProcess < n) 
            {
                fprintf(file,"process #%d PID #%d creating new process #%d\n", currentProcess, getpid(), currentProcess + 1);
                 codePID = fork();
                if ( codePID == 0) 
                {
                    currentProcess++; 
                    continue; 
                }
                 else 
                {
                    fprintf(file,"starting process #%d  PID#%d\n", currentProcess, getpid());
                    sleep(getRandTime(1,8));
                    wait(NULL);

                    fprintf(file,"ending process #%d  PID#%d\n", currentProcess, getpid());
                    fclose(file);
                    return 0;
                }
            } 
            else 
            {
                fprintf(file,"starting process #%d  PID#%d\n", currentProcess, getpid());
                sleep(getRandTime(1,8));

                fprintf(file,"ending process #%d  PID#%d\n", currentProcess, getpid());
                fclose(file);
                return 0;
            }
        }
    }
              
    fclose(file);
    return 0;
}