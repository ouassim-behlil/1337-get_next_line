/* tests/test_main.c
 *
 * Interactive harness for get_next_line.
 * Build with `make` (default target) and run:
 *   ./gnl                        # read from STDIN
 *   ./gnl tests/fixtures/file    # read a file
 *   ./gnl f1 f2                  # alternate reads between files
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static void test_single_fd(const char *filename)
{
    int   fd;
    char  *line;
	int		count = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    printf("===== Reading file: %s =====\n", filename);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("line %d:%s", ++count, line);
        free(line);
    }
    close(fd);
}

static void test_multi_fd(const char *f1, const char *f2)
{
    int   fd1;
    int   fd2;
    char  *line1;
    char  *line2;

    fd1 = open(f1, O_RDONLY);
    fd2 = open(f2, O_RDONLY);
    if (fd1 < 0 || fd2 < 0)
    {
        perror("open");
        if (fd1 >= 0) close(fd1);
        if (fd2 >= 0) close(fd2);
        return;
    }
    printf("===== Alternating read between '%s' and '%s' =====\n", f1, f2);
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    while (line1 || line2)
    {
        if (line1)
        {
            printf("[fd1] %s", line1);
            free(line1);
            line1 = get_next_line(fd1);
        }
        if (line2)
        {
            printf("[fd2] %s", line2);
            free(line2);
            line2 = get_next_line(fd2);
        }
    }
    close(fd1);
    close(fd2);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        char *line;
        printf("===== Reading from STDIN (Ctrl+D to end) =====\n");
        while ((line = get_next_line(0)) != NULL)
        {
            printf("%s", line);
            free(line);
        }
    }
    else if (argc == 2)
    {
        test_single_fd(argv[1]);
    }
    else if (argc == 3)
    {
        test_multi_fd(argv[1], argv[2]);
    }
    else
    {
        for (int i = 1; i < argc; ++i)
            test_single_fd(argv[i]);
    }
    return 0;
}
