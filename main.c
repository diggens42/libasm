/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:44:39 by fwahl             #+#    #+#             */
/*   Updated: 2025/09/23 16:49:45 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void tests_strcpy(const char *src, const char *description)
{
    char original_dest[256];
    char custom_dest[256];

    strcpy(original_dest, src);
    ft_strcpy(custom_dest, src);

    printf("Testing: %s\n", description);
    printf("  Source: \"%s\"\n", src);
    printf("  Expected: \"%s\"\n", original_dest);
    printf("  Actual:   \"%s\"\n", custom_dest);
    printf("  Result:   %s\n\n",
        (strcmp(original_dest, custom_dest) == 0) ? "PASS ✓" : "FAIL ✗");

    assert(strcmp(original_dest, custom_dest) == 0);
}


static void tests_strlen(const char *str,  const char *description)
{
    size_t  original = strlen(str);
    size_t  custom   = ft_strlen(str);

    printf("Testing: %s\n", description);
    printf("  String: \"%s\"\n", str);
    printf("  Expected: %zu\n", original);
    printf("  Actual:   %zu\n", custom);
    printf("  Result:   %s\n\n", (original == custom) ? "PASS ✓" : "FAIL ✗");

    assert(original == custom);
}

int main()
{
    printf("=== Testing ft_strlen vs standard strlen ===\n\n");
    tests_strlen("", "Empty string");
    tests_strlen("H", "Single character");
    tests_strlen("Hi", "Two characters");
    tests_strlen("Hello", "Normal word");
    tests_strlen("Hello, World!", "String with punctuation");
    tests_strlen("This is a longer string to test", "Longer string");
    tests_strlen("String with numbers 123456", "String with numbers");
    tests_strlen("Special chars: !@#$%^&*()", "Special characters");


    printf("=== Testing ft_strcpy vs standard strcpy ===\n\n");
    tests_strcpy("", "Empty string");
    tests_strcpy("H", "Single character");
    tests_strcpy("Hi", "Two characters");
    tests_strcpy("Hello", "Normal word");
    tests_strcpy("Hello, World!", "String with punctuation");
    tests_strcpy("This is a longer string to test", "Longer string");
    tests_strcpy("String with numbers 123456", "String with numbers");
    tests_strcpy("Special chars: !@#$%^&*()", "Special characters");

    return (0);
}
