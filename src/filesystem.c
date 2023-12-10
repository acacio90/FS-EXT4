#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#define BLOCK_SIZE 4096

void read_superblock(int fd, struct ext4_superblock *sb) {
    // Supomos que o superbloco está localizado no offset 1024
    off_t offset = 1024;

    // Movendo o ponteiro do arquivo para o início do superbloco
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("Erro ao posicionar o ponteiro do arquivo no superbloco");
        exit(EXIT_FAILURE);
    }

    // Lendo o superbloco
    if (read(fd, sb, sizeof(struct ext4_superblock)) == -1) {
        perror("Erro ao ler o superbloco");
        exit(EXIT_FAILURE);
    }
}

void read_block(int fd, int block_number, char *buffer) {
    // Supomos que o tamanho do bloco é de 4096 bytes (4 KB)
    off_t block_offset = block_number * BLOCK_SIZE;

    // Movendo o ponteiro do arquivo para o início do bloco
    if (lseek(fd, block_offset, SEEK_SET) == -1) {
        perror("Erro ao posicionar o ponteiro do arquivo no bloco");
        exit(EXIT_FAILURE);
    }

    // Lendo o bloco
    if (read(fd, buffer, BLOCK_SIZE) == -1) {
        perror("Erro ao ler o bloco");
        exit(EXIT_FAILURE);
    }
}

void read_inode(int fd, int inode_number, struct ext4_inode *inode) {
    // Tamanho do inode no sistema de arquivos EXT4
    size_t inode_size = sizeof(struct ext4_inode);

    // Calcula o offset do inode no sistema de arquivos
    off_t inode_offset = 1024 + sizeof(struct ext4_superblock) + (inode_number - 1) * inode_size;

    // Move o ponteiro do arquivo para o início do inode
    if (lseek(fd, inode_offset, SEEK_SET) == -1) {
        perror("Erro ao posicionar o ponteiro do arquivo no inode");
        exit(EXIT_FAILURE);
    }

    // Lê o inode
    if (read(fd, inode, inode_size) == -1) {
        perror("Erro ao ler o inode");
        exit(EXIT_FAILURE);
    }
}

void list_directory(int fd, int inode_number) {
    struct ext4_dir_entry *directory_entry = malloc(sizeof(struct ext4_dir_entry));

    // Lê o inode do diretório
    struct ext4_inode dir_inode;
    read_inode(fd, inode_number, &dir_inode);

    // Verifica se é um diretório
    if ((dir_inode.i_mode & 0xF000) != 0x4000) { // Verifica se é um diretório
        fprintf(stderr, "O inode não é de um diretório.\n");
        free(directory_entry);
        exit(EXIT_FAILURE);
    }

    // Loop pelos blocos de dados do diretório
    for (int i = 0; i < EXT4_N_BLOCKS; i++) {
        if (dir_inode.i_block[i] == 0) {
            break;  // Fim dos blocos de dados do diretório
        }

        // Lê cada bloco de dados do diretório
        char *block_data = malloc(BLOCK_SIZE);
        read_block(fd, dir_inode.i_block[i], block_data);

        // Itera sobre as entradas de diretório neste bloco
        char *ptr = block_data;
        while (ptr < block_data + BLOCK_SIZE) {
            memcpy(directory_entry, ptr, sizeof(struct ext4_dir_entry));

            // Imprime o nome da entrada de diretório (ou manipula conforme necessário)
            printf("Nome: %.*s\n", directory_entry->name_len, directory_entry->name);

            // Avança para a próxima entrada de diretório
            ptr += directory_entry->rec_len;
        }

        free(block_data);
    }

    free(directory_entry);
}

void cat_file(int fd, int inode_number) {
    // Implementar a lógica para exibir o conteúdo de um arquivo
}

void show_info(int fd) {
    // Implementar a lógica para exibir informações do sistema de arquivos e da imagem
}

void export_file(int fd, const char *source_path, const char *target_path) {
    // Implementar a lógica para exportar um arquivo
}

void touch_file(int fd, const char *filename) {
    // Implementar a lógica para criar um arquivo vazio
}

void mkdir_directory(int fd, const char *dirname) {
    // Implementar a lógica para criar um diretório vazio
}

void rm_file(int fd, const char *filename) {
    // Implementar a lógica para remover um arquivo
}

void rmdir_directory(int fd, const char *dirname) {
    // Implementar a lógica para remover um diretório vazio
}

void rename_file(int fd, const char *old_filename, const char *new_filename) {
    // Implementar a lógica para renomear um arquivo
}
