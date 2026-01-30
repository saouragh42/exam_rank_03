/* tsp.c */
#include <stdio.h>   /* fscanf, fprintf, stdin, stdout */
#include <stdlib.h>  /* malloc, free */
#include <math.h>    /* sqrtf, INFINITY */

/* distance entre les villes i et j (coords à plat dans cities) */
float distance(float *cities, int i, int j)
{
    float dx = cities[i * 2]     - cities[j * 2];
    float dy = cities[i * 2 + 1] - cities[j * 2 + 1];
    return sqrtf(dx * dx + dy * dy);
}

/* échanger deux indices */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ====== TA VERSION GARDEE ====== */
void find_min_path(float *cities, int *order,
                   int fix_pos, int last_pos, int city_count, float *min)
{
    int i = fix_pos;
    float sum;
    int idx = 0;

    if (fix_pos == last_pos)
    {
        sum = 0;
        while (idx < city_count - 1)
        {
            sum += distance(cities, order[idx], order[idx + 1]);
            idx++;
        }
        sum += distance(cities, order[city_count - 1], order[0]);
        if (sum < *min)
            *min = sum;
    }
    else
    {
        while (i <= last_pos)
        {
            swap(&order[fix_pos], &order[i]);
            find_min_path(cities, order, fix_pos + 1, last_pos, city_count, min);
            swap(&order[fix_pos], &order[i]);
            i++;
        }
    }
}


int main(void)
{
    /* max 11 villes -> 22 floats (x,y) et 11 indices */
    float *cities = (float *)malloc(sizeof(float) * 22);
    int   *order  = (int   *)malloc(sizeof(int)   * 11);
    int count = 0;
    float x, y;
    float min = INFINITY; /* sentinelle propre (nécessite -lm) */

    if (!cities || !order)
        return 1;

    /* lecture '%f, %f' depuis stdin (jusqu'à 11 villes) */
    while (count < 11 && fscanf(stdin, "%f, %f", &x, &y) == 2)
    {
        cities[count * 2]     = x;
        cities[count * 2 + 1] = y;
        order[count] = count;
        count++;
    }

    if (count == 0 || count == 1)
    {
        /* chemin fermé de 0 ou 1 point = 0 */
        fprintf(stdout, "%.2f\n", 0.0f);
    }
    else
    {
        /* fixe la 1re ville à 0 et permute 1..count-1 */
        find_min_path(cities, order, 1, count - 1, count, &min);
        fprintf(stdout, "%.2f\n", min);
    }

    free(cities);
    free(order);
    return 0;
}
