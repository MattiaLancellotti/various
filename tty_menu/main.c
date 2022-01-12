#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define __move_up_by(x) printf("\033[%dA", x);
#define __move_down_by(x) printf("\033[%dB", x);

/*
 * Saving the original state of the terminal to make it easy to safely disable
 * and exit raw mode.
 */
static struct termios terminal_origin;

int enable_rawmode(void)
{
   /* `termios.h`, a header that controls terminal's properties */
   struct termios new_term_config = terminal_origin;
   new_term_config.c_lflag &= ~(ECHO | ICANON);

   /* Updating the terminal's config */
   if (tcsetattr(0, TCSANOW, &new_term_config) == -1) {
      fprintf(stderr, "Couldn't enable raw mode.\n");
      return -1;
   }

   return 0;
}

void disable_rawmode(void)
{
   /* Resetting terminal's properties */
   if (tcsetattr(0, TCSANOW, &terminal_origin) == -1)
      fprintf(stderr, "Couldn't disable raw mode.\n");
}

int main(int argc, char **argv)
{
   int arg_count, out, pos = 0;

   /* This program needs arguments to be able to work */
   if (argc == 1) {
      fprintf(stdout, "Help message.\n");
      return EXIT_SUCCESS;
   }

   arg_count = argc-2;
   if (tcgetattr(0, &terminal_origin) == -1)  {
      fprintf(stderr, "Couldn't retrieve terminal attributes.\n");
      return EXIT_FAILURE;
   }

   atexit(disable_rawmode);
   enable_rawmode();

   /* Printing the list */
   for (size_t i = 1; i < argc; i++)
      printf("%s\n", argv[i]);

   __move_up_by(argc-1);
   while ((out = getchar()) != EOF && out != '\n' && out != 'q') {
      if (out == 'j') {
         if (pos == arg_count) {
            __move_up_by(arg_count);
            pos = 0;
         } else {
            __move_down_by(1);
            pos++;
         }
      } else if (out == 'k') {
         if (pos == 0) {
            __move_down_by(arg_count);
            pos = arg_count;
         } else {
            __move_up_by(1);
            pos--;
         }
      }
   }

   disable_rawmode();

   return 0;
}
