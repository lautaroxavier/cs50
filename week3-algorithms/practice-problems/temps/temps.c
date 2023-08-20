// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

void * bubble_sort(void *vec, int ce, int size, int (*cmp)(const void *, const void *));

void swap_elements(void *, void *, int size);

int cmp_avg_temps(const void *, const void *);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

int cmp_avg_temps(const void *t1, const void *t2)
{
    const avg_temp *temp1 = t1;
    const avg_temp *temp2 = t2;
    return temp1->temp - temp2->temp;
}

void swap_elements(void *e1, void *e2, int size)
{
    char aux[size];
    memcpy(aux, e1, size);
    memcpy(e1, e2, size);
    memcpy(e2, aux, size);
}

void * bubble_sort(void *vec, int ce, int size, int (*cmp)(const void *, const void *))
{
    // mientras haya habido algun intercambio y haya mas de un elemento sin ordenar
        // iterar desde 0 hasta el anteultimo elemento sin ordenar
            // comparar el elemento actual con el siguiente
                // si el actual es mayor al siguiente intercambiarlos
    bool swaps;
    void *start = vec;
    void *fin = vec + (size * (ce - 1));
    do
    {
        for (vec = start, swaps = false; vec < fin; vec += size)
        {
            if (cmp(vec, (vec + size)) < 0)
            {
                swap_elements(vec, vec + size, size);
                swaps = true;
            }
        }
        ce--;
    }
    while (swaps && ce > 1);
    return start;
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    bubble_sort(temps, NUM_CITIES, sizeof(avg_temp), cmp_avg_temps);
}
