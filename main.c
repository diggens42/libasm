/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:44:39 by fwahl             #+#    #+#             */
/*   Updated: 2025/09/23 19:42:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void tests_write(int fd, const void *buf, size_t count, const char *description)
{
    // Save original file position for file descriptors
    off_t orig_pos = -1;
    if (fd > 2) {
        orig_pos = lseek(fd, 0, SEEK_CUR);
    }
    
    // Test standard write
    errno = 0;
    ssize_t original = write(fd, buf, count);
    int original_errno = errno;
    
    // Reset file position if applicable
    if (fd > 2 && orig_pos != -1) {
        lseek(fd, orig_pos, SEEK_SET);
    }
    
    // Test custom write
    errno = 0;
    ssize_t custom = ft_write(fd, buf, count);
    int custom_errno = errno;
    
    printf("Testing: %s\n", description);
    printf("  FD: %d, Buffer: \"%.*s\", Count: %zu\n", 
           fd, (int)count, (char*)buf, count);
    printf("  Expected: %zd (errno: %d)\n", original, original_errno);
    printf("  Actual:   %zd (errno: %d)\n", custom, custom_errno);
    printf("  Result:   %s\n\n",
        (original == custom && original_errno == custom_errno) 
        ? "PASS ✓" : "FAIL ✗");
    
    assert(original == custom);
    assert(original_errno == custom_errno);
}

static void tests_write_errno(int fd, const void *buf, size_t count, const char *description)
{
    // Test standard write for errno
    errno = 0;
    ssize_t original = write(fd, buf, count);
    int original_errno = errno;
    
    // Test custom write for errno
    errno = 0;
    ssize_t custom = ft_write(fd, buf, count);
    int custom_errno = errno;
    
    printf("Testing errno: %s\n", description);
    printf("  FD: %d, Buffer: %p, Count: %zu\n", fd, buf, count);
    printf("  Expected return: %zd\n", original);
    printf("  Actual return:   %zd\n", custom);
    printf("  Expected errno: %d (%s)\n", 
           original_errno, strerror(original_errno));
    printf("  Actual errno:   %d (%s)\n", 
           custom_errno, strerror(custom_errno));
    printf("  Result:   %s\n\n",
        (original == custom && original_errno == custom_errno) 
        ? "PASS ✓" : "FAIL ✗");
    
    assert(original == custom);
    assert(original_errno == custom_errno);
}

static void test_file_write(void)
{
    const char *test_file = "test_write.txt";
    
    // Create/open a test file
    int fd = open(test_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create test file");
        return;
    }
    
    printf("=== Testing ft_write with files ===\n\n");
    
    // Test writing to file
    tests_write(fd, "Hello", 5, "Write 'Hello' to file");
    tests_write(fd, " World!", 7, "Write ' World!' to file");
    tests_write(fd, "", 0, "Write empty string to file (0 bytes)");
    tests_write(fd, "Line1\nLine2\n", 12, "Write with newlines");
    
    // Test writing binary data
    unsigned char binary_data[] = {0x00, 0xFF, 0xAA, 0x55, 0x01};
    tests_write(fd, binary_data, sizeof(binary_data), "Write binary data");
    
    // Close and verify file content
    close(fd);
    
    // Read back and verify
    fd = open(test_file, O_RDONLY);
    if (fd != -1) {
        char buffer[256] = {0};
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        printf("File content verification:\n");
        printf("  Bytes written total: %zd\n", bytes_read);
        printf("  Content (text part): \"%.12s\"\n\n", buffer);
        close(fd);
    }
    
    // Clean up
    unlink(test_file);
}

static void test_large_write(void)
{
    printf("=== Testing ft_write with large buffer ===\n\n");
    
    // Create a large buffer
    size_t large_size = 8192;  // 8KB
    char *large_buffer = malloc(large_size);
    if (!large_buffer) {
        printf("Failed to allocate large buffer\n");
        return;
    }
    
    // Fill buffer with pattern
    for (size_t i = 0; i < large_size; i++) {
        large_buffer[i] = 'A' + (i % 26);
    }
    
    // Test with stdout (redirecting to /dev/null to avoid flooding terminal)
    int devnull = open("/dev/null", O_WRONLY);
    if (devnull != -1) {
        tests_write(devnull, large_buffer, large_size, "Write 8KB to /dev/null");
        tests_write(devnull, large_buffer, 4096, "Write 4KB to /dev/null");
        tests_write(devnull, large_buffer, 1, "Write 1 byte from large buffer");
        close(devnull);
    }
    
    free(large_buffer);
}

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


        printf("=== Testing ft_write vs standard write ===\n\n");
    
    // Test writing to stdout
    printf("--- Testing stdout (fd=1) ---\n");
    tests_write(1, "Test stdout\n", 12, "Write to stdout");
    tests_write(1, "", 0, "Write empty string to stdout");
    tests_write(1, "A", 1, "Write single character to stdout");
    tests_write(1, "Hello, World!\n", 14, "Write greeting to stdout");
    
    // Test writing to stderr
    printf("\n--- Testing stderr (fd=2) ---\n");
    tests_write(2, "Test stderr\n", 12, "Write to stderr");
    
    // Test with special characters
    printf("\n--- Testing special characters ---\n");
    tests_write(1, "Tab:\tNewline:\n", 15, "Special characters");
    tests_write(1, "\x01\x02\x03", 3, "Non-printable characters");
    
    // Test file operations
    test_file_write();
    
    // Test large writes
    test_large_write();
    
    // Test error conditions
    printf("=== Testing ft_write error handling (errno) ===\n\n");
    
    // Test with invalid file descriptor
    tests_write_errno(-1, "test", 4, "Invalid fd (-1)");
    tests_write_errno(999, "test", 4, "Invalid fd (999)");
    
    // Test with NULL buffer (should set EFAULT)
    tests_write_errno(1, NULL, 5, "NULL buffer");
    
    // Test with closed file descriptor
    int fd = open("/tmp/test_ft_write.tmp", O_CREAT | O_WRONLY, 0644);
    if (fd != -1) {
        close(fd);
        tests_write_errno(fd, "test", 4, "Closed file descriptor");
        unlink("/tmp/test_ft_write.tmp");
    }
    
    // Test with read-only file descriptor
    fd = open("/dev/null", O_RDONLY);
    if (fd != -1) {
        tests_write_errno(fd, "test", 4, "Write to read-only fd");
        close(fd);
    }
    
    // Test writing to a directory (should fail)
    fd = open(".", O_RDONLY);
    if (fd != -1) {
        tests_write_errno(fd, "test", 4, "Write to directory fd");
        close(fd);
    }
    
    printf("=== Testing edge cases ===\n\n");
    
    // Test with very large count (but valid buffer)
    char small_buf[10] = "small";
    tests_write(1, small_buf, 5, "Normal write of small buffer");
    
    // Test partial writes scenarios
    const char *long_string = "This is a longer string for testing partial writes\n";
    tests_write(1, long_string, strlen(long_string), "Long string write");
    
    // Test with zero count but valid buffer
    tests_write(1, "valid buffer", 0, "Zero count with valid buffer");
    return (0);
}
