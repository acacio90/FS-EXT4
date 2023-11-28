#ifndef FILESYSTEM_H
#define FILESYSTEM_H

struct ext4_superblock {
    // Adicionar os campos necessários do superbloco
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

#endif
