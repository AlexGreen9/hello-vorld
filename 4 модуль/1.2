#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
double Square(double side) {
       return side * side;
       }
int main(int argc, char *argv[]){
       if(argc !=2){
             printf("Использование: %s <side_lenght>\n", argv[0]);
             exit(1);
       }
       double side = atof(argv[1]);
       pid_t pid = fork();
       if (pid < 0){
             fprintf(stderr, "Fork сломался\n");
             exit(1);
       }
       else if(pid == 0){
             //дочерний процесс
             double childArea = Square(side);
             printf("Дочерний процесс: площадь квадрата с длиной стороны: %.2f is %.2f\n", side, childArea);
             }
             else{
                   //родительский процесс
                   double parentArea = Square(side);
             printf("Родительский процесс: площадь квадрата с длиной стороны: %.2f is %.2f\n", side, parentArea);
                   wait(NULL); //ждём, пока завершиться дочерний процесс
             }
       return 0;
}

