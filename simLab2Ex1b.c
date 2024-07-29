#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

// Function to encode special characters in a shell string
void encodeShellString(char *dest, const char *src) {
    while (*src) {
        if (*src == ' ' || *src == '!' || *src == '"' || *src == '#' || *src == '$' ||
            *src == '%' || *src == '&' || *src == '\'' || *src == '(' || *src == ')' ||
            *src == '*' || *src == '+' || *src == ',' || *src == '-' || *src == '.' ||
            *src == '/' || *src == ':' || *src == ';' || *src == '<' || *src == '=' ||
            *src == '>' || *src == '?' || *src == '@' || *src == '[' || *src == '\\' ||
            *src == ']' || *src == '^' || *src == '_' || *src == '`' || *src == '{' ||
            *src == '|' || *src == '}' || *src == '~') {
            *dest++ = '\\';
        }
        *dest++ = *src++;
    }
    *dest = '\0';
}

// This program prints the size of a specified file in bytes
int main(int argc, char **argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    // Encode the file name to make it safe for the shell
    char encodedFileName[BUFSIZE];
    encodeShellString(encodedFileName, argv[1]);

    // Construct the command to get the file size
    char cmd[BUFSIZE];
    snprintf(cmd, sizeof(cmd), "wc -c < %s", encodedFileName);

    // Execute the command
    int result = system(cmd);
    if (result == -1) {
        perror("system");
        return -1;
    }

    return 0;
}
