#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 6
#define COLUMNS 6
#define NOT_CONNECTED -1

enum CITIES { A, B, C, D, E, F };

//  ###  A  B  C  D  E  F
//   A   0 50 -1 -1 -1 70
//   B  50  0 40 -1 50 -1
//   C  -1 40  0 20 20 -1
//   D  -1 -1 20  0 -1 -1
//   E  -1 20 50 -1  0 50
//   F  70 -1 -1 -1 50  0

void print_mat(int[][COLUMNS]);
char *print_path(int [], size_t);
int are_connected(int[][COLUMNS], int, int);
int are_interconnected(int[][COLUMNS], int[], int, int, int);
static void shift(int[], size_t);
static void reset(int[], size_t);

int main() {
    int mat[ROWS][COLUMNS] = { 0 }, path[COLUMNS] = { -1, -1, -1, -1, -1, -1 };

    mat[A][A] = 0;
  mat[A][B] = 50;
  mat[A][C] = NOT_CONNECTED;
  mat[A][D] = NOT_CONNECTED;
  mat[A][E] = NOT_CONNECTED;

  mat[B][A] = 50;
  mat[B][B] = 0;
  mat[B][C] = 40;
  mat[B][D] = NOT_CONNECTED;
  mat[B][E] = 20;

  mat[C][A] = NOT_CONNECTED;
  mat[C][B] = 40;
	mat[C][C] = 0;
	mat[C][D] = 20;
  mat[C][E] = 50;

	mat[D][A] = NOT_CONNECTED;
	mat[D][B] = NOT_CONNECTED;
	mat[D][C] = 20;
	mat[D][D] = 0; 
  mat[D][E] = NOT_CONNECTED;
  
  mat[E][A] = NOT_CONNECTED;
  mat[E][B] = 20;
  mat[E][C] = 50;
  mat[E][D] = NOT_CONNECTED;
  mat[E][E] = NOT_CONNECTED;

  mat[F][A] = 70;
  mat[F][B] = NOT_CONNECTED;
  mat[F][C] = NOT_CONNECTED;
  mat[F][D] = NOT_CONNECTED;  
  mat[F][E] = 50;
  mat[F][F] = 0;

  print_mat(mat);
  printf("Is there a direct way?    A -> B: %d\n", are_connected(mat, A, B) ? 1 : 0);
  printf("Is there a direct way?    A -> D: %d\n", are_connected(mat, A, D) ? 1 : 0);
  printf("Is there a direct way?    A -> E: %d\n", are_connected(mat, A, E) ? 1 : 0);
  printf("Is there a direct way?    E -> C: %d\n", are_connected(mat, E, C) ? 1 : 0);
  printf("Is there a direct way?    F -> E: %d\n", are_connected(mat, F, E) ? 1 : 0);
  printf("Is there a direct way?    F -> D: %d\n", are_connected(mat, F, D) ? 1 : 0);

  printf("Is there an indirect way? E -> E: %d\n", are_interconnected(mat, path, E, E, A));
  printf("Path: \n=> ");
  printf("%s", print_path(path, COLUMNS));

  reset(path, COLUMNS);
  
  printf("Is there an indirect way? D -> A: %d\n", are_interconnected(mat, path, D, D, A));
  printf("Path: \n=> ");
  printf("%s", print_path(path, COLUMNS));

  reset(path, COLUMNS);

  printf("Is there an indirect way? F -> D: %d\n", are_interconnected(mat, path, F, F, D));
  printf("Path: \n=> ");
  printf("%s", print_path(path, COLUMNS));

  reset(path, COLUMNS);

  printf("Is there an indirect way? F -> C: %d\n", are_interconnected(mat, path, F, F, C));
  printf("Path: \n=>");
  printf("%s", print_path(path, COLUMNS));
}

void print_mat(int mat[][COLUMNS]) {
  printf("CONNECTIONS:\n");
  for (size_t i=0; i<ROWS; i++) {
    for (size_t j=0; j<COLUMNS; j++)
      printf("\t> From location %2ld to location %2ld: %3d Km\n", i, j, mat[i][j]);

    if (i != ROWS-1)
      printf("\n");
  }
}

int are_connected(int mat[][COLUMNS], int first_location, int second_location) {
  return first_location != -1 && second_location != -1 ? mat[first_location][second_location]+1 : 0;
}

int are_interconnected(int mat[][COLUMNS], int path[], int start_location, int first_location, int second_location) {
  int first_locations_connections[COLUMNS];

  if (first_location == second_location) {
    path[0] = first_location;
    return 1;
  }

  //getting nodes
  for (int i=0; i<COLUMNS; i++)
    first_locations_connections[i] = mat[first_location][i] > 0 ? i : -1;
 
  //getting deeper
  for (size_t i=0; i<COLUMNS; i++)
    if (first_locations_connections[i] != -1 && start_location != first_locations_connections[i])
      if (are_interconnected(mat, path, first_location, first_locations_connections[i], second_location)) {
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
