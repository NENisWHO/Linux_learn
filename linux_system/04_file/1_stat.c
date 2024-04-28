/*************************************************************************
	> File Name: 1_stat.c
	> Author: 
	> Mail: 
	> Created Time: 2024年04月19日 星期五 19时01分05秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
//crtl + = 文本对其
//条件编译 #if 后为1 执行后面的代码，为0则不执行
#if 0
  struct stat {
      dev_t     st_dev;         /* ID of device containing file */
      ino_t     st_ino;         /* Inode number */
      mode_t    st_mode;        /* File type and mode */
      nlink_t   st_nlink;       /* Number of hard links */
      uid_t     st_uid;         /* User ID of owner */
      gid_t     st_gid;         /* Group ID of owner */
      dev_t     st_rdev;        /* Device ID (if special file) */
      off_t     st_size;        /* Total size, in bytes */
      blksize_t st_blksize;     /* Block size for filesystem I/O */
      blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

      /* Since Linux 2.6, the kernel supports nanosecond
      precision for the following timestamp fields.
      For the details before Linux 2.6, see NOTES. */

      struct timespec st_atim;  /* Time of last access */
      struct timespec st_mtim;  /* Time of last modification */
      struct timespec st_ctim;  /* Time of last status change */

      #define st_atime st_atim.tv_sec      /* Backward compatibility */
      #define st_mtime st_mtim.tv_sec
      #define st_ctime st_ctim.tv_sec
  };
#endif

int main(void) {
    int ret = -1;
    struct stat s;
    
    //获取指定文件的信息
    ret = stat("txt", &s);
    if (ret == -1) {
        perror("stat");
        return 1;
    }
    //文件属性信息
    printf("st_dev: %lu\n", s.st_dev);
    printf("st_ino: %ld\n", s.st_ino);
    printf("st_nlink: %lu\n", s.st_nlink);
    printf("st_uid: %d\n", s.st_uid);
    printf("st_gid: %d\n", s.st_gid);
    printf("st_size: %ld\n", s.st_size);



    return 0;
}

