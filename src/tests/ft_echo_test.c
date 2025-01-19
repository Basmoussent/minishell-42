/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:33:26 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/19 21:37:43 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_echo_test(const char *input, const char *expected_output)
{
    int pipefd[2];
    pid_t pid;
    char buffer[1024];
    int read_bytes;

    if (pipe(pipefd) == -1)
    {
        perror(COLOR_RED "pipe" COLOR_RESET);
        return 0;
    }

    pid = fork();
    if (pid == 0)
    {
        // Child process: redirect stdout and stderr to pipe, then call ft_echo
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);

        ft_echo((char *)input); // Call your echo implementation
        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process: read from pipe and compare output
        close(pipefd[1]); // Close unused write end
        wait(NULL);       // Wait for child to finish

        read_bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);

        if (read_bytes >= 0)
        {
            buffer[read_bytes] = '\0'; // Null-terminate the output

            // Strip trailing newlines and spaces
            char *expected_trimmed = ft_strtrim(expected_output, "\n");
            char *actual_trimmed = ft_strtrim(buffer, "\n");

            printf(COLOR_CYAN "Input: \"%s\"\n" COLOR_RESET, ft_strtrim(input, "\n "));
            printf(COLOR_CYAN "Expected: \"%s\"\n" COLOR_RESET, expected_trimmed);
            printf(COLOR_CYAN "Output:   \"%s\"\n" COLOR_RESET, actual_trimmed);

            if (strcmp(actual_trimmed, expected_trimmed) == 0)
            {
                printf(COLOR_GREEN "PASS\n" COLOR_RESET);
                printf("------------------------------------\n");
                free(expected_trimmed);
                free(actual_trimmed);
                return 1; // Test passed
            }
            else
            {
                printf(COLOR_RED "FAIL\n" COLOR_RESET);
                printf("------------------------------------\n");
                free(expected_trimmed);
                free(actual_trimmed);
                return 0; // Test failed
            }
        }
    }
    else
    {
        perror(COLOR_RED "fork" COLOR_RESET);
        return 0;
    }
    return 0;
}

int ft_echo_test(void)
{
    int passed = 0;
    int failed = 0;

    printf(COLOR_YELLOW "Testing ft_echo...\n" COLOR_RESET);

    printf(COLOR_RED "THIS TEST HAS TO FAIL NO MATTER WHAT\n" COLOR_RESET);
    passed += run_echo_test("echo 123", "\n");
    passed += run_echo_test("echo -n hello world", "hello world");
    passed += run_echo_test("echo hello\\world", "hello\\world\n");
    passed += run_echo_test("echo hello;world", "");
    passed += run_echo_test("echo 'hello ; world'", "hello ; world\n");
    passed += run_echo_test("echo -n \"hello ; world\"", "hello ; world");

    // Summary
    failed = 6 - passed; // Total tests - passed
    printf(COLOR_CYAN "\nTest Summary:\n" COLOR_RESET);
    printf(COLOR_GREEN "Passed: %d\n" COLOR_RESET, passed);
    printf(COLOR_RED "Failed: %d\n" COLOR_RESET, failed);

    return (failed == 0) ? 0 : 1; // Return 0 if all tests passed
}