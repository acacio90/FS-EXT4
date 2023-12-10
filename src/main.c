#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    // Verifique argumentos e abra o arquivo de imagem
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <imagem.img>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *device = argv[1];
    int fd = open(device, O_RDWR);
    if (fd == -1) {
        perror("Erro ao abrir a imagem do sistema de arquivos");
        exit(EXIT_FAILURE);
    }

    int current_inode = 0;

    // Loop principal do shell
    while (1) {
        // Obtendo o comando do usuário
        char command[256];
        printf("$ ");
        fgets(command, sizeof(command), stdin);
        if (strncmp(command, "ls", 2) == 0) {
            list_directory(fd, current_inode);
        }/* else if (strncmp(command, "cat", 3) == 0) {
        
            char *filename = command + 4;
            cat_file(fd, current_inode, filename);
        } else if (strncmp(command, "info", 4) == 0) {
            show_info(fd);
        } else if (strncmp(command, "export", 6) == 0) {
            char *source_path = strtok(command + 7, " ");
            char *target_path = strtok(NULL, " ");
            export_file(fd, source_path, target_path);
        } else if (strncmp(command, "exit", 4) == 0) {
            close(fd);
            exit(EXIT_SUCCESS);
        } else {
            printf("Comando não reconhecido.\n");
        }
    */
    }
    return 0;
}
