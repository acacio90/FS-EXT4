#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

#define BLOCK_SIZE 4096  // Tamanho do bloco, ajuste conforme necessário
#define EXT4_N_BLOCKS 15 // Número máximo de blocos em uma inode

// Estrutura da entrada de diretório
struct ext4_dir_entry {
    uint32_t inode;          // Número do inode
    uint16_t rec_len;        // Comprimento do registro
    uint8_t name_len;        // Comprimento do nome
    uint8_t file_type;       // Tipo do arquivo (pode ser omitido dependendo da sua implementação)
    char name[255];          // Nome do arquivo (ajuste conforme necessário)
};

// Estrutura do inode
struct ext4_inode {
    uint16_t i_mode;            // Modo do inode
    uint32_t i_block[EXT4_N_BLOCKS]; // Ponteiro para blocos de dados
};

// Define a estrutura do superbloco do EXT4
struct ext4_superblock {
    uint32_t inodes_count;       // Total de inodes no sistema de arquivos
    uint32_t blocks_count_lo;    // Total de blocos no sistema de arquivos (parte baixa)
    uint32_t reserved_blocks_count_lo;  // Número de blocos reservados para o superusuário (parte baixa)
    uint32_t free_blocks_count_lo;      // Número de blocos livres (parte baixa)
    uint32_t free_inodes_count; // Número de inodes livres
    uint32_t first_data_block;  // Número do primeiro bloco de dados
};

void read_superblock(int fd, struct ext4_superblock *sb);
void read_block(int fd, int block_number, char *buffer);
void list_directory(int fd, int inode_number);
void cat_file(int fd, int inode_number);
void show_info(int fd);
void export_file(int fd, const char *source_path, const char *target_path);
void touch_file(int fd, const char *filename);
void mkdir_directory(int fd, const char *dirname);
void rm_file(int fd, const char *filename);
void rmdir_directory(int fd, const char *dirname);
void rename_file(int fd, const char *old_filename, const char *new_filename);

void read_inode(int fd, int inode_number, struct ext4_inode *inode);


#endif
