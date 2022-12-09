#include "fx.cpp"
#include <iostream>
using namespace std;

char dir = 's';
char last_dir = 's';

#define LED_PIN 1
#define ROWS 16
#define COLS 16
#define LED_COUNT 16*16

#define UP	7
#define DOWN	6
#define LEFT	5
#define RIGHT	4
#define INTERRUPT 2

int map_px ( int l, int c ) {
	return l *  COLS + ((l % 2)?COLS-c-1:c);
}

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int snake_x = 6;
int snake_y = 6;

int growing = 2;
int snake_size = 3;

int apple_x;
int apple_y;

int power_x;
int power_y; 

int new_seed = 0;
int new_power = 0;
bool active_power = false;
bool obstacle = true;

uint32_t apple_color = 0xFF0000;
uint32_t snake_color = 0x00FF00;
uint32_t death_color = 0x0000FF;
uint32_t power_color = 0xFFFF00;

#define MAX_SNAKE_SIZE 500
int snake[MAX_SNAKE_SIZE][2] = { 0 };

volatile int button_pressed = 0;

void set_button_pressed(void) {
	button_pressed = 1;
}

bool flag = true;
void setup () {

	pinMode(UP, INPUT);
	pinMode(DOWN, INPUT);
	pinMode(LEFT, INPUT);
	pinMode(RIGHT, INPUT);
	pinMode(INTERRUPT, INPUT_PULLUP);
	
	attachInterrupt(digitalPinToInterrupt(INTERRUPT), set_button_pressed, RISING);

	randomSeed(analogRead(0));
	
	for(int i = 0; i < 12; i ++){
		for(int j = 0; j < 12; j ++){
			if(i == 0 || i == 11) strip.setPixelColor((i*12) + j, 255, 255, 255);
			else {
				strip.setPixelColor((i*12) + 11, 255, 255, 255);
				strip.setPixelColor((i*12), 255, 255, 255);
				break;
			}		
		}
	}

	apple_x = random(ROWS);
	apple_y = random(COLS);
	if(apple_x == snake_x) while(apple_y == snake_y) apple_y = random(COLS);
	
	for(int i = 0; i < snake_size; i++) {
		snake[i][0] = snake_x;
		snake[i][1] = snake_y;
	}

	strip.begin();

	strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);
	
	strip.show ();
	
}

void seed_apple() {
	apple_x = random(ROWS);
	apple_y = random(COLS);
	
	for(int i = 0; i < snake_size; i++) {
		if(apple_x == snake[i][0] && apple_y == snake[i][1]) {
			apple_x = random(ROWS);
			apple_y = random(COLS);
			i = 0;
		}
	}

	while(true){
		if (strip.getPixelColor((apple_x*12) + apple_y) == 16777215){
			apple_x = random(ROWS);
			apple_y = random(COLS);
		} else{
			break;
		}
	}

	strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
}

void reset_game() {
	
	strip.setPixelColor(map_px(snake_x, snake_y), death_color);
	strip.show();
	
	delay(1000);
	
	dir = 's';
	last_dir = 's';
	
	snake_x = ROWS / 2;	snake_y = COLS / 2;
	snake_size = 3;
	growing = 2;
	
	apple_x = random(ROWS);
	apple_y = random(COLS);
	new_seed = 0;
	new_power = 0;

	if(apple_x == snake_x) while(apple_y == snake_y) apple_y = random(COLS);
	
	for(int i = 0; i < snake_size; i++) {
		snake[i][0] = snake_x;
		snake[i][1] = snake_y;
	}
	
	strip.clear();
	
	
	
	for(int i = 0; i < 12; i ++){
		for(int j = 0; j < 12; j ++){
			if(i == 0 || i == 11) strip.setPixelColor((i*12) + j, 255, 255, 255);
			else {
				strip.setPixelColor((i*12) + 11, 255, 255, 255);
				strip.setPixelColor((i*12), 255, 255, 255);
				break;
			}		
		}
	}

	seed_apple();
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);

	strip.show();
	
}

void seed_power() {
	power_x = random(ROWS);
	power_y = random(COLS);

	for(int i = 0; i < snake_size; i++) {
		if(power_x == snake[i][0] && power_y == snake[i][1]) {
			power_x = random(ROWS);
			power_y = random(COLS);
			i = 0;
		}
	}

	while(true){
		if (strip.getPixelColor((power_x*12) + power_y) == 16777215){
			power_x = random(ROWS);
			power_y = random(COLS);
		} else if(apple_x == power_x && apple_y == power_y) {
			power_x = random(ROWS);
			power_y = random(COLS);
		} else{
			break;
		}
	}

	strip.setPixelColor(map_px(power_x, power_y), power_color);
}
void power_map(){
	if(obstacle){
		for(int i = 0; i < 12; i ++){
			for(int j = 0; j < 12; j ++){
				if(i == 0 || i == 11) strip.setPixelColor((i*12) + j, 0, 0, 0);
				else {
					strip.setPixelColor((i*12) + 11, 0, 0, 0);
					strip.setPixelColor((i*12), 0, 0, 0);
					break;
				}		
			}
		}

		strip.show();
		obstacle = false;
	}
	else{
		for(int i = 0; i < 12; i ++){
			for(int j = 0; j < 12; j ++){
				if((i*12) + j == (apple_x*12) + apple_y){
					apple_x = 6; apple_y = 6;
					strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
				}

				if((i*12) + j == (power_x*12) + power_y){
					power_x = 6; power_y = 6;
					strip.setPixelColor(map_px(power_x, power_y), power_color);
				}

				if(i == 0 || i == 11) strip.setPixelColor((i*12) + j, 255, 255, 255);
				else {
					strip.setPixelColor((i*12) + 11, 255, 255, 255);
					strip.setPixelColor((i*12), 255, 255, 255);
					break;
				}		
			}
		}

		while(true){
			if (strip.getPixelColor((apple_x*12) + apple_y) == 16777215){
				apple_x = random(ROWS);
				apple_y = random(COLS);
			} else{
				break;
			}
		}

		strip.show();
		obstacle = true;
	}
}
void change_direction() {
	
	//Debounce time
	delay(0);
	if(digitalRead(UP) == HIGH) {
		dir = 'u';
	} else if (digitalRead(DOWN) == HIGH) {
		dir = 'd';
	} else if (digitalRead(LEFT) == HIGH) {
		dir = 'l';
	} else if (digitalRead(RIGHT) == HIGH) {
		dir = 'r';
	}
	button_pressed = 0;
}

void move_snake(char c) {

	if(c == 'u' && last_dir == 'd') last_dir = 'd';
	else if(c == 'd' && last_dir == 'u') last_dir = 'u';
	else if(c == 'r' && last_dir == 'l') last_dir = 'l';
	else if(c == 'l' && last_dir == 'r') last_dir = 'r';
	else last_dir = c;
	
	switch(last_dir) { 
		case 'u' :
			snake_x = snake[0][0] - 1;
			snake_y = snake[0][1];
			if(snake_x == -1) snake_x = ROWS-1;
			break;
		case 'd' :
			snake_x = snake[0][0] + 1;
			snake_y = snake[0][1];
			if(snake_x == ROWS) snake_x = 0;
			break;
		case 'l' :
			snake_x = snake[0][0];
			snake_y = snake[0][1] - 1;
			if(snake_y == -1) snake_y = COLS-1;
			break;
		case 'r' :
			snake_x = snake[0][0];
			snake_y = snake[0][1] + 1;
			if(snake_y == COLS) snake_y = 0;
			break;
			
	}
	
	if(!growing) strip.setPixelColor(map_px(snake[snake_size-1][0], snake[snake_size-1][1]), 0);
	else --growing;
	
	if(snake_x == apple_x && snake_y == apple_y) {
		++growing;
		++snake_size;
		new_seed = 1;
		if(!active_power) new_power = 1;
	}
	
	if(snake_x == power_x && snake_y == power_y && active_power) {
		active_power = false;
		power_map();
	}

	for(int i = snake_size - 1; i > 0; i--) { 
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
		if(snake_x == snake[i][0] && snake_y == snake[i][1]) { reset_game(); return; }
		if(strip.getPixelColor((snake_x*12) + snake_y) == 16777215) { reset_game(); return; }
	}

	snake[0][0] = snake_x;
	snake[0][1] = snake_y;
	
	if(new_seed) { 
		seed_apple(); 
		new_seed = 0; 

		int power = random(100);
		if (new_power && power >= 0 && power <= 50) {
			seed_power();
			active_power = true;
			new_power = 0;
		}
	}
	
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);
}

void loop () {
	if(button_pressed) change_direction();
	if(dir != 's') move_snake(dir);
	strip.show();
	delay(100 - snake_size / 5);
}
