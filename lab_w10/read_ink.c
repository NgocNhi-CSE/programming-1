#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tPoint
{
    int x;
    int y;
};

typedef struct tPoint Point;

void draw_bit(char** data, Point* points, int height, int width)
{

}

void draw_to_screen(char** data, int height, int width)
{
    for (int i = 0;i < height;i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (data[i][j])
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: read_ink <file_name>");
        return 0;
    }

    const char* filename = argv[1];

    FILE* f = fopen(filename, "r");

    char s[100];

    Point p_list[1000];

    int index = 0;
    while (fgets(s, 100, f) != NULL)
    {
        printf("%s\n", s);
        // check if begin with "["
        if (s[0] == '[')
        {
        }
        else
        {
            // get the point
            // Point p;
            int attr;
            sscanf(s, "%d %d %d", &attr, &p_list[index].x, &p_list[index].y);
            index++;
        }
    }

    fclose(f);


    int width = 100;
    int height = 50;

    char** data = malloc(height * sizeof(char*));

    for (int i = 0; i < height; i++)
    {
        data[i] = malloc(width * sizeof(char));
        memset(data[i], 0, width);
    }

    // scale the points to width and height
    // int width, height, offset_x, offset_y;
    int max_x, max_y, min_x, min_y;

    for (int i = 0; i < index; i++)
    {
        if (i == 0)
        {
            max_x = min_x = p_list[i].x;
            max_y = min_y = p_list[i].y;
        }
        else
        {
            if (p_list[i].x > max_x)
            {
                max_x = p_list[i].x;
            }
            if (p_list[i].x < min_x)
            {
                min_x = p_list[i].x;
            }
            if (p_list[i].y > max_y)
            {
                max_y = p_list[i].y;
            }
            if (p_list[i].y < min_y)
            {
                min_y = p_list[i].y;
            }
        }
    }

    int pad = 2;

    float scale_x = (float) (width - 2*pad) / (max_x - min_x + 1);
    float scale_y = (float) (height - 2*pad) / (max_y - min_y + 1);
    int offset_x = -min_x + pad;
    int offset_y = -min_y + pad;

    for (int i = 0; i < index; i++)
    {
        p_list[i].x = (p_list[i].x + offset_x) * scale_x ;
        p_list[i].y = (p_list[i].y + offset_y) * scale_y ;
    }

    for (int i = 0; i < index; i++)
    {
        data[p_list[i].y][p_list[i].x] = 1;
    }

    draw_to_screen(data, height, width);

    // write to file
    FILE* f_out = fopen("output.txt", "w");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (data[i][j])
            {
                fprintf(f_out, "* ");
            }
            else
            {
                fprintf(f_out, " ");
            }
        }
        fprintf(f_out, "\n");
    }
}