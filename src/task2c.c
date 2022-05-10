#include "util.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SYS_EXIT 1
#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CLOSE 6
#define SYS_GETDENTS 0x8d

struct linux_dirent {
               unsigned long  d_ino;     /* Inode number */
               unsigned long  d_off;     /* Offset to next linux_dirent */
               unsigned short d_reclen;  /* Length of this linux_dirent */
               char           d_name[];  /* Filename (null-terminated) */
                                 /* length is actually (d_reclen - 2 -
                                    offsetof(struct linux_dirent, d_name)) */
               /*
               char           pad;       // Zero padding byte
               char           d_type;    // File type (only since Linux
                                         // 2.6.4); offset is (d_reclen - 1)
               */
           };

typedef struct linux_dirent dirnet;

int system_call();


int main(int argc, char **argv)
{

    int nread, fd, bpos;
    struct linux_dirent *d;

    int BUF_SIZE = 8192;
    int arg_index = 1;
    int output_fd = STDOUT;
    char buf[BUF_SIZE];

    char * ten_spaces = "            ";
    char* new_line = "\n";
    char *prefix = "";

    while (arg_index < argc)
	{
		if (*(argv[arg_index] + 1) == 'p')
		{
			prefix = argv[arg_index] + 2;
			arg_index++;
		}
		else
		{
			arg_index++;
		}
		
	}

    system_call(SYS_WRITE, output_fd, prefix, strlen(prefix));
	system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));


    fd = system_call(SYS_OPEN, ".", 0 , 0);
    nread = system_call(SYS_GETDENTS, fd, buf, BUF_SIZE);
    if (nread == -1)
    {
        system_call(SYS_WRITE,STDOUT, "error-getdents",BUF_SIZE);
        return 1;
    }
	system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
    system_call(SYS_WRITE,output_fd, "file type    offset    d_name\n",31);
    for (bpos = 0; bpos < nread;) {
        d = (struct linux_dirent *) (buf + bpos);
        if (strncmp(prefix, d->d_name, strlen(prefix)))
        {
            bpos += d->d_reclen;
            continue;
        }
        system_call(SYS_WRITE, output_fd, itoa(d->d_reclen), 1);
        system_call(SYS_WRITE, output_fd, ten_spaces, strlen(ten_spaces));
        system_call(SYS_WRITE, output_fd, itoa(d->d_off), 1);
        system_call(SYS_WRITE, output_fd, ten_spaces, strlen(ten_spaces));
        system_call(SYS_WRITE, output_fd, d->d_name, strlen(d->d_name));
        system_call(SYS_WRITE, output_fd, new_line, strlen(new_line));
        bpos += d->d_reclen;
    }
    return 0;
}