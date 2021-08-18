#include<stdlib.h> 
#include<stdio.h> 
#include<unistd.h> 
#include<time.h> 
#include<ctype.h>
#include<sys/ioctl.h>

#define SIDE 10
#define BOX 15

#define CLEAR system("clear");
#define RAW system("stty raw");
#define NORAW system("stty -raw");
#define NOECHO system("stty -echo");
#define ECHO system("stty echo");
#define Up(x); printf("\033[%dA", x);
#define Down(x); printf("\033[%dB", x);
#define Right(x); printf("\033[%dC", x);
#define Left(x); printf("\033[%dD", x);

static struct winsize w;

static struct {
	int selected;
	int xpos, ypos;
} *cursor;

struct game_box {
	int **content;
	int name;
	int x, y;
	int layer;
};

static int *ptr;

// Help
void help(void);
void game_help(void);

// Init
int init_game(struct game_box **);
void init_menu(int);
void load(int **);

// Mem
struct game_box *new_gbox(int, int, int, int); //not freed

// Input
int handle_input(struct game_box **, int);

// GUI/TTY
void draw(struct game_box *);
void set_mouse(int, int);
int check(struct game_box **);
static void draw_h_line(int);
static void draw_v_line(int **, struct game_box *);

// Support
int search(struct game_box **, int);

int main() {
	struct game_box **gwin = malloc(sizeof(struct game_box *)*BOX);

	CLEAR
	if (!init_game(gwin))
		return 0;
	RAW
	NOECHO
	while(handle_input(gwin, cursor->selected))
		;
	NORAW
	ECHO
	CLEAR

	free(cursor);
	free(ptr);

	return 0;
}

int init_game(struct game_box **gwin) {
	int i, c=10;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	for (i=0; i<BOX; i++) {
		gwin[i] = new_gbox(i, c, 10, 2);
		load(gwin[i]->content);
		c+=SIDE+5;
	}

	if (check(gwin))
		return 0;

	cursor = malloc(sizeof(void *));
	cursor->selected = 0;
	cursor->xpos=0;
	cursor->ypos=0;

	ptr = malloc(sizeof(int)*3);
	ptr[0] = gwin[0]->content[0][0]; //content, useless
	ptr[1] = 0; // x
	ptr[2] = 0; // y
	for (i=0; i<BOX; i++)
		draw(gwin[i]);

	return 1;
}

struct game_box *new_gbox(int name, int new_x, int new_y, int new_layer) {
	struct game_box *new = malloc(sizeof(struct game_box));
	new->content = malloc(sizeof(int *)*SIDE);
	new->name = name;
	new->x = new_x;
	new->y = new_y;
	new->layer = new_layer;
	return new;
}

int handle_input(struct game_box **gwin, int current) {
	int c, tmp, i;
	struct game_box *win = gwin[current];

	set_mouse(win->x+1, win->y+1);
	ptr[0] = win->content[0][0];
	ptr[1] = 0;
	ptr[2] = 0;
	while((c=getchar()) != 'q')
		if (c == 'l') 
			if (ptr[1] == SIDE-1) {
				set_mouse(win->x+1, cursor->ypos);
				ptr[0] = win->content[0][ptr[2]];
				ptr[1] = 0;
			} else {
				set_mouse(cursor->xpos+1, cursor->ypos);
				ptr[0] = win->content[++ptr[1]][ptr[2]];
			}
		else if (c == 'h')
			if (ptr[1] == 0) {
				set_mouse(win->x+SIDE, cursor->ypos);
				ptr[0] = win->content[SIDE-1][ptr[2]];
				ptr[1] = SIDE-1;
			} else {
				set_mouse(cursor->xpos-1, cursor->ypos);
				ptr[0] = win->content[--ptr[1]][ptr[2]];
			}
		else if (c == 'j')
			if (ptr[2] == SIDE-1) {
				set_mouse(cursor->xpos, win->y+1);
				ptr[0] = win->content[ptr[1]][0];
				ptr[2] = 0;
			} else {
				set_mouse(cursor->xpos, cursor->ypos+1);
				ptr[0] = win->content[ptr[1]][++ptr[2]];
			}
		else if (c == 'k')
			if (ptr[2] == 0) {
				set_mouse(cursor->xpos, win->y+SIDE);
				ptr[0] = win->content[ptr[1]][SIDE-1];
				ptr[2] = SIDE-1;
			} else {
				set_mouse(cursor->xpos, cursor->ypos-1);
				ptr[0] = win->content[ptr[1]][--ptr[2]];
			}
		else if (c == 32) {
			if (win->content[ptr[2]][ptr[1]] < 48)
				(win->content[ptr[2]][ptr[1]])++;
			else
				win->content[ptr[2]][ptr[1]] = 40;
			CLEAR
			set_mouse(0, 0);
			for (i=0; i<BOX; i++)
				draw(gwin[i]);
			set_mouse(win->x+1+ptr[1], win->y+1+ptr[2]);
		} else if (isdigit(c)) {
				tmp = search(gwin, c-48);
				if (tmp != -1) {
					cursor->selected = tmp;
					return 1;
				}
		}
	return 0;
}

void load(int **c) {
	int i, j;
	srand(time(NULL));
	for (i=0; i<SIDE; i++) {
		*(c+i) = malloc(sizeof(int)*SIDE);
		for(j=0; j<SIDE; j++)
			*(*(c+i)+j) = rand()%10+40;
	}
}

int check(struct game_box **gwin) {
	if (gwin[BOX-1]->x+SIDE+2 > w.ws_col || gwin[BOX-1]->y+SIDE+2 > w.ws_row)
		return 1;
	return 0;
}

void draw(struct game_box *win) {
	set_mouse(win->x, win->y);
	draw_h_line(0);
	draw_v_line(win->content, win);
	set_mouse(win->x, cursor->ypos+1);
	draw_h_line(1);
}

void set_mouse(int x, int y) {
	if (y > cursor->ypos) {
		Down(y-cursor->ypos);
	} else if (y < cursor->ypos) {
		Up(cursor->ypos-y);
	}
	cursor->ypos = y;

	if (x > cursor->xpos) {
		Right(x-cursor->xpos);
	} else if (x < cursor->xpos) {
		Left(cursor->xpos-x);
	}
	cursor->xpos = x;
}

static void draw_h_line(int v) {
	int i=0;
	printf(v ? "\u2517" : "\u250F");
	while(i++<SIDE)
		printf("\u2501");
	printf(v ? "\u251B" : "\u2513");
	cursor->xpos+= SIDE+2;
}

static void draw_v_line(int **c, struct game_box *win) {
	int i, j;
	for (i=0; i<SIDE; i++) {
		set_mouse(win->x, cursor->ypos+1);
		printf("\u2503");
		for (j=0; j<SIDE; j++)
			printf("\033[%dm \033[0m", c[i][j]);
		printf("\u2503");
		cursor->xpos += SIDE+2;
	}
}

int search(struct game_box **gwin, int name) {
	int i;
	for(i=0; i<BOX; i++)
		if (gwin[i]->name == name)
			return i;
	return -1;
}
