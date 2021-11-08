/*
** testes com o wrapper CSFML
** Prof. Filipo Mor - filipomor.com
** Novembro de 2021
*/
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Window.h>
#include <SFML/System/Clock.h>

sfIntRect PosicaoFrame(int AlturaSpriteSheet, int LarguraSpriteSheet, int qtFrames, int qtFramesPorLinha, int idxFrame)
{
    /*
    ** Retorna a posicao do frame desejado a partir das dimensoes informadas
    ** do sprite sheet e a quantidade de frames existentes, considerando
    ** a possibilidade de existirem varias linhas contendo frames.
    ** O indice (idx) considera os frames da esquerda para direita e
    ** de cima para baixo.
    */

    int Linha = idxFrame  / qtFramesPorLinha;
    int Coluna = idxFrame % qtFramesPorLinha;

    sfIntRect retorno;
    retorno.height = AlturaSpriteSheet  / ( qtFrames / qtFramesPorLinha );
    retorno.width  = LarguraSpriteSheet / qtFramesPorLinha;
    retorno.left   = retorno.width  * Coluna;
    retorno.top    = retorno.height * Linha;


    //printf("\nLinha: %d :: Coluna: %d \n", Linha, Coluna);

    return retorno;

}

int main()
{
    sfRenderWindow *janela;
    sfVideoMode modo = {800, 600, 32};
    janela = sfRenderWindow_create( modo, "titulo de teste", sfResize | sfClose, NULL);

    sfTexture *textura = sfTexture_createFromFile("imagens/megaman_transparente.png", NULL); // H=366 W=860 5 frames por linha, duas linhas
    sfSprite *desenho = sfSprite_create();
    sfIntRect spriteFrame = {0, 0, 172, 183};
    //Hframe = 183
    //Wframe = 172

    sfSprite_setTexture(desenho, textura, 0);
    //sfSprite_setTextureRect(desenho,spriteFrame);
    //sfVector2f fator = {0.05, 0.05};
    sfVector2f fator;
    fator.x = 1.0f;
    fator.y = 1.0f;
    sfSprite_scale(desenho, fator);
    //sfSprite_scale(desenho, (sfVector2f){0.05, 0.05});

    sfClock *relogio = sfClock_create();


    float posX = 0.0f, posY = 0.0f;
    int framePosX=0, framePosY=0;
    int frameIdx=0;

    while(sfRenderWindow_isOpen(janela))
    {
        sfEvent evento;
        while(sfRenderWindow_pollEvent(janela, &evento))
        {
            if(evento.type == sfEvtClosed)
            {
                sfRenderWindow_close(janela);
            }
        }


        sfTime tempo = sfClock_getElapsedTime(relogio);
        if(tempo.microseconds >=150000)
        {
            frameIdx++;
            if(frameIdx >= 10) frameIdx=0;
            sfClock_restart(relogio);
        }

        sfRenderWindow_clear(janela, sfBlack);

        // teclado
        if(sfKeyboard_isKeyPressed(sfKeyRight))
        {
            posX+=0.1;
        }
        if(sfKeyboard_isKeyPressed(sfKeyLeft))
        {
            posX-=0.1;
        }
        if(sfKeyboard_isKeyPressed(sfKeyUp))
        {
            posY-=0.1;
        }
        if(sfKeyboard_isKeyPressed(sfKeyDown))
        {
            posY+=0.1;
        }

        sfSprite_setPosition(desenho, (sfVector2f){posX, posY});
        sfIntRect retorno = PosicaoFrame(366, 860, 10, 5, frameIdx);

        sfSprite_setTextureRect(desenho,retorno/*spriteFrame*/);

        sfRenderWindow_drawSprite(janela, desenho,NULL);
        sfRenderWindow_display(janela);
    }


    //printf("\nH: %d ::: W: %d\nT: %d ::: L: %d\n", retorno.height, retorno.width, retorno.top, retorno.left);


    sfTexture_destroy(textura);
    sfSprite_destroy(desenho);
    sfRenderWindow_destroy(janela);

    return 0;
}
