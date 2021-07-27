#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 6
#define COLUMNS 6
#define NA -1

enum CITIES { A, B, C, D, E, F };

/* Creting the grid with the necessary information */
static int mat[ROWS][COLUMNS] = {
   {  0, 50, NA, NA, NA, 70 },
   { 50,  0, 40, NA, 50, NA },
   { NA, 40,  0, 20, 20, NA },
   { NA, NA, 20,  0, NA, NA },
   { NA, 20, 50, NA,  0, 50 },
   { 70, NA, NA, NA, 50,  0 }
};

void print_mat(void);
char *print_path(int [], size_t);
int are_connected(int /*first_loc*/, int /*sec_loc*/);
int are_interconnected(int[], int, int, int);
static void shift(int[], size_t);
static void reset(int[], size_t);

int main(void) {
   int path[COLUMNS] = { -1, -1, -1, -1, -1, -1 };

   (void) print_mat();
   printf("Is there a direct way?    A -> B: %s\n", are_connected(A, B) ? "yes" : "no");
   printf("Is there a direct way?    E -> C: %s\n", are_connected(E, C) ? "yes" : "no");
   printf("Is there a direct way?    F -> E: %s\n", are_connected(F, E) ? "yes" : "no");
   printf("Is there a direct way?    F -> D: %s\n", are_connected(F, D) ? "yes" : "no");

   printf("Is there an indirect way? (E -> E): ");
   if (are_interconnected(path, E, E, A))
      printf("%s", print_path(path, COLUMNS));
   else
      printf("No");

   reset(path, COLUMNS);
  
   printf("Is there an indirect way? (D -> A): ");
   if (are_interconnected(path, D, D, A))
      printf("%s", print_path(path, COLUMNS));
   else
      printf("No");

   reset(path, COLUMNS);

   printf("Is there an indirect way? F -> D: ");
   if (are_interconnected(path, F, F, D))
      printf("%s", print_path(path, COLUMNS));
   else
      printf("No")

   reset(path, COLUMNS);

   return 0;
}

void print_mat(void) {
  printf("CONNECTIONS:\n");
  for (size_t i=0; i<ROWS; i++) {
    for (size_t j=0; j<COLUMNS; j++)
      printf("\t> From location %2ld to location %2ld: %3d Km\n", i, j, mat[i][j]);

    if (i != ROWS-1)
      printf("\n");
  }
}

int are_connected(int first_loc, int sec_loc) {
   /* Checking if the given locations are available */
   if (first_loc != NA && sec_loc != NA)
      return mat[first_loc][sec_loc]+1;

   /* Not connected */
   return 0;
}

int are_interconnected(int path[], int start_location, int first_location, int second_location) {
   int first_locations_connections[COLUMNS];

   if (first_location == second_location) {
      path[0] = first_location;
      return 1;
   }

   //getting nodes
   for (int i=0; i<COLUMNS; i++)
      first_locations_connections[i] = mat[first_location][i] > 0 ? i : -1;
 
   //going deeper
   for (size_t i=0; i<COLUMNS; i++)
      if (first_locations_connections[i] != -1 && start_location != first_locations_connections[i])
         if (are_interconnected(path, first_location, first_locations_connections[i], second_location)) {
            shift(path, COLUMNS);
            path[0] = first_location;
            return 1;
         }

   return 0;
}

static void shift(int vet[], size_t size) {
   for (size_t i=size-1; i>0; i--)
      vet[i] = vet[i-1];
   vet[0] = 0;
}

static void reset(int vet[], size_t size) {
  for (size_t i=0; i<size; i++)
    vet[i] = -1;
}

char *print_path(int path[], size_t size) {
  char *tmp = malloc(sizeof(char)*23);

  strcpy(tmp, "{ ");
  for (size_t i=0; i<size; i++)
    switch(path[i]) {
      case A:
        strcat(tmp, "A ");
        break;
      case B:
        strcat(tmp, "B ");
        break;
      case C:
        strcat(tmp, "C ");
        break;
      case D:
        strcat(tmp, "D ");
        break;
      case E:
        strcat(tmp, "E ");
        break;
      case F:
        strcat(tmp, "F ");
        break;
      default:
        break;
    }

  strcat(tmp, "}\n\0");
  return realloc(tmp, strlen(tmp));
}
