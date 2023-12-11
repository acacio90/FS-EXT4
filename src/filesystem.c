#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
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
