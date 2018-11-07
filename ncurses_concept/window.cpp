#include <ncurses.h>
#include <iostream>
#include <form.h>
#include <menu.h>
#include <string.h>
#include <cassert>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
WINDOW *display_menu(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
static char* trim_whitespaces(char *str);
static void driver(int ch, bool*);
int kbhit();
void entry_point(void);
    
typedef struct user 
{
	std::string first;
	std::string last;
	std::string birthdate;
}User_struct;

static FORM *form;
static FIELD *fields[9];
static WINDOW * win_form;
int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    entry_point();
}
void entry_point()
{
    std::string logo[16];
    logo[0] =  "TTTTTTTTTTTTTTTTTTTTTTT   SSSSSSSSSSSSSSS NNNNNNNN        NNNNNNNN";
    logo[1] =  "T:::::::::::::::::::::T SS:::::::::::::::SN:::::::N       N::::::N";
    logo[2] =  "T:::::::::::::::::::::TS:::::SSSSSS::::::SN::::::::N      N::::::N";
    logo[3] =  "T:::::TT:::::::TT:::::TS:::::S     SSSSSSSN:::::::::N     N::::::N";
    logo[4] =  "TTTTTT  T:::::T  TTTTTTS:::::S            N::::::::::N    N::::::N";
    logo[5] =  "        T:::::T        S:::::S            N:::::::::::N   N::::::N";
    logo[6] =  "        T:::::T         S::::SSSS         N:::::::N::::N  N::::::N";
    logo[7] =  "        T:::::T          SS::::::SSSSS    N::::::N N::::N N::::::N";
    logo[8] =  "        T:::::T            SSS::::::::SS  N::::::N  N::::N:::::::N";
    logo[9] =  "        T:::::T               SSSSSS::::S N::::::N   N:::::::::::N";
    logo[10] = "        T:::::T                    S:::::SN::::::N    N::::::::::N";
    logo[11] = "        T:::::T                    S:::::SN::::::N     N:::::::::N";
    logo[12] = "      TT:::::::TT      SSSSSSS     S:::::SN::::::N      N::::::::N";
    logo[13] = "      T:::::::::T      S::::::SSSSSS:::::SN::::::N       N:::::::N";
    logo[14] = "      T:::::::::T      S:::::::::::::::SS N::::::N        N::::::N";
    logo[15] = "      TTTTTTTTTTT       SSSSSSSSSSSSSSS   NNNNNNNN         NNNNNNN";
    WINDOW * login = newwin(LINES, COLS,0,0);
    box(login, '|', '~');
	wborder(login, '|', '|', '~', '~', '+', '+', '+', '+');
    wrefresh(login);
    int j = 3;
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    wbkgd(stdscr,COLOR_PAIR(1));
    wbkgd(login, COLOR_PAIR(1));
    refresh();
    wrefresh(login);
    wattron(login,COLOR_PAIR(2));
    mvwprintw(login,3, COLS/2 - 35, "Made by: EDGAR, ADI, ATAFO, JOSEPH, TUFAN");
    wattroff(login,COLOR_PAIR(2));
    mvwprintw(login,LINES-2, 2, "PRESS ANY KEY TO CONTINUE");
    for(int i = 0; i < 16; i++)
    {
        mvwprintw(login,++j, COLS/2 - 35, logo[i].c_str());
        wrefresh(login);
    }
	int c = wgetch(login);
	if(c == 10)
	{
		wclear(login);
        static bool initialize_user = false; // get the value from the file
        std::string logo[6];
        logo[0] = " _____ ____  _    _ ";
        logo[1] = "|_   _/ ___|| \\ | |";
        logo[2] = "  | | \\___ \\|  \\| |";
        logo[3] = "  | |  ___) | |\\  |";
        logo[4] = "  |_| |____/|_| \\_|";
        //logo[5] = "";
        WINDOW *menu;
        menu = newwin(LINES, COLS, 0, 0);
        box(win_form,0,0);
        box(menu, 0 , 0);
        start_color();
        init_pair(1,COLOR_CYAN, COLOR_BLACK);
        wattron(menu, COLOR_PAIR(1));
        wborder(menu, '|', '|', '~', '~', '+', '+', '+', '+');
        int j = 0;
        for(int i = 0; i < 5; i++)
        {
            mvwprintw(menu ,++j, COLS / 2 - 10, logo[i].c_str());
            wrefresh(menu);
        }
        win_form = derwin(menu, LINES - 7 ,78, 6, COLS / 2 - 39);
        assert(win_form != NULL);
        box(win_form, 0, 0);
        wborder(win_form, '|', '|', '=', '=', '+', '+', '+', '+');
        
        fields[0] = new_field(1, 10, 0, 0, 0, 0);
        fields[1] = new_field(1, 30, 0, 15, 0, 0);
        fields[2] = new_field(1, 10, 2, 0, 0, 0);
        fields[3] = new_field(1, 30, 2, 15, 0, 0);
        fields[4] = new_field(1, 10, 4, 0, 0, 0);
        fields[5] = new_field(1, 30, 4, 15, 0, 0);
        fields[6] = new_field(1, 10, 6, 0, 0, 0);
        fields[7] = new_field(1, 30, 6, 15, 0, 0);
        fields[8] = NULL;
        assert(fields[0] != NULL && fields[1] != NULL && fields[2] != NULL && fields[3] != NULL);

        set_field_buffer(fields[0], 0, "First Name");
        set_field_buffer(fields[1], 0, "Name");
        set_field_buffer(fields[2], 0, "Last Name");
        set_field_buffer(fields[3], 0, "Name");
        set_field_buffer(fields[4], 0, "Interest");
        set_field_buffer(fields[5], 0, "e.g Boxing");
        set_field_buffer(fields[6], 0, "Birthdate");
        set_field_buffer(fields[7], 0, "MM/DD/YYY");


        set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
        set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
        set_field_opts(fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
        set_field_opts(fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
        set_field_opts(fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
        set_field_opts(fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
        set_field_opts(fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
        set_field_opts(fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);



        set_field_back(fields[1], A_UNDERLINE);
        set_field_back(fields[3], A_UNDERLINE);
        set_field_back(fields[5], A_UNDERLINE);
        set_field_back(fields[7], A_UNDERLINE);


        form = new_form(fields);
        assert(form != NULL);
        set_form_win(form, win_form);
        set_form_sub(form, derwin(win_form, 15, 60, 2, 15));
        post_form(form);
        mvwprintw(win_form, 10,15, "Press Enter to submit");
        refresh();
        wrefresh(menu);
        wrefresh(win_form);
        int ch;
        bool is_running = true;
        while ((ch = getch()) != KEY_F(1) && is_running)
            driver(ch, &is_running);
        
        unpost_form(form);
        free_form(form);
        free_field(fields[0]);
        free_field(fields[1]);
        free_field(fields[2]);
        free_field(fields[3]);
        free_field(fields[4]);
        free_field(fields[5]);
        free_field(fields[6]);
        free_field(fields[7]);
        free_field(fields[8]);
        werase(win_form);
        delwin(win_form);
        werase(menu);
        delwin(menu);
        wrefresh(win_form);
    }
    std::string choices[] = {"List Users", "Show User", "Edit", "Resync", "Post", "Show Statistics", "Exit"};
    int choice;
    int highlight = 0;
    WINDOW * menu_screen_lhs;
    WINDOW * menu_screen_rhs;
    menu_screen_lhs = newwin(LINES - 8,COLS / 2 - 20, 7,15);
    menu_screen_rhs = newwin(LINES - 8,COLS / 2 - 20, 7,COLS / 2 + 1);
    keypad(menu_screen_lhs, TRUE);
    box(menu_screen_lhs, 0, 0);
    box(menu_screen_rhs, 0, 0);
    wattron(menu_screen_lhs, COLOR_PAIR(1));
    wattron(menu_screen_rhs, COLOR_PAIR(1));
    wborder(menu_screen_lhs, '|', '|', '=', '=', '+', '+', '+', '+');
    wborder(menu_screen_rhs, '|', '|', '=', '=', '+', '+', '+', '+');
    while(1)
    {
        wrefresh(menu_screen_rhs);
        wrefresh(menu_screen_lhs);
        int y,x;
        getmaxyx(menu_screen_lhs,y,x);
        for(size_t i = 0; i < 7; i++)
        {
            if(i == highlight)
                wattron(menu_screen_lhs,A_REVERSE);

            mvwprintw(menu_screen_lhs,i+1,x/2 - 7, choices[i].c_str());
            wattroff(menu_screen_lhs, A_REVERSE);
        }
        choice = wgetch(menu_screen_lhs);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 8)
                    highlight = 7;
                break;
            default:
                break;
        }
        if(highlight == 6 && choice == 10) break;
    }
    wrefresh(menu_screen_lhs);
    wrefresh(menu_screen_rhs);
    refresh();
    getchar();
    endwin();


}
int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
void destroy_win(WINDOW *local_win)
{   
        /* box(local_win, ' ', ' '); : This won't produce the desired
         *   * result of erasing the window. It will leave it's four corners 
         *       * and so an ugly remnant of window. 
         *           */
        wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
            /* The parameters taken are 
             *   * 1. win: the window on which to operate
             *       * 2. ls: character to be used for the left side of the window 
             *           * 3. rs: character to be used for the right side of the window 
             *               * 4. ts: character to be used for the top side of the window 
             *                   * 5. bs: character to be used for the bottom side of the window 
             *                       * 6. tl: character to be used for the top left corner of the window 
             *                           * 7. tr: character to be used for the top right corner of the window 
             *                               * 8. bl: character to be used for the bottom left corner of the window 
             *                                   * 9. br: character to be used for the bottom right corner of the window
             *                                       */
            wrefresh(local_win);
                delwin(local_win);
}
static char* trim_whitespaces(char *str)
{
    char *end;

    // trim leading space
    while(isspace(*str))
        str++;

    if(*str == 0) // all spaces?
        return str;

    // trim trailing space
    end = str + strnlen(str, 128) - 1;

    while(end > str && isspace(*end))
        end--;

    // write new null terminator
    *(end+1) = '\0';

    return str;
}

static void driver(int ch, bool * is_running)
{
    int i;

    switch (ch) {
        case 10: // This is supposed to be the enter key but the ncurses macro isnt working for some reason,
            // Or the current field buffer won't be sync with what is displayed
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_PREV_FIELD);
            move(LINES-3, 2);
            /* This is the code to retrieve the values
            for (i = 0; fields[i]; i++) {
                printw("%s", trim_whitespaces(field_buffer(fields[i], 0)));
            }
            */
            *(is_running) = false;
            refresh();
            pos_form_cursor(form);
            break;

        case KEY_DOWN:
            form_driver(form, REQ_NEXT_FIELD);
            form_driver(form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(form, REQ_PREV_FIELD);
            form_driver(form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(form, REQ_NEXT_CHAR);
            break;

            // Delete the char before cursor
        case KEY_BACKSPACE:
        case 127:
            form_driver(form, REQ_DEL_PREV);
            break;

            // Delete the char under the cursor
        case KEY_DC:
            form_driver(form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(form, ch);
            break;
    }

    wrefresh(win_form);
}
