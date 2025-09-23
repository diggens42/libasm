/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:44:39 by fwahl             #+#    #+#             */
/*   Updated: 2025/09/23 19:14:14 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void tests_strcmp(const char *s1, const char *s2, const char *description)
{
    int original = strcmp(s1, s2);
    int custom   = ft_strcmp(s1, s2);

    printf("Testing: %s\n", description);
    printf("  String 1: \"%s\"\n", s1);
    printf("  String 2: \"%s\"\n", s2);
    printf("  Expected: %d\n", original);
    printf("  Actual:   %d\n", custom);
    printf("  Result:   %s\n\n",
        ((original == 0 && custom == 0) || (original < 0 && custom < 0) || (original > 0 && custom > 0))
        ? "PASS ✓" : "FAIL ✗");

    // Assert that the signs match
    assert((original == 0 && custom == 0) || (original < 0 && custom < 0) || (original > 0 && custom > 0));
}

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

    
    printf("=== Testing ft_strcmp vs standard strcmp ===\n\n");
    tests_strcmp("", "", "Empty strings");
    tests_strcmp("H", "H", "Single character equal");
    tests_strcmp("Hello", "Hello", "Equal words");
    tests_strcmp("Hello", "Hell", "Prefix comparison");
    tests_strcmp("Apple", "Banana", "Different words");
    tests_strcmp("Banana", "Apple", "Reverse different words");
    tests_strcmp("Hello", "hello", "Case-sensitive comparison");
    tests_strcmp("", "Non-empty", "Empty vs non-empty");
    tests_strcmp("Non-empty", "", "Non-empty vs empty");
    tests_strcmp("123", "1234", "Numbers, prefix case");
    tests_strcmp("abc\xFF", "abc\x7F", "High-bit character comparison");

    return (0);
}
