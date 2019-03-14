#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>

const int N = 10;

void swap(char *a, char *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void swapi(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

struct pos
{
    int i;
    int j;
};

int checkGameOver(char M[][N], int i, int j)
{
    if (((M[i + 1][j] == '#' && M[i][j + 1] == '#') || (M[i - 1][j] == '#' && M[i][j - 1] == '#'))
    || ((M[i + 1][j] == '@' && M[i][j + 1] == '@')  || (M[i - 1][j] == '@' && M[i][j - 1] == '@')))
    return 1;
    else return 0;
}

void draw(char M[][N])
{
    clear();

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printw("%c ", M[i][j]);

        printw("\n");
    }
}

void init(char M[][N], struct pos *p_pos, int *k)
{
    FILE *f;
    char ch;

    *k = 0;

    f = fopen("level.txt", "rb");

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            ch = fgetc(f);

            if (ch != '\n') M[i][j] = ch;
            else j--;

            if (M[i][j] == '&')
            {
                p_pos->i = i;
                p_pos->j = j;
            }
            else if (M[i][j] == 'x') (*k)++;
        }

    fclose(f);
}

int main(void)
{
    initscr();
    raw();
    noecho();

    int di = 0, dj = 0;
    int k;
    int run = 1;

    struct pos p_pos;
    char M[N][N];
    char input;

    init(M, &p_pos, &k);

    while (run)
    {
        draw(M);

        input = getch();
        input = toupper(input);

        switch (input)
        {
            case 'W': di = -1; dj = 0; break;
            case 'A': di = 0; dj = -1; break;
            case 'S': di = 1; dj = 0;  break;
            case 'D': di = 0; dj = 1;  break;
            case 'R':

                init(M, &p_pos, &k);
                di = dj = 0;
                draw(M); break;

            case 'X': run = 0; break;
            default: di = dj = 0;
        }

        p_pos.i += di;
        p_pos.j += dj;

        if (M[p_pos.i][p_pos.j] == ' ' || M[p_pos.i][p_pos.j] == '@')
        {
            if (M[p_pos.i + di][p_pos.j + dj] == ' ')
            {
                swap(&M[p_pos.i + di][p_pos.j + dj], &M[p_pos.i][p_pos.j]);
                swap(&M[p_pos.i - di][p_pos.j - dj], &M[p_pos.i][p_pos.j]);

                if (checkGameOver(M, p_pos.i + di, p_pos.j + dj) && M[p_pos.i + di][p_pos.j + dj] == '@')
                {
                    draw(M);
                    printw("\nLOOSEER!\n");
                    run = 0;
                }
            }
            else if (M[p_pos.i + di][p_pos.j + dj] == 'x' && M[p_pos.i][p_pos.j] == '@')
            {
                M[p_pos.i + di][p_pos.j + dj] = '.';
                M[p_pos.i][p_pos.j] = '&';
                M[p_pos.i - di][p_pos.j - dj] = ' ';

                k--;
            }
            else if (M[p_pos.i][p_pos.j] != '@')
                swap(&M[p_pos.i - di][p_pos.j - dj], &M[p_pos.i][p_pos.j]);
            else
            {
                p_pos.i -= di;
                p_pos.j -= dj;
            }
        }
        else
        {
            p_pos.i -= di;
            p_pos.j -= dj;
        }

        if (k == 0)
        {
            draw(M);
            printw("\nVICTORY!\n");
            run = 0;
        }
    }

    getch();
    endwin();
    return 0;
}