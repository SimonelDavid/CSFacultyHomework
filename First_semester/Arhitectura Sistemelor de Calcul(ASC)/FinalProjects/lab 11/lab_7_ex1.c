#include <stdio.h>
#inlcude <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int a = 5;
    // doar daca apelam pipe() aici are sens pentru ca se creeaza un canal de comunicatii cu sens
    int pid = fork();
    if (pid == -1)       //fork() has failed
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
 
    // aici sa nu scriem niciodata cod(doar daca stim foarte bine ce facem) si sa cautam alte solutii daca avem nevoide de cod aici
 
    if (pid == 0)       // in child
    {
        int sum = a + 5;
        
        exit(EXIT_SUCCES);
    }
    
    else    // in parent else de aici nu este necesar deoarece si cu si fara else codul se executa in parinte DACA SI NUMAI DACA am dat exit(EXIT_SUCCES) mai sus in child
    {
        signal(SIGCHLD, SIG_IGN);   // pentru prevenirea proceselor zombie
        //
        int status;
        wait(&status);      // pentru prevenirea preoceselor orfan
    }
    
    return 0;
}