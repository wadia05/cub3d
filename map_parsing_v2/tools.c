#include "../mandatory/cub3d.h"


void free_split(char **split)
{
    if (!split)
        return;
        
    int i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

int validate_file_extension(char *ext)
{
    trim_end(ext);
    int len = ft_strlen(ext);
    if (ext[len - 1] == 'b' && ext[len - 2] == 'u' && ext[len - 3] == 'c' && ext[len - 4] == '.')
    {
        printf("good trip extension\n");
    }
    else
    {
        print_error("bad trip extension\n");
        exit(1);
    }
    return 0;
}

int word_count(char **str)
{
    int i = 0;
        printf("hello");
    while (str[i] != NULL)
    {
        i++;
    }
    printf("%d\n", i);
    return (i);
}