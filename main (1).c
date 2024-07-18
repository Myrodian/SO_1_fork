#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define MENSAGEM 25
#define FIM_LEITURA 0
#define FIM_ESCRITA 1

void dividir_comando(char comando[], char* lista[]){
    int indice_argumentos = 0;
    char* token = strtok (comando," ");
    while (token != NULL){
        lista[indice_argumentos++] = token;
        token = strtok (NULL, " \n");
    }
    lista[indice_argumentos++] = NULL;
//    aux = token[0];

    for(int i = 0; i<indice_argumentos; i++){
        printf("token[%d] = %s\n", i, lista[i]);
    }
}
int dividir_pipe(char comando[], char* lista[]){
    int indice_argumentos = 0;
    int num_pipes = 0;
    printf("%s\n", comando);
    char* token = strtok (comando," ");
    while (token != NULL){
        if(strcmp(token, "|") == 0){
            lista[indice_argumentos++] = NULL;
            num_pipes++;
        }else{
            lista[indice_argumentos++] = token;
        }
        token = strtok (NULL, " ");
    }
    lista[indice_argumentos++] = NULL;
    for(int i = 0; i<indice_argumentos; i++){
        if(token[i] != NULL){   // concatenando string do comando

        }else{  // trocando o comando pro proximo filho

        }
    }
    for(int i = 0; i<indice_argumentos; i++){
        printf("token[%d] = %s\n", i, lista[i]);
    }
    return num_pipes;
}
int main() {
    int fd[2], sw = 10;
    pid_t retorno_fork;
    int num_pipes;
    char comando[100];
    char* lista_arg[20];
    char* aux;
    while(sw != 0){
        fflush(stdin);
        printf("Digite um comando:$");
        fgets(comando, 100, stdin);
        comando[strcspn(comando, "\n")] = 0;
//        printf("%s\n", comando);
        if(strcmp(comando, "exit") == 0){
            exit(0);
        }else{
            pipe(fd);
            if(pipe(fd) == -1){
                printf("Deu merda!");
                exit(-1);
            }
            dividir_comando(comando, lista_arg);
//            retorno_fork = fork();// criação do filho

            }if((retorno_fork = fork()) == 0){// cria o filho com seu processo(Filho 01)
//            dup2(fd[FIM_ESCRITA], STDOUT_FILENO);
//            close(fd[FIM_ESCRITA]);
//            close(fd[FIM_LEITURA]);
            // split
            execvp(comando, lista_arg);

            }else if(retorno_fork < 0){
            printf("Processo filho nao foi criado!");
            exit(-1);
        }
//        if(fork() == 0){ // cria o filho com seu processo(Filho 02)
//        dup2(fd[FIM_LEITURA], STDIN_FILENO);
//            close(fd[FIM_LEITURA]);
//            close(fd[FIM_ESCRITA]);
//            //split
//            dividir_comando(comando, lista_arg);
//            execvp(, lista_arg);
//
//        }
            if (retorno_fork > 0){// processo pai
                wait(NULL);
            }
        }
    return 0;
}
