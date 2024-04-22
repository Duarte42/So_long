#include <stdio.h>

int main()
{
    FILE *file;
    char *path = "./src/file.txt";

        file = fopen(path, "r"); // Attempt to open the file for reading
    if (file)
    {
        printf("File exists and can be opened.\n");
        fclose(file);
    }
    else
    {
        printf("Failed to open file. Please check the path.\n");
    }

    return 0;
}
