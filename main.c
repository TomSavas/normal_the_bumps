#include <stdio.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        printf("No file provided.\n");
        return 1;
    }

    const char *out_file = "out_normal.jpg";
    if (argc > 2)
        out_file = argv[2];

    const float softness = 128.f;
    const float sqr_softness = softness * softness;

    int x, y, n;
    unsigned char *img = stbi_load(argv[1], &x, &y, &n, 1);

    unsigned char *normal_img = malloc(sizeof(unsigned char)*3 * x * y);
    for (int i = 0; i < y; i++)
    {
        int row_idx = i * x;
        int top_idx = min(max((i-1), 0), y) * x;
        int bot_idx = min(max((i+1), 0), y) * x;

        for (int j = 0; j < x; j++)
        {
            int left_idx = min(max((j-1), 0), x);
            int right_idx = min(max((j+1), 0), x);

            float top_left  = img[top_idx + left_idx];
            float top       = img[top_idx + j];
            float top_right = img[top_idx + right_idx];

            float left      = img[row_idx + left_idx];
            float right     = img[row_idx + right_idx];

            float bot_left  = img[bot_idx + left_idx];
            float bot       = img[bot_idx + j];
            float bot_right = img[bot_idx + right_idx];
 
            // sobel kernel
            float dX = -(top_left + 2*left + bot_left ) + (top_right + 2*right + bot_right);
            float dY = -(top_left + 2*top  + top_right) + (bot_left  + 2*bot   + bot_right);

            // normalize
            float len = sqrt(dX*dX + dY*dY + sqr_softness);
            float vec_x = dX / len;
            float vec_y = dY / len;
            float vec_z = softness / len;

            int index = (i*x + j);
            normal_img[index*3 + 0] = (vec_x+1) * 255.0/2.0;
            normal_img[index*3 + 1] = (vec_y+1) * 255.0/2.0;
            normal_img[index*3 + 2] = (vec_z+1) * 255.0/2.0;
        }
    }

    stbi_write_jpg(out_file, x, y, 3, normal_img, 100);

    stbi_image_free(img);
    free(normal_img);

    return 0;
}
