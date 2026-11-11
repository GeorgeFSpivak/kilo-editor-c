#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// stores the terminal's original settings.
struct termios orig_termios;

// restores the terminal's original settings.
void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// configures the terminal for raw mode and registers,
// the restore function to run on normal exit.
void enableRawMode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;

    raw.c_iflag = raw.c_iflag & ~(ICRNL | IXON);
    raw.c_lflag = raw.c_lflag & ~(ECHO | ICANON | IEXTEN | ISIG);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// displays input bytes and exits when 'q' is pressed.
int main(void) {
    enableRawMode();

    unsigned char c;

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ('%c')\n", c, c);
        }
    }

    return 0;
}
