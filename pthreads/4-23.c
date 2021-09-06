#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <omp.h>

#define GEN_MAX_MIN (1)
#define NUM_GEN (1000000)
#define RADIUS (1)
#define SQUARE_ENDS (4)
#define MONTE_CARLO(x, y) (float)(4)*x/(x+y)

int inner_points = 0;
int outer_points = 0;

struct point {
  float x;
  float y;
};

struct square {
  struct point ends[4];
  struct point center;
};

float generate_coord(void);
float calc_distance(struct point * /*first_point*/, struct point * /*second_point*/);
float calc_PI(void);
struct square *find_square(struct point * /*start*/);

void generate_rand_coord(struct point * /*start*/);

static void print_point(struct point * /*_point*/);
static void print_square(struct square * /*_square*/);

int main(void) {
  srand((unsigned)time(NULL));

  /* defining the first point */
  struct point start = { .x = -1, .y = 1 };
  struct square *outer_square = find_square(&start);

  /* Printing the square info */
  print_square(outer_square);

  printf("Inner points: %d\nOuter points: %d\nPI: %f\n", inner_points, outer_points, calc_PI());
}

float generate_coord(void) {
  float scale = rand() / (float)(RAND_MAX);
  return (-GEN_MAX_MIN) + scale * (GEN_MAX_MIN*2 - (-GEN_MAX_MIN));
}

struct square *find_square(struct point *start) {
  struct square *square_t = malloc(sizeof(struct square));

  //Setting the ends
  square_t->ends[0] = *start;
  square_t->ends[1] = (struct point){ .x = start->x + (RADIUS*2), .y = start->y              };
  square_t->ends[2] = (struct point){ .x = start->x,              .y = start->y - (RADIUS*2) };
  square_t->ends[3] = (struct point){ .x = start->x + (RADIUS*2), .y = start->y - (RADIUS*2) };

  //Finding the center of the square
  square_t->center =  (struct point){ .x = start->x + RADIUS,     .y = start->y - RADIUS     };

  return square_t;
}

float calc_distance(struct point *first_point, struct point *second_point) {
  float x = abs(first_point->x - second_point->x);
  float y = abs(first_point->y - second_point->y);

  return sqrt(pow(x, 2) + pow(y, 2));
}

void generate_rand_coord(struct point *start) {
  int times = rand() % NUM_GEN +1;
  
#pragma omp parallel for
  for (int i=0; i<times; i++) {
    if (calc_distance(start, &(struct point){ .x = generate_coord(), .y = generate_coord()}) > RADIUS)
      ++outer_points;
    else
      ++inner_points;
  }
}

float calc_PI(void) {
  return MONTE_CARLO(inner_points, outer_points);
}

static void print_point(struct point *_point) {
  printf("(X = %.3f, Y = %.3f)", _point->x, _point->y);
}

static void print_square(struct square *_square) {
  printf("square = [ Ends = [ ");
  for (int i=0; i<SQUARE_ENDS; i++) {
    print_point(_square->ends+i);

    if (i != SQUARE_ENDS-1)
      printf(", ");
  }

  printf(" ], Center = ");
  print_point(&_square->center);
  printf(" ]\n");
}
