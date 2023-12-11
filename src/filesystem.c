#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "filesystem.h"

void read_superblock(FILE *image, struct super_block_t *superblock) {
    fseek(image, SUPERBLOCK_OFFSET, SEEK_SET);
    fread(superblock, sizeof(struct super_block_t), 1, image);
}

void read_block_group_descriptors(FILE *image, struct block_group_descriptors *descritores) {
    fseek(image, GROUP_DESCRIPTORS_OFFSET, SEEK_SET);
    fread(descritores, sizeof(struct block_group_descriptors), 1, image);
}

void ext4_info(struct super_block_t *superblock) {
    printf("General Information:\n");
    printf("Filesystem Volume Name: %s\n", superblock->s_volume_name);
    printf("Last Mounted On: %s", ctime(&(superblock->s_last_mounted)));
    printf("Filesystem UUID: \n"); 
    printf("Filesystem Magic Number: %x\n", superblock->s_magic);
    printf("Filesystem Revision Level: %d\n", superblock->s_rev_level);
    printf("Filesystem Features: %llx\n", (unsigned long long)superblock->s_feature_compat);
    printf("Filesystem Flags: %x\n", superblock->s_flags);
    printf("Default Mount Options: %s\n", superblock->s_mount_opts);
    printf("Filesystem State: %d\n", superblock->s_state);
    printf("Error Behavior: %d\n", superblock->s_errors);
    printf("OS Type: %d\n", superblock->s_creator_os);
    printf("Inode Count: %d\n", superblock->s_inodes_count);
    printf("Block Count: %d\n", superblock->s_blocks_count_lo);
    printf("Reserved Block Count: %d\n", superblock->s_r_blocks_count_lo);
    printf("Overhead Blocks: %d\n", superblock->s_overhead_blocks);
    printf("Free Blocks: %d\n", superblock->s_free_blocks_count_lo);
    printf("Free Inodes: %d\n", superblock->s_free_inodes_count);
    printf("First Data Block: %d\n", superblock->s_first_data_block);
    printf("Block Size: %d\n", 1024 << superblock->s_log_block_size);
    printf("Cluster Size: %d\n", 1024 << superblock->s_log_cluster_size);
    printf("Group Descriptor Size: %ld\n", sizeof(struct block_group_descriptors));
    printf("Filesystem Creation Time: %s", ctime((const time_t *)&superblock->s_lastcheck));
    printf("First Unreserved Inode: %d\n", superblock->s_first_ino);
}

// No arquivo filesystem.c, implemente a função
void ext4_print_inode_info(FILE *image, struct super_block_t *superblock, int inode_number) {
    struct inode_t inode;

    // Lê o inode correspondente ao inode_number
    fseek(image, INODE_OFFSET(inode_number), SEEK_SET);
    fread(&inode, sizeof(struct inode_t), 1, image);

    // Imprime as informações do inode
    printf("Inode %d Information:\n", inode_number);
    printf("Mode: %o\n", inode.i_mode);
    printf("UID: %d\n", inode.i_uid);
    printf("GID: %d\n", inode.i_gid);
    printf("Size: %d\n", inode.i_size_lo);
    printf("Links Count: %d\n", inode.i_links_count);
    printf("Blocks Count: %d\n", inode.i_blocks_lo);

    // Adicione mais informações conforme necessário

    // Exemplo: Imprimir os blocos de dados do inode
    printf("Data Blocks: ");
    for (int i = 0; i < EXT4_NUM_BLOCKS; ++i) {
        printf("%d ", inode.i_block[i]);
    }
    printf("\n");
}

void ext4_cat(FILE *image, int block_size, struct inode_t *inode) {
    if (inode->i_size_lo <= 0) {
        printf("Empty file.\n");
        return;
    }

    int i;
    char buffer[block_size];

    for (i = 0; i < EXT4_NUM_BLOCKS && inode->i_block[i] != 0; i++) {
        fseek(image, DATA_BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
        fread(buffer, 1, block_size, image);
        printf("%s", buffer);
    }
}

void ext4_ls(FILE *image, struct super_block_t *superblock, int inode_number) {
    // Lê o inode do diretório
    struct inode_t directory_inode;
    fseek(image, INODE_OFFSET(inode_number), SEEK_SET); 
    fread(&directory_inode, sizeof(struct inode_t), 1, image);

    // Verifica se é um diretório
    if ((directory_inode.i_mode & S_IFMT) != EXT4_S_IFDIR) {
        fprintf(stderr, "Erro: O inode não é um diretório.\n", directory_inode.i_mode);
        int file_type = directory_inode.i_mode & S_IFMT;
        printf("%d\n", inode_number);
        printf("%o\n", file_type);
        printf("%o\n", S_IFMT);
        printf("%o\n", EXT4_S_IFDIR);
        return;
    }
    // Lê os blocos de dados do diretório
    int i, block_size = 1024 << superblock->s_log_block_size;
    for (i = 0; i < EXT4_NUM_BLOCKS && directory_inode.i_block[i] != 0; ++i) {
        // Exibe os arquivos do diretório
        ext4_ls_block(image, &directory_inode, directory_inode.i_block[i]);
    }
}

void ext4_ls_block(FILE *image, struct inode_t *directory_inode, int block_number) {
    int block_size = 1024 << directory_inode->osd2.linux2.l_i_blocks_high;
    int num_entries = block_size / sizeof(struct dir_entry_2_t);

    // Aloca espaço para as entradas do diretório
    struct dir_entry_2_t *dir_entries = malloc(block_size);
    if (!dir_entries) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    // Lê as entradas do diretório
    fseek(image, DATA_BLOCK_OFFSET(block_number), SEEK_SET);
    fread(dir_entries, block_size, 1, image);

    // Itera sobre as entradas do diretório
    int i;
    for (i = 0; i < num_entries; ++i) {
        // Verifica se a entrada do diretório está válida
        if (dir_entries[i].inode != 0) {
            // Exibe informações da entrada do diretório
            printf("%s\n", dir_entries[i].name);
        }
    }

    // Libera a memória alocada
    free(dir_entries);
} 