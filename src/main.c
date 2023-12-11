#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void show_prompt() {
    printf("ext4shell:[myext4image/] $ ");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *file_name = argv[1];
    FILE *image = fopen(file_name, "rb");

    if (image == NULL) {
        perror("Error opening the image");
        return 1;
    }

    struct super_block_t superblock;
    struct block_group_descriptors descriptors;

    // Read the superblock and block group descriptors
    fseek(image, SUPERBLOCK_OFFSET, SEEK_SET);
    fread(&superblock, sizeof(struct super_block_t), 1, image);

    fseek(image, GROUP_DESCRIPTORS_OFFSET, SEEK_SET);
    fread(&descriptors, sizeof(struct block_group_descriptors), 1, image);

    // Assign the appropriate value to the new s_last_mount_time field
    snprintf(superblock.s_last_mounted, sizeof(superblock.s_last_mounted), "%d", superblock.s_mtime);

    char command[256];

    while (1) {
        show_prompt();
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Ctrl+D or read error, exit the loop
        }

        // Remove the newline character
        command[strcspn(command, "\n")] = '\0';

        // Here you can parse and execute user commands
        // Implement shell logic as needed

        if (strcmp(command, "info") == 0) {
            ext4_info(&superblock);
        } else if (strcmp(command, "exit") == 0) {
            break; // Exit the loop
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    fclose(image);

    return 0;
}
