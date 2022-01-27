#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int p[2])
{
    int flat;
    int primes;
    int n;
    close(p[1]);
    if(read(p[0], &primes, 4)!=4){
        fprintf(2,"fail to read data from pipe");
        exit(1);
    }
    printf("prime %d\n", prime);
    flat = read(p[0], &n, 4);
    if(flat){
        int newp[2];
        pipe(newp);
        if(fork() == 0){
            prime(newp);
        }else{
            close(newp[0]);
            if(n%primes) write(newp[1], &n, 4);
            while(read(p[0],&n,4)){
                if(n%primes) write(newp[1],&n,4);
        }
        close(p[0]);
        close(newp[1]);
        wait(0);
        }
    }
    exit(0);
}

int main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);
    if(fork() == 0){
        prime(p);
    }else{
        close(p[0]);
        for(int i = 2; i <=35; i++)
        {
            if(write(p[1], &i, 4)!=4){
                fprintf(2,"fail to write 2 ~ 35 into pipe");
                exit(1);
            }
            close(p[1]);
            wait(0);
            exit(0);
        }
    }
    return 0;
}