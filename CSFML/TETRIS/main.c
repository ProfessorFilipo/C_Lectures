#include <SFML/Graphics.h>
#include <time.h>
#include <stdbool.h>

#define M 20
#define N 10

int field[M][N] = {0};

struct Point
{
    int x, y;
}   a[4], b[4];

int figures[7][4] =
{
    {1, 3, 5, 7}, // I
    {2, 4, 5, 7}, // Z
    {3, 5, 4, 6}, // S
    {3, 5, 4, 7}, // T
    {2, 3, 5, 7}, // L
    {3, 5, 7, 6}, // J
    {2, 3, 4, 5}  // O
};

bool Verifica()
{
    int i=0;
    for(i=0; i<4; i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    }

    return 1;
}

int main()
{
    srand(time(0));

    sfVideoMode VideoMode = {320, 480, 32};
    sfRenderWindow *window;
    window = sfRenderWindow_create(VideoMode, "TETRIS!!!", sfClose, NULL);

    sfRenderTexture *fundo = sfTexture_createFromFile("background.png", NULL);
    sfSprite *spriteFundo = sfSprite_create();
    sfSprite_setTexture(spriteFundo, fundo, 0);

    sfRenderTexture *moldura = sfTexture_createFromFile("frame.png", NULL);
    sfRenderTexture *textura = sfTexture_createFromFile("tiles.png", NULL);
    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, textura,0);
    sfIntRect frame = {0, 0, 18, 18};
    sfSprite_setTextureRect(sprite, frame);

    int dx=0; bool rotate=0; int colorNum=1; int i=0; int j=0;
    sfTime timer, delay;
    timer.microseconds = 0;
    delay.microseconds = 500000;

    sfClock *relogio = sfClock_create();

    while (sfRenderWindow_isOpen(window))
    {
        sfTime tempo = sfClock_getElapsedTime(relogio);
        sfClock_restart(relogio);
        timer.microseconds += tempo.microseconds;

        sfEvent Evento;
        while(sfRenderWindow_pollEvent(window, &Evento))
        {
            if(Evento.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }

            if(Evento.type == sfEvtKeyPressed)
            {
                if(Evento.key.code == sfKeyUp) rotate = true;
                else if (Evento.key.code == sfKeyLeft)  dx = -1;
                else if (Evento.key.code == sfKeyRight) dx = 1;

                if(Evento.key.code == sfKeyDown)
                {
                    delay.microseconds = 50000;
                }
            }

        }

        // movimentação
        for(i =0; i<4; i++)
        {
            a[i].x += dx;
        }
        if(!Verifica())
        {
            for(i=0; i<4; i++)
            {
                a[i] = b[i];
            }
        }

        // rotação
        if(rotate)
        {
            struct Point p = a[1];
            for(i=0; i<4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if(!Verifica())
            {
                for(i=0; i<4; i++)
                {
                    a[i] = b[i];
                }
            }
        }

        /// tick!
        if (timer.microseconds > delay.microseconds)
        {
            for(i=0; i<4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if(!Verifica())
            {
                for(i=0; i<4; i++)
                {
                    field[b[i].y][b[i].x] = colorNum;
                }

                colorNum = 1 + rand()%7;
                int n = rand()%7;

                for(i=0; i<4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer.microseconds = 0;
        }

        /*int n=3;
        if( a[0].x == 0)
        for(i=0; i<4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }*/

        /// verifica linhas !
        int k = M-1;
        for(i=M-1; i>0; i--)
        {
            int cont=0;
            for(j=0; j<N; j++)
            {
                if (field[i][j])
                {
                    cont++;
                }
                field[k][j] = field[i][j];
            }
            if (cont < N) k--;
        }

        dx=0; rotate=0; delay.microseconds = 500000;

        // desenha!
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, spriteFundo, NULL);

        for(i=0; i<M; i++)
        {
            for(j=0; j<N; j++)
            {
                if(field[i][j]==0) continue;
                sfSprite_setTextureRect(sprite,(sfIntRect){field[i][j]*18,0,18,18});
                sfSprite_setPosition(sprite, (sfVector2f){j*18, i*18});
                sfRenderWindow_drawSprite(window, sprite, NULL);
            }
        }

        for(i=0; i<4; i++)
        {
            sfSprite_setTextureRect(sprite,(sfIntRect){colorNum*18, 0, 18, 18});
            sfSprite_setPosition(sprite, (sfVector2f){a[i].x*18, a[i].y*18});
            sfRenderWindow_drawSprite(window, sprite, NULL);
        }

        //sfRenderWindow_drawSprite(window, spriteFundo, NULL);

        sfRenderWindow_display(window);
    }
}
