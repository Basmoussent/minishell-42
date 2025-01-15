/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   ft_exit_test.c          :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2025/01/15 14:26:28 by bdenfir           #+#  #+#          */
/*   Updated: 2025/01/15 14:29:02 by bdenfir          ###   ########.fr    */
/*                                      */
/* ************************************************************************** */

#include "minishell.h"

int run_test(const char *input, const char *expected_result)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        int status = ft_exit((char *)input);
        printf(COLOR_YELLOW "ft_exit result: %d\n" COLOR_RESET, status);
        exit(status);
    }
    else if (pid > 0)
    {
        int status;
        wait(&status);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            printf(COLOR_CYAN "Input: \"%s\"\n" COLOR_RESET, input);

            // Compare expected and actual results
            if (atoi(expected_result) == exit_status)
            {
                printf(COLOR_GREEN "PASS" COLOR_RESET);
                printf(COLOR_CYAN " | Expected: %s | Returned: %d\n" COLOR_RESET,
                       expected_result, exit_status);
                printf("------------------------------------\n");
                return 1;
            }
            else
            {
                printf(COLOR_RED "FAIL" COLOR_RESET);
                printf(COLOR_CYAN " | Expected: %s | Returned: %d\n" COLOR_RESET,
                       expected_result, exit_status);
                printf("------------------------------------\n");
                return 0;
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

int ft_exit_test(void)
{
    int passed = 0;
    int failed = 0;

    printf(COLOR_CYAN "Testing ft_exit...\n" COLOR_RESET);

    passed += run_test("exit", "0");
    passed += run_test("exit 0", "0");
    passed += run_test("exit 42", "42");
    passed += run_test("exit -1", "255");
    passed += run_test("exit 256", "0");
    passed += run_test("exit 9223372036854775807", "255");
    passed += run_test("exit -9223372036854775808", "0");
    passed += run_test("exit abc", "2");
    passed += run_test("exit 123 abc", "1");
    passed += run_test("exit 9223372036854775808", "2");
    passed += run_test("exit -9223372036854775809", "2");

    // Summary
    printf(COLOR_CYAN "\nTest Summary:\n" COLOR_RESET);
    printf(COLOR_GREEN "Passed: %d\n" COLOR_RESET, passed);
    printf(COLOR_RED "Failed: %d\n" COLOR_RESET, passed - 11);

    return (failed == 0) ? 0 : 1;
}
