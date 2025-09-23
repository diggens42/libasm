/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:44:39 by fwahl             #+#    #+#             */
/*   Updated: 2025/09/23 15:55:03 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

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

    return (0);
}
