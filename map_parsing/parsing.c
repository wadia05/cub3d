#include "../mandatory/cub3d.h"

int word_count(char **str)
{
    int i = 0;
    while (str[i] != NULL)
    {
        i++;
    }
    return (i);
}

int color_erorr(char *str)
{
    int i = 0;
    int cont = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ',')
            cont++;
        i++;
    }
    if (cont > 2)
    {
        print_error("too many commas");
        return 1;
    }
    return 0;
}

char *join_color(char **stc)
{
    char *color = NULL;
    char *temp;
    int i = 1;

    while (stc[i] != NULL)
    {
        temp = ft_strjoin(color, stc[i]);
        free(color);
        color = temp;
        i++;
    }
    return color;
}
void free_splaited(char **splt)
{
    int i = 0;
    while (splt[i] != NULL)
    {
        free(splt[i]);
        i++;
    }
}
int print_error(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

int is_valid_colors(char *str_color, color_t *color_)
{
    if (color_erorr(str_color) == 1)
        return 1;
    char **color = ft_split(str_color, ',');
    if (color == NULL)
    {
        print_error("split\n");
        return 1;
    }
    if (word_count(color) != 3)
    {
        print_error("you need 3 color values R G B and the values should be between 0 and 255\n");
        free_splaited(color);
        return 1;
    }
    color_->r = ft_atoi(color[0]);
    color_->g = ft_atoi(color[1]);
    color_->b = ft_atoi(color[2]);
    if ((color_->r < 0 || color_->r > 255) || (color_->g < 0 || color_->g > 255) || (color_->b < 0 || color_->b > 255))
    {
        print_error("color values should be between 0 and 255\n");
        free_splaited(color);
        return 1;
    }
    free_splaited(color);
    return 0;
}

int paths_check(map_t *stc)
{
    if (open(stc->no, O_RDONLY) == -1)
    {
        print_error("NO path not valid\n");
        return (1);
    }
    if (open(stc->so, O_RDONLY) == -1)
    {
        print_error("SO path not valid\n");
        return (1);
    }
    if (open(stc->we, O_RDONLY) == -1)
    {
        print_error("WE path not valid\n");
        return (1);
    }
    if (open(stc->ea, O_RDONLY) == -1)
    {
        print_error("EA path not valid\n");
        return (1);
    }
    return (0);
}

void remove_newline(char *line)
{
    int i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            break;
        }
        i++;
    }
}

int check_exention_file(char *ext)
{
    trim_end(ext);
    int len = ft_strlen(ext);
    if (ext[len - 1] == 'b' && ext[len - 2] == 'u' && ext[len - 3] == 'c' && ext[len - 4] == '.')
    {
        print_error("good extension");
    }
    else
    {
        print_error("bad extension");
        exit(1);
    }
    return 0;
}

void free_struct(map_t *hd, int file)
{
    close(file);
    free(hd->c_color);
    free(hd->f_color);
    free(hd->f);
    free(hd->c);
    free(hd->no);
    free(hd->so);
    free(hd->we);
    free(hd->ea);
    free(hd);
}

void texture_data(map_t *stc, char **texture_dt, char *line, int file)
{
    if (*texture_dt != NULL)
    {
        free_struct(stc, file);
        exit(write(1, "duplicated\n", 11));
    }
    *texture_dt = ft_strdup(line);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        write(1, "Usage: ./program filename\n", 26);
        return 1;
    }
    check_exention_file(av[1]);
    map_t *stc = malloc(sizeof(map_t));
    if (stc == NULL)
    {
        write(1, "malloc\n", 7);
        return 1;
    }
    ft_memset(stc, 0, sizeof(map_t));
    stc->f_color = malloc(sizeof(color_t));
    stc->c_color = malloc(sizeof(color_t));
    if (stc->f_color == NULL || stc->c_color == NULL)
    {
        write(1, "malloc\n", 7);
        free(stc);
        return 1;
    }
    ft_memset(stc->f_color, 0, sizeof(color_t));
    ft_memset(stc->c_color, 0, sizeof(color_t));
    int file = open(av[1], O_RDONLY);
    if (file == -1)
    {
        write(1, "file\n", 5);
        free(stc->f_color);
        free(stc->c_color);
        free(stc);
        return 1;
    }

    char *line = NULL;
    char **line2 = NULL;

    line = get_next_line(file);
    while (line != NULL)
    {
        if (stc->c != NULL && stc->f != NULL && stc->no != NULL && stc->so != NULL && stc->we != NULL && stc->ea != NULL)
        {
            printf("start parsing of the map\n");
            parse_map(file, stc);
            break;
        }
        if (line[0] == '\n')
        {
            free(line);
            line = get_next_line(file);
            continue;
        }

        remove_newline(line);
        line2 = ft_split(line, ' ');
        free(line);
        line = NULL;
        if (line2 == NULL)
        {
            write(1, "split\n", 6);
            free_struct(stc, file);
            break;
        }
        if (ft_strncmp(line2[0], "F", ft_strlen(line2[0])) == 0)
        {
            stc->f = join_color(line2);
            if (is_valid_colors(stc->f, stc->f_color) == 1)
            {
                free(stc->f);
                break;
            }
        }
        else if (ft_strncmp(line2[0], "C", ft_strlen(line2[0])) == 0)
        {
            stc->c = join_color(line2);
            if (is_valid_colors(stc->c, stc->c_color) == 1)
            {
                free(stc->c);
                break;
            }
        }
        else if (word_count(line2) != 2)
        {
            print_error("there is more than one path\n");
            break;
        }

        if (ft_strncmp(line2[0], "NO", ft_strlen(line2[0])) == 0)
            texture_data(stc, &stc->no, line2[1], file);
        else if (ft_strncmp(line2[0], "SO", ft_strlen(line2[0])) == 0)
            texture_data(stc, &stc->so, line2[1], file);
        else if (ft_strncmp(line2[0], "WE", ft_strlen(line2[0])) == 0)
            texture_data(stc, &stc->we, line2[1], file);
        else if (ft_strncmp(line2[0], "EA", ft_strlen(line2[0])) == 0)
            texture_data(stc, &stc->ea, line2[1], file);

        free_splaited(line2);

        line = get_next_line(file);
    }

    if (paths_check(stc) == 1)
    {
        free_struct(stc, file);
        return 1;
    }
    free_struct(stc, file);
    return 0;
}