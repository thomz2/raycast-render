// TODO: implementar destrutores nas classes

#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include "classes/headers/math/Vec3.h"
#include "classes/headers/primitives/Esfera.h"
#include "classes/headers/primitives/Cilindro.h"
#include "classes/headers/primitives/Cone.h"
#include "classes/headers/Canvas.h"
#include "classes/headers/Ray.h"
#include "classes/headers/Scene.h"
#include "classes/headers/materiais/BaseMaterial.h"
#include "classes/headers/materiais/MaterialTarefa.h"
#include "classes/headers/math/Transformations.h"
#include "classes/headers/math/Mat4.h"
#include "classes/headers/math/Vec4.h"
#include "classes/headers/Camera.h"
#include "classes/headers/primitives/Triangulo.h"
#include "classes/headers/primitives/Mesh.h"
#include "classes/headers/primitives/ObjMesh.h"
#include "classes/headers/primitives/mesh/Texture.h"
#include "classes/headers/luzes/LuzPontual.h"
#include "classes/headers/luzes/LuzSpot.h"
#include "classes/headers/luzes/LuzDirecional.h"

using namespace std;

const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

void renderizarCenario(Scene* cenario, double dJanela, Vec3 olhoPintor) {
    cenario->pintarCanvas2(dJanela, olhoPintor);
}

void colorirCenario(SDL_Renderer* renderer, Scene* cenario, int nLin, int nCol) {
    for (int l = 0; l < nLin; ++l) {
        for (int c = 0; c < nCol; ++c) {
            SDL_Color cor = cenario->canvas->cores[l][c];

            SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, cor.a);
            SDL_RenderDrawPoint(renderer, c, l); // x = coluna que ta e y = linha que ta
        }
    }
}

int main ( int argc, char *argv[] ) {

    SDL_Window *window; // = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wJanela, hJanela, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer;


    // initializeSDLAndWindow(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    const double dJanela = 30;
    const double rEsfera = 40;
    const double zCentroEsfera = - (dJanela + rEsfera) - 50; // sempre diminuindo um valor

    Vec3 lookat(0, 0, -dJanela);
    // Vec3 lookfrom(-30, 60, 90);
    Vec3 lookfrom(0, 0, 50);

    Camera *camera = new Camera(lookfrom, lookat, Vec3(0, 1, 0), 90, WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene *cenario = new Scene(&window, &renderer, WINDOW_WIDTH, WINDOW_HEIGHT, Vec3(0.8, 0.8, 0.8), camera);
    const double wJanela = camera->wJanela, hJanela = camera->hJanela;
    camera->cenario = cenario;
    // camera->changeCamera();

    SDL_Color corVermelha = {255, 0, 0, 255};
    SDL_Color corVerde = {0, 255, 0, 255};
    SDL_Color corAzul = {0, 0, 255, 255};

    Texture* textura = new Texture("assets/snow.png", true);
    Plano* chao = new Plano(5, corAzul, BaseMaterial(Vec3(0.2, 0.7, 0.2), Vec3(0, 0, 0), Vec3(0.2, 0.7, 0.2), 1), Vec3(0, -20, 0), Vec3(0, 1, 0), textura);
    Plano* planoDeFundo = new Plano(6, corAzul, BaseMaterial(Vec3(0, 1, 1), Vec3(0, 0, 0), Vec3(0, 1, 1), 1), Vec3(0, 0, -700), Vec3(0, 0, 1));


    BaseMaterial materialMesh = BaseMaterial();
    materialMesh.REFLETIVIDADE = Vec3(0.2, 0.2, 0.2);
    // ObjMesh1* mesh2 = new ObjMesh(3, "assets/Yoshi2/Yoshi.obj", "assets/Yoshi/yoshi_all.png", materialMesh);
    // ObjMesh* mesh2 = new ObjMesh(2, "assets/porygon/porygon.obj", "assets/porygon/porygon_body.png", materialMesh);
    // ObjMesh* mesh3 = new ObjMesh(3, "assets/mine_cube/cube.obj", "assets/uv_test.png", materialMesh);
    // mesh3->applyMatrix(Transformations::scale(25, 25, 25));
    // mesh3->applyMatrix(Transformations::translate(0, 0, -50));

    ObjMesh* stan = new ObjMesh(6, "assets/stan/stan.obj", "assets/stan/stan_all.png", materialMesh);
    // stan->applyMatrix(Transformations::translate(-35, -20, -18));
    stan->applyMatrix(Transformations::translate(0, -5, -18));


    ObjMesh* cartman = new ObjMesh(7, "assets/cartman/cartman2.obj", "assets/cartman/cartman_all.png", materialMesh);
    cartman->applyMatrix(Transformations::translate(35, -20, -18));

    Cone* montanha1 = new Cone(8, corAzul, Vec3(-500, -20, -900), Vec3(0, 1, 0), 1500, 800, BaseMaterial(Vec3(0, 153.0/255.0, 51.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));
    Cone* montanha2 = new Cone(9, corAzul, Vec3(500, -20, -850), Vec3(0, 1, 0), 1500, 800, BaseMaterial(Vec3(0, 153.0/255.0, 51.0/255.0), Vec3(0, 0, 0), Vec3(0, 153.0/255.0, 51.0/255.0), 1));


    // megaman->applyMatrix();

    // mesh2->textura->testColors();

    LuzPontual* luzPontual = new LuzPontual(Vec3(-250, 125, 0), Vec3(0.2, 0.2, 0.2));
    LuzSpot* luzSpot = new LuzSpot(Vec3(-15, 50, -18), Vec3(0.3, 0.3, 0.3), Vec3(0, -1, 0).norm(), 60);
    LuzDirecional* luzDirecional = new LuzDirecional(Vec3(0.5, 0.5, 0.5), Vec3(-1, -1, 0).norm());

    // Esfera* esferaTeste = new Esfera(100, corAzul, Vec3(30, 30, -30), 15, BaseMaterial(Vec3(0.8, 0.2, 0.2), Vec3(0.2, 0.2, 0.8), Vec3(0.2, 0.8, 0.2), 10));
    ObjMesh* cubo = new ObjMesh(8, "assets/cube/cube.obj", BaseMaterial(Vec3(1, 0.078, 0.576), Vec3(1, 0.078, 0.576), Vec3(1, 0.078, 0.576), 1));
    cubo->applyMatrix(Transformations::scale(5, 5, 5));

    // cenario->objetos.push_back(megaman);
    // cenario->objetos.push_back(roll);
    cenario->objetos.push_back(stan);
    // cenario->objetos.push_back(cartman);
    cenario->objetos.push_back(chao);
    cenario->objetos.push_back(planoDeFundo);
    cenario->objetos.push_back(montanha1);
    cenario->objetos.push_back(montanha2);
         
    cenario->luzes.push_back(luzDirecional);
    // cenario->luzes.push_back(luzPontual);
    // cenario->luzes.push_back(luzSpot);

    const int nCol = 500;
    const int nLin = 500;
    const double Dx = (double)wJanela / (double)nCol;
    const double Dy = (double)hJanela / (double)nLin;
    cenario->setCanvas(nLin, nCol, Dx, Dy);

    bool rodando = true;
    double i = 0;
    double res = 10;
    while (rodando) {
        SDL_Event windowEvent;
        while ( SDL_PollEvent(&windowEvent) ) {
            if (SDL_QUIT == windowEvent.type) { 
                rodando = false;
                break; 
            }
            else if (windowEvent.type == SDL_KEYDOWN) {
                // Lógica para teclas pressionadas
                switch (windowEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        rodando = false;
                        break;
                    case SDLK_w:
                        // Lógica para mover a câmera para cima
                        camera->moveForward(5);
                        break;
                    case SDLK_s:
                        // Lógica para mover a câmera para baixo
                        camera->moveBackward(5);
                        break;
                    case SDLK_a:
                        // Lógica para mover a câmera para a esquerda
                        camera->moveLeft(5);
                        break;
                    case SDLK_d:
                        // Lógica para mover a câmera para a direita
                        camera->moveRight(5);
                        break;
                    case SDLK_LSHIFT:
                        camera->moveDown(5);
                        break;
                    case SDLK_RSHIFT:
                        camera->moveDown(5);
                        break;
                    case SDLK_SPACE:
                        camera->moveUp(5);
                        break;
                    case SDLK_1:
                        res = 1;
                        break;
                    case SDLK_2:
                        res = 2;
                        break;
                    case SDLK_5:
                        res = 5;
                        break;
                    case SDLK_9:
                        res = 10;
                        break;
                }
            }
        }

        camera->update();
        camera->renderAndPaintCanvasThread(4, res);
        colorirCenario(renderer, cenario, nLin, nCol);
        
        SDL_RenderPresent(renderer); // usar para pintar
        if ( window = nullptr ) {
            cout << "ERRO:" << SDL_GetError() << "\n";
            return 1;
        }
    }
    
    // while (rodando) {
        // for (int i = -100; i <= 0 ; i+=5) {

            // SDL_Event windowEvent;
            // while ( SDL_PollEvent(&windowEvent) ) {
            //     if (SDL_QUIT == windowEvent.type) { 
            //         rodando = false;
            //         break;  
            //     }
            // }
    


    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}
