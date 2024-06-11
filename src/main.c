#include <stdint.h>

#define PI 3.14159265358979323846

#define HEIGHT 400
#define WIDTH 600

#define RED    0xFF0000FF
#define GREEN  0xFF00FF00
#define BLUE   0xffFF0000
#define BLACK  0xff000000
#define YELLOW 0xFFFF00FF
#define CYAN   0xFFFFFF00
#define MAGENTA 0xFFFF00FF
#define BLACK   0xFF000000
#define COLOR_COUNT 8



// imports
void log(char*);
double sin(double x);

// globals
int32_t COLORS[COLOR_COUNT] = {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    BLACK,
};
int32_t pixels[HEIGHT][WIDTH] = {0};
float frequency =1,
    amplitude=1,
    phase=0;


// globals accessors
int32_t width(){
    return WIDTH;
}
int32_t height(){
    return HEIGHT;
}

int32_t get_pixels(){
    return pixels;
}
void set_frequency(float f){
    frequency = f;
}
void set_amplitude(float a){
    amplitude = a;
}
void set_phase(float a){
    phase = a;
}

// methods
void fill(int x, int y, int32_t color){
    pixels[y][x] = color;
}

void clear_pixels(){
    for(int32_t i=0;i<HEIGHT; i++){
        for(int32_t j=0; j<WIDTH; j++){
            pixels[i][j] = BLACK;
        }
    }
}

void draw_sine_wave(double frequency, double amplitude, double phase) {
    for (int x = 0; x < WIDTH; x++) {
        double angle = (2 * PI * frequency * (x - WIDTH / 2) / WIDTH) + phase;
        int y = (int)(HEIGHT / 2 + amplitude * (HEIGHT / 2) * sin(angle));
        if (y >= 0 && y < HEIGHT) {
            pixels[y][x] = GREEN;
        }
    }
}

float draw() {
    clear_pixels();
    draw_sine_wave(frequency, amplitude, phase);
    return 1;
}
