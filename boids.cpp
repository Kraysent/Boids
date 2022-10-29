#include <iostream>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Boid.h"
#include "Vector.h"

int N = 1000;
int Width = 1000;
int Height = 600;
double max_speed = 40.0;
double vision_radius = 80;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main( int argc, char *argv[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_SetWindowTitle(window, "Boids test");
    SDL_Texture* boid_texture = SDL_CreateTextureFromSurface(renderer, IMG_Load("boid.png"));
    
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return EXIT_FAILURE;
    }
    
    std::vector<Boid> boids;

    for (int i = 0; i < N; i++) {
        double vel_angle = fRand(0, 2 * M_PI);
        boids.push_back(Boid(Vector2(fRand(0.0, (double)Width), fRand(0.0, (double)Height)), Vector2(max_speed * cos(vel_angle), max_speed * sin(vel_angle))));
    }

    SDL_Event windowEvent;
    uint32_t currFrameTime = 0;
    uint32_t frameStart = 0;
    uint32_t frameDelay = 1000 / 60;

    while (true)
    {
        frameStart = SDL_GetTicks();

        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        for (const Boid& b : boids) {
            Vector2 coords = b.GetPosition();
            SDL_Rect input, out;

            SDL_QueryTexture(boid_texture, nullptr, nullptr, &input.w, &input.h);
            input.x = 0;
            input.y = 0;
            SDL_QueryTexture(boid_texture, nullptr, nullptr, &out.w, &out.h);
            out.x = coords.X - out.w / 2;
            out.y = coords.Y - out.h / 2;

            SDL_RenderCopyEx(renderer, boid_texture, &input, &out, (b.GetVelocity().GetAngle()) * 57.7, NULL, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(renderer);

        for (int i = 0; i < N; i++) {
            boids[i].Move(0.04);
            // boids[i].Steer(-0.0001);

            if (boids[i].Position.X > (double)Width) {
                boids[i].Position.X = 0.0;
            }
            if (boids[i].Position.X < 0.0) {
                boids[i].Position.X = (double)Width;
            }
            if (boids[i].Position.Y > (double)Height) {
                boids[i].Position.Y = 0.0;
            }
            if (boids[i].Position.Y < 0.0) {
                boids[i].Position.Y = (double)Height;
            }

            Vector2 avgSep = Vector2(0.0, 0.0);
            Vector2 avgPos = Vector2(0.0, 0.0);
            Vector2 avgVel = Vector2(0.0, 0.0);
            int neighbourCount = 0;

            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                
                // separation
                // if ((boids[j].Position - boids[j].Position).Magnitude() < vision_radius) {
                    
                // }

                // alignment

                if ((boids[j].Position - boids[i].Position).Magnitude() < vision_radius) {
                    avgSep -= boids[j].Position - boids[i].Position;
                    avgPos += boids[j].Position;
                    avgVel += boids[j].Velocity;

                    neighbourCount++;
                }
            }

            if (avgSep.Magnitude() != 0) {
                avgSep /= neighbourCount;
                avgSep /= avgSep.Magnitude();            
            }
            
            if (avgPos.Magnitude() != 0) {
                avgPos /= neighbourCount;
                avgPos /= avgPos.Magnitude();            
            }

            if (avgVel.Magnitude() != 0) {
                avgVel /= neighbourCount;
                avgVel /= avgVel.Magnitude();
            }

            boids[i].Velocity += avgSep * 0.01 + avgPos * 0.5 + avgVel * 0.5;

            boids[i].Velocity.ScaleToMagnitude(max_speed);
        }

        currFrameTime = (SDL_GetTicks() - frameStart);

        if (frameDelay > currFrameTime) {
            SDL_Delay(frameDelay - currFrameTime);
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}