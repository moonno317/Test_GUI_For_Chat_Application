#include <ncurses.h>

void chatFunction() {
    initscr();
    cbreak();
    noecho();

    int maxRow, maxCol;
    getmaxyx(stdscr, maxRow, maxCol);
    int chatBoxHeight = maxRow - 7;
    int chatBoxWidth = maxCol - 6;

    WINDOW *chatBox = newwin(chatBoxHeight, chatBoxWidth, 4, 2);
    box(chatBox, 0, 0);

    int inputBoxHeight = 3;
    int inputBoxWidth = chatBoxWidth - 2;

    WINDOW *inputBox = newwin(inputBoxHeight, inputBoxWidth, maxRow - inputBoxHeight - 2, 2);
    box(inputBox, 0, 0);
    keypad(inputBox, true);
    wrefresh(chatBox);
    wrefresh(inputBox);

    int ch;
    char message[100];
    int messageLength = 0;

    while ((ch = wgetch(inputBox)) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (messageLength > 0) {
                messageLength--;
                message[messageLength] = '\0';
                mvwdelch(inputBox, 1, messageLength + 1); } } else {
            if (messageLength < inputBoxWidth - 3) {
                message[messageLength] = ch;
                messageLength++;
                message[messageLength] = '\0';
                mvwaddch(inputBox, 1, 2 + messageLength, ch); } } }

    mvwprintw(chatBox, chatBoxHeight / 2, 1, "world");
    wrefresh(chatBox);

    getch();
    endwin(); }

int main() {
    chatFunction();
    return 0; }
