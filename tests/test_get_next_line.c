#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "get_next_line.h"

typedef struct s_file_case
{
	const char		*name;
	const char		*path;
	const char		**expected;
	size_t			expected_count;
}	t_file_case;

static void	assert_true(int condition, const char *message)
{
	if (!condition)
	{
		fprintf(stderr, "[FAIL] %s\n", message);
		exit(EXIT_FAILURE);
	}
}

static void	assert_equals(const char *expected, const char *actual,
		const char *context)
{
	if (!actual)
	{
		fprintf(stderr, "[FAIL] Expected \"%s\" but got NULL in %s\n",
			expected, context);
		exit(EXIT_FAILURE);
	}
	if (strcmp(expected, actual) != 0)
	{
		fprintf(stderr,
			"[FAIL] Mismatch in %s\n  expected: \"%s\"\n  actual:   \"%s\"\n",
			context, expected, actual);
		exit(EXIT_FAILURE);
	}
}

static void	run_file_case(const t_file_case *tc)
{
	size_t	idx;
	char	*line;
	int		fd;

	fprintf(stdout, "[ RUN ] %s\n", tc->name);
	fd = open(tc->path, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "[FAIL] Unable to open %s: %s\n",
			tc->path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	idx = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		assert_true(idx < tc->expected_count,
			"Received more lines than expected");
		assert_equals(tc->expected[idx], line, tc->name);
		free(line);
		idx++;
	}
	close(fd);
	assert_true(idx == tc->expected_count, "Missing lines in output");
	fprintf(stdout, "[ OK  ] %s\n", tc->name);
}

static void	test_invalid_fd(void)
{
	fprintf(stdout, "[ RUN ] invalid_fd\n");
	assert_true(get_next_line(-1) == NULL, "Expected NULL for invalid fd");
	fprintf(stdout, "[ OK  ] invalid_fd\n");
}

static void	test_multi_fd(void)
{
	const char	*expected1[] = {
		"Line one in sample1.\n",
		"Line two in sample1.\n",
		"Line three in sample1.\n"
	};
	const char	*expected2[] = {
		"First line of sample2.\n",
		"Second line.\n",
		"Third line with more words.\n"
	};
	size_t		idx1;
	size_t		idx2;
	char		*line;
	int			fd1;
	int			fd2;

	fprintf(stdout, "[ RUN ] multi_fd_alternating\n");
	fd1 = open("tests/fixtures/sample1.txt", O_RDONLY);
	fd2 = open("tests/fixtures/sample2.txt", O_RDONLY);
	assert_true(fd1 >= 0 && fd2 >= 0, "Failed to open fixture for multi-fd test");
	idx1 = 0;
	idx2 = 0;
	while (idx1 < 3 || idx2 < 3)
	{
		if (idx1 < 3)
		{
			line = get_next_line(fd1);
			assert_equals(expected1[idx1], line, "multi_fd fd1");
			free(line);
			idx1++;
		}
		if (idx2 < 3)
		{
			line = get_next_line(fd2);
			assert_equals(expected2[idx2], line, "multi_fd fd2");
			free(line);
			idx2++;
		}
	}
	assert_true(get_next_line(fd1) == NULL, "Expected NULL after EOF on fd1");
	assert_true(get_next_line(fd2) == NULL, "Expected NULL after EOF on fd2");
	close(fd1);
	close(fd2);
	fprintf(stdout, "[ OK  ] multi_fd_alternating\n");
}

int	main(void)
{
	const char	*sample1_expected[] = {
		"Line one in sample1.\n",
		"Line two in sample1.\n",
		"Line three in sample1.\n"
	};
	const char	*sample2_expected[] = {
		"First line of sample2.\n",
		"Second line.\n",
		"Third line with more words.\n"
	};
	const char	*no_newline_expected[] = {
		"no newline at end"
	};
	const char	*empty_expected[] = {NULL};
	const t_file_case	cases[] = {
	{
		.name = "sample1",
		.path = "tests/fixtures/sample1.txt",
		.expected = sample1_expected,
		.expected_count = sizeof(sample1_expected) / sizeof(sample1_expected[0])
	},
	{
		.name = "sample2",
		.path = "tests/fixtures/sample2.txt",
		.expected = sample2_expected,
		.expected_count = sizeof(sample2_expected) / sizeof(sample2_expected[0])
	},
	{
		.name = "no_newline",
		.path = "tests/fixtures/no_newline.txt",
		.expected = no_newline_expected,
		.expected_count = sizeof(no_newline_expected) / sizeof(no_newline_expected[0])
	},
	{
		.name = "empty_file",
		.path = "tests/fixtures/empty.txt",
		.expected = empty_expected,
		.expected_count = 0
	}
	};
	size_t	i;

	for (i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i)
		run_file_case(&cases[i]);
	test_invalid_fd();
	test_multi_fd();
	fprintf(stdout, "All tests passed.\n");
	return (EXIT_SUCCESS);
}
