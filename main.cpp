#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL.h>
#include<iostream>
#include<cstdlib>
#include<ctime>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* args[]){

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "Sadly, the program cannot run. SDL Error: " << SDL_GetError() << std::endl;
      return -1;
   }
   if (TTF_Init() == -1) {
      std::cout << "TTF initialization error: " << TTF_GetError() << std::endl;
      SDL_Quit();
      return -1;
   }
   TTF_Font* font = TTF_OpenFont("Fonts/FreeSansBold.ttf", 24);
   if (font == nullptr) {
      std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
      SDL_Quit();
      return -1;
   }

   SDL_Window* window = SDL_CreateWindow("Some square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (window == nullptr) {
      std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
      SDL_Quit();
      return -1;
   }

   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   if (renderer == nullptr) {
      std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window);
      SDL_Quit();
      return -1;
   }
   // random generator
   std::srand(std::time(0));

   // general proprieties  
   bool quit{false};
   SDL_Event e;
   int score{0};
   int FOOTER_HEIGHT{60};
   int frame_counter{5}, FRAME_FREQUENCY{7};
   bool bird_angry = false;
   
   // position mouse and boom
   int rec_position_x{SCREEN_WIDTH / 4};
   int rec_position_y{SCREEN_HEIGHT / 4};
   const int REC_WIDTH{128};
   const int REC_HEIGHT{88};
   
   // bird position
   int random_postion_x{200}, random_postion_y{200}, BIRD_WIDTH{250}, BIRD_HEIGHT{250};
   float x_bird_speed{1}, y_bird_speed{1};
   
   // title display
   SDL_Color score_color = {0, 0, 0};
   SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Kill fck birds", score_color);
   SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
   SDL_FreeSurface(text_surface);
   SDL_Rect text_rect = {0, 0, SCREEN_WIDTH, 60};

   // load normal bird texture
   SDL_Surface* temp_surface = IMG_Load("image/duck_web.png");
   SDL_Texture* birdTexture = SDL_CreateTextureFromSurface(renderer, temp_surface);
   if (birdTexture == nullptr) {
      std::cout << "Failed to load bird texture: " << SDL_GetError() << std::endl;
   }
   SDL_FreeSurface(temp_surface);

   // angry bird load
   SDL_Surface* temp_surface_Angry = IMG_Load("image/white-46066_1280.png");
   SDL_Texture* AngrybirdTexture = SDL_CreateTextureFromSurface(renderer, temp_surface_Angry);
   if (AngrybirdTexture == nullptr) {
      std::cout << "Failed to load bird texture: " << SDL_GetError() << std::endl;
   }
   SDL_FreeSurface(temp_surface_Angry);

   // Load boom texture
   SDL_Surface* temp_surface1 = IMG_Load("image/bang-148261_1280.png");
   SDL_Texture* boom_texture = SDL_CreateTextureFromSurface(renderer, temp_surface1);
   if (boom_texture == nullptr) {
      std::cout << "Failed to load boom texture: " << SDL_GetError() << std::endl;
   }
   SDL_FreeSurface(temp_surface1);

   while(!quit){
      while(SDL_PollEvent(&e) != 0){
         if(e.type == SDL_QUIT){
               quit = true;
         }
         if(e.type == SDL_MOUSEBUTTONDOWN){
            if(e.button.button == SDL_BUTTON_LEFT){
               rec_position_x = e.button.x;
               rec_position_y = e.button.y;
               if((e.button.x >= random_postion_x && e.button.x <= BIRD_WIDTH + random_postion_x) && (e.button.y >= random_postion_y && e.button.y <= BIRD_HEIGHT + random_postion_y)){
                  if(bird_angry) {
                     bird_angry = false;
                     random_postion_x = std::rand() % (SCREEN_WIDTH - BIRD_WIDTH);
                     random_postion_y = FOOTER_HEIGHT + std::rand() % (SCREEN_HEIGHT - BIRD_HEIGHT - FOOTER_HEIGHT);
                  } else {
                     bird_angry = true;
                  }
               }
            }
         }
      }
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //background color
      SDL_RenderClear(renderer);
      
      if(bird_angry){
         // speed bird
         frame_counter++;
         if(frame_counter % FRAME_FREQUENCY == 0){
            random_postion_x += x_bird_speed;
            random_postion_y += y_bird_speed;
            frame_counter = 0;
         }

         // bounce the bird off the wall
         if(random_postion_x + BIRD_WIDTH >= SCREEN_WIDTH || random_postion_x <= 0){
            x_bird_speed = -x_bird_speed;
         }
         if(random_postion_y + BIRD_HEIGHT >= SCREEN_HEIGHT || random_postion_y <= FOOTER_HEIGHT){
            y_bird_speed = -y_bird_speed;
         }

         SDL_Rect bird = {random_postion_x, random_postion_y, BIRD_WIDTH, BIRD_HEIGHT};
         SDL_RenderCopy(renderer, AngrybirdTexture, nullptr, &bird);
      } else {
         // generate a bird
         SDL_Rect bird = {random_postion_x, random_postion_y, BIRD_WIDTH, BIRD_HEIGHT};
         SDL_RenderCopy(renderer, birdTexture, nullptr, &bird);
      }

      // generate a boom
      SDL_Rect boom = {rec_position_x - REC_WIDTH/2, rec_position_y - REC_HEIGHT/2, REC_WIDTH, REC_HEIGHT};
      SDL_RenderCopy(renderer, boom_texture, nullptr, &boom);

      // generate a text
      SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

      // generate a line 
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
      SDL_RenderDrawLine(renderer, 0, FOOTER_HEIGHT, SCREEN_WIDTH, FOOTER_HEIGHT);

      // display
      SDL_RenderPresent(renderer);
   }

   SDL_DestroyTexture(text_texture);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}

