#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include "audio.h"
#include "context.h"
#include "startmenu.h"

#define MS_PER_FRAME 90
unsigned int lastTimeStartMenu = 0;
unsigned int currentTimeStartMenu;
int run_menu = 1, quit = 0;
uint32_t last_frame = 0;

Start_menu Start_menu_new(){
    Start_menu start_menu;
    start_menu.screen_surface2 = SDL_GetWindowSurface(window);
    start_menu.menu_image[0] = IMG_Load("../assets/start_animation1.png");
    start_menu.menu_image[1] = IMG_Load("../assets/start_animation2.png");
    start_menu.menu_image[2] = IMG_Load("../assets/start_animation3.png");
    start_menu.menu_image[3] = IMG_Load("../assets/start_animation4.png");

    start_menu.position.x = 0;
    start_menu.position.y = 0;
    start_menu.position.w = 768;
    start_menu.position.h = 768;

    start_menu.frame = 0;

    return start_menu;
}

void Start_menu_draw(Start_menu start_menu, int frame){
    SDL_FillRect(start_menu.screen_surface2, NULL, SDL_MapRGB(start_menu.screen_surface2->format, 255, 255, 255));
    SDL_BlitSurface(start_menu.menu_image[frame], &start_menu.position, start_menu.screen_surface2, NULL);   
    SDL_UpdateWindowSurface(window);
}

int Start_menu_state(Start_menu *start_menu){
    if(last_frame + MS_PER_FRAME >= SDL_GetTicks()) {
        return 2;
    }

    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                run_menu = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    /*case SDLK_q:
                        run_menu = 0;
                        break;
                    */    
                    case SDLK_SPACE:
                        run_menu = 0;
                        break;                
                }
        }
    }

    
    currentTimeStartMenu = SDL_GetTicks();
    if(currentTimeStartMenu > lastTimeStartMenu + MS_PER_FRAME){
        if(start_menu->frame < 3){
            start_menu->frame++;
        }
        else{
            start_menu->frame = 0;
        }
    }
    lastTimeStartMenu = currentTimeStartMenu;
    
    last_frame = SDL_GetTicks();
    return run_menu;
}

void Start_menu_delete(Start_menu start_menu){
    for(int i=0; i<3; ++i){
        SDL_FreeSurface(start_menu.menu_image[i]);
    }
}