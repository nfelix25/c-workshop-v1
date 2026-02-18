#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

const char *path = "index.html";
#define BUFFER_SIZE 500

int main() {
  int err_fd = open("ERRRRR", O_RDONLY);
  int fd = open(path, O_RDONLY);

  if (err_fd == -1) {
    printf("Error: %d\nCause: %s\n\n", err_fd, strerror(errno));
  }

  printf("FD: %d\n\n", fd);

  char buffer[BUFFER_SIZE];
  // ssize_t is a signed int useful when -1 as an error is possible
  ssize_t bytes_read = read(10, buffer, BUFFER_SIZE);

  if (bytes_read == -1) {
    printf("Error: %zd bytes read.\nCause: %s\n\n", bytes_read, strerror(errno));
  } else {
    printf("Buffer size: %d\nActual size: %zd\n\n", BUFFER_SIZE, bytes_read);
  }

  ssize_t bytes_read2 = read(fd, buffer, BUFFER_SIZE);

  if (bytes_read2 == -1) {
    printf("Error: %zd bytes read.\nCause: %s\n\n", bytes_read2, strerror(errno));
  } else {
    printf("Buffer size: %d\nActual size: %zd\n\n", BUFFER_SIZE, bytes_read2);
  }

  struct my_stat {
    dev_t     st_dev; // ID of device w/file on it
    ino_t     st_ino; // inode number
    mode_t    st_mode; // protection
    nlink_t   st_nlink; // number of hard links
    uid_t     st_uid; // user ID of owner
    gid_t     st_gid; // group ID of owner
    dev_t     st_rdev; // Device ID
    time_t    my_st_atime; // last access time
    long      st_atimensec; // nsec of last access
    time_t    my_st_mtime; // last modification time
    long      st_mtimensec; // last data modification nsec
    time_t    my_st_ctime; // last status change time
    long      st_ctimensec; // nsec of last status change
    off_t     st_size; // total size, in bytes
    blksize_t st_blksize; // block size for I/O
  }; // Doesnt work but god for reference

  struct stat metadata;
  // struct my_stat my_metadata;

  // fstat mutates metadata directly, return only used for error handling
  // Does not return address becuase memory from func calls is freed
  if (fstat(fd, &metadata) == -1) {
    // Error
    printf("Error: %d\nCause: %s\n\n", errno, strerror(errno));
  }

  // fstat(fd, &my_metadata);

  // my_metadata.my_st_atime = metadata.st_atime;
  // my_metadata.my_st_mtime = metadata.st_mtime;
  // my_metadata.my_st_ctime = metadata.st_ctime;

  // printf("%zd", sizeof(my_metadata));

  printf("Device ID: %d\nInode Number: %llu\nProtection: %d\nHard Links: %d\nUser ID: %d\nGroup ID: %d\nSize: %lld\nBlock Size: %d\nAccess Time: %ld\nModification Time: %ld\nStatus Change Time: %ld\n\n", metadata.st_dev, metadata.st_ino, metadata.st_mode, metadata.st_nlink, metadata.st_uid, metadata.st_gid, metadata.st_size, metadata.st_blksize, metadata.st_atime, metadata.st_mtime, metadata.st_ctime);

  // printf("Device ID: %d\nInode Number: %llu\nProtection: %d\nHard Links: %d\nUser ID: %d\nGroup ID: %d\nSize: %lld\nBlock Size: %d\nAccess Time: %ld\nModification Time: %ld\nStatus Change Time: %ld\n\n", my_metadata.st_dev, my_metadata.st_ino, my_metadata.st_mode, my_metadata.st_nlink, my_metadata.st_uid, my_metadata.st_gid, my_metadata.st_size, my_metadata.st_blksize, my_metadata.my_st_atime, my_metadata.my_st_mtime, my_metadata.my_st_ctime);

  struct stat copy = metadata;

  copy.st_blocks = 0;

  printf("Original: %lld\nCopy: %lld\n\n", metadata.st_blocks, copy.st_blocks);

  struct stat *ref = &metadata;

  // ref->st_blocks equivalent to (*ref).st_blocks
  ref->st_blocks = 0;

  printf("Original: %lld\nRef: %lld\n\n", metadata.st_blocks, ref->st_blocks);

  char sized_buffer[metadata.st_size + 1];

  ssize_t sized_bytes_read_before_lseek = read(fd, sized_buffer, metadata.st_size);

  printf("Size: %lld\nBytes read without lseek: %zd\n\n", metadata.st_size, sized_bytes_read_before_lseek);

  // File descriptor position must be reset
  lseek(fd, 0, SEEK_SET);
  // lseek using CUR whence/starting point
  // lseek(fd, metadata.st_size * -1, SEEK_CUR);

  ssize_t sized_bytes_read = read(fd, sized_buffer, metadata.st_size);
  sized_buffer[metadata.st_size] = '\0';

  printf("Size: %lld\nBytes read after lseek: %zd\nBuffer contents: %s\n\n", metadata.st_size, sized_bytes_read, sized_buffer);

  close(fd);

  return 0;
}
