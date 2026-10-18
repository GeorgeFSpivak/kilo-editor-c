#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

// stores the terminal's original settings.
struct termios orig_termios;

// restores the terminal's original settings.
void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// turns off terminal echo and registers
// the restore function to run on normal exit.
void enableRawMode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag = raw.c_lflag & ~ECHO;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// reads terminal input and exits after 'q' is submitted with Enter.
int main(void) {
    enableRawMode();

    char c;

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    }

    return 0;
}
