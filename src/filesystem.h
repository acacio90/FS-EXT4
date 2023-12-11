#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

extern int current_directory_inode;

// Constantes para tipos de arquivo no sistema de arquivos EXT4
#define EXT4_S_IFREG  0x8000 // Arquivo regular
#define EXT4_S_IFDIR  0x4000 // Diretório
#define EXT4_S_IFCHR  0x2000 // Dispositivo de caractere
#define EXT4_S_IFBLK  0x6000 // Dispositivo de bloco
#define EXT4_S_IFIFO  0x1000 // Pipe FIFO
#define EXT4_S_IFSOCK 0xC000 // Socket
#define S_IFMT  0xF000

// Constantes para permissões no sistema de arquivos EXT4
#define EXT4_S_IRUSR 0x0100 // Leitura pelo dono
#define EXT4_S_IWUSR 0x0080 // Escrita pelo dono
#define EXT4_S_IXUSR 0x0040 // Execução pelo dono
#define EXT4_S_IRGRP 0x0020 // Leitura pelo grupo
#define EXT4_S_IWGRP 0x0010 // Escrita pelo grupo
#define EXT4_S_IXGRP 0x0008 // Execução pelo grupo
#define EXT4_S_IROTH 0x0004 // Leitura por outros
#define EXT4_S_IWOTH 0x0002 // Escrita por outros
#define EXT4_S_IXOTH 0x0001 // Execução por outros

#define EXT4_ROOT_INO 2  // ou o valor correto para o inode raiz no seu sistema de arquivos

#define EXT4_NAME_LENGTH 255
#define EXT4_NUM_BLOCKS 15
#define SUPERBLOCK_OFFSET 1024
#define GROUP_DESCRIPTORS_OFFSET 2048
#define INODE_OFFSET(inode_number) (1024 + inode_number * sizeof(struct inode_t))
#define DATA_BLOCK_OFFSET(block_number) (1024 + block_number * BLOCK_SIZE)

#define BLOCK_SIZE 4096

struct super_block_t {
    int32_t s_inodes_count;
    int32_t s_blocks_count_lo;
    int32_t s_r_blocks_count_lo;
    int32_t s_free_blocks_count_lo;
    int32_t s_free_inodes_count;
    int32_t s_first_data_block;
    int32_t s_log_block_size;
    int32_t s_log_cluster_size;
    int32_t s_blocks_per_group;
    int32_t s_clusters_per_group;
    int32_t s_inodes_per_group;
    int32_t s_mtime;
    int32_t s_wtime;
    int16_t s_mnt_count;
    int16_t s_max_mnt_count;
    int16_t s_magic;
    int16_t s_state;
    int16_t s_errors;
    int16_t s_minor_rev_level;
    int32_t s_lastcheck;
    int32_t s_checkinterval;
    int32_t s_creator_os;
    int32_t s_rev_level;
    int16_t s_def_resuid;
    int16_t s_def_resgid;
    int32_t s_first_ino;
    int16_t s_inode_size;
    int16_t s_block_group_nr;
    int32_t s_feature_compat;
    int32_t s_feature_incompat;
    int32_t s_feature_ro_compat;
    uint8_t s_uuid[16];
    char s_volume_name[16];
    char s_last_mounted[64];
    int32_t s_algorithm_usage_bitmap;
    uint8_t s_prealloc_blocks;
    uint8_t s_prealloc_dir_blocks;
    int16_t s_reserved_gdt_blocks;
    uint8_t s_journal_uuid[16];
    int32_t s_journal_inum;
    int32_t s_journal_dev;
    int32_t s_last_orphan;
    int32_t s_hash_seed[4];
    uint8_t s_def_hash_version;
    uint8_t s_jnl_backup_type;
    int16_t s_desc_size;
    int32_t s_default_mount_opts;
    int32_t s_first_meta_bg;
    int32_t s_mkfs_time;
    int32_t s_jnl_blocks[17];
    int32_t s_blocks_count_hi;
    int32_t s_r_blocks_count_hi;
    int32_t s_free_blocks_count_hi;
    int16_t s_min_extra_isize;
    int16_t s_want_extra_isize;
    int32_t s_flags;
    int16_t s_raid_stride;
    int16_t s_mmp_interval;
    int64_t s_mmp_block;
    int32_t s_raid_stripe_width;
    uint8_t s_log_groups_per_flex;
    uint8_t s_checksum_type;
    int16_t s_reserved_pad;
    int64_t s_kbytes_written;
    int32_t s_snapshot_inum;
    int32_t s_snapshot_id;
    int64_t s_snapshot_r_blocks_count;
    int32_t s_snapshot_list;
    int32_t s_error_count;
    int32_t s_first_error_time;
    int32_t s_first_error_ino;
    int64_t s_first_error_block;
    uint8_t s_first_error_func[32];
    int32_t s_first_error_line;
    int32_t s_last_error_time;
    int32_t s_last_error_ino;
    int32_t s_last_error_line;
    int64_t s_last_error_block;
    uint8_t s_last_error_func[32];
    uint8_t s_mount_opts[64];
    int32_t s_usr_quota_inum;
    int32_t s_grp_quota_inum;
    int32_t s_overhead_blocks;
    int32_t s_backup_bgs[2];
    uint8_t s_encrypt_algos[4];
    uint8_t s_encrypt_pw_salt[16];
    int32_t s_lpf_ino;
    int32_t s_prj_quota_inum;
    int32_t s_checksum_seed;
    int32_t s_reserved[98];
    int32_t s_checksum;
};

struct block_group_descriptors {
    int32_t bg_block_bitmap_lo;
    int32_t bg_inode_bitmap_lo;
    int32_t bg_inode_table_lo;
    int16_t bg_free_blocks_count_lo;
    int16_t bg_free_inodes_count_lo;
    int16_t bg_used_dirs_count_lo;
    int16_t bg_flags;
    int32_t bg_exclude_bitmap_lo;
    int16_t bg_block_bitmap_csum_lo;
    int16_t bg_inode_bitmap_csum_lo;
    int16_t bg_itable_unused_lo;
    int16_t bg_checksum;
    int32_t bg_block_bitmap_hi;
    int32_t bg_inode_bitmap_hi;
    int32_t bg_inode_table_hi;
    int16_t bg_free_blocks_count_hi;
    int16_t bg_free_inodes_count_hi;
    int16_t bg_used_dirs_count_hi;
    int16_t bg_itable_unused_hi;
    int32_t bg_exclude_bitmap_hi;
    int16_t bg_block_bitmap_csum_hi;
    int16_t bg_inode_bitmap_csum_hi;
    uint32_t bg_reserved;
};

struct inode_t {
    int16_t i_mode;
    int16_t i_uid;
    int32_t i_size_lo;
    int32_t i_atime;
    int32_t i_ctime;
    int32_t i_mtime;
    int32_t i_dtime;
    int16_t i_gid;
    int16_t i_links_count;
    int32_t i_blocks_lo;
    int32_t i_flags;
    union {
        struct {
            int32_t l_i_version;
        } linux1;
        struct {
            uint32_t h_i_translator;
        } hurd1;
        struct {
            uint32_t m_i_reserved1;
        } masix1;
    } osd1;
    int32_t i_block[EXT4_NUM_BLOCKS];
    int32_t i_generation;
    int32_t i_file_acl_lo;
    int32_t i_size_high;
    int32_t i_obso_faddr;
    union {
        struct {
            int16_t l_i_blocks_high;
            int16_t l_i_file_acl_high;
            int16_t l_i_uid_high;
            int16_t l_i_gid_high;
            int16_t l_i_checksum_lo;
            int16_t l_i_reserved;
        } linux2;
        struct {
            int16_t h_i_reserved1;
            uint16_t h_i_mode_high;
            uint16_t h_i_uid_high;
            uint16_t h_i_gid_high;
            uint32_t h_i_author;
        } hurd2;
        struct {
            int16_t h_i_reserved1;
            int16_t m_i_file_acl_high;
            uint32_t m_i_reserved2[2];
        } masix2;
    } osd2;
    int16_t i_extra_isize;
    int16_t i_checksum_hi;
    int32_t i_ctime_extra;
    int32_t i_mtime_extra;
    int32_t i_atime_extra;
    int32_t i_crtime;
    int32_t i_crtime_extra;
    int32_t i_version_hi;
    int32_t i_projid;
};

struct extent_header_t {
    int16_t eh_magic;
    int16_t eh_entries;
    int16_t eh_max;
    int16_t eh_depth;
    int32_t eh_generation;
};

struct extent_idx_t {
    int32_t ei_block;
    int32_t ei_leaf_lo;
    int16_t ei_leaf_hi;
    uint16_t ei_unused;
};

struct dir_entry_2_t {
    int32_t inode;
    int16_t rec_len;
    uint8_t name_len;
    uint8_t file_type;
    char name[EXT4_NAME_LENGTH];
};

struct extent_t {
    int32_t ee_block;
    int16_t ee_len;
    int16_t ee_start_hi;
    int32_t ee_start_lo;
};

struct fake_dirent {
    int32_t inode;
    int16_t rec_len;
    uint8_t name_len;
    uint8_t file_type;
};

struct dx_root_info {
    int32_t reserved_zero;
    uint8_t hash_version;
    uint8_t info_length;
    uint8_t indirect_levels;
    uint8_t unused_flags;
};

struct dx_entry {
    int32_t hash;
    int32_t block;
};

struct dx_root_t {
    struct fake_dirent dot;
    char dot_name[4];
    struct fake_dirent dotdot;
    char dotdot_name[4];
    struct dx_root_info info;
    struct dx_entry dx_entries[0];
};

#endif
