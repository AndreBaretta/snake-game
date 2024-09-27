#include <raylib.h>

#define CELLSIZE 30
#define CELLCOUNT 25
#define TICKTIME 0.2
#define TITLE "JOGO"
#define TARGETFPS 60
#define SCREENSIZE CELLSIZE*CELLCOUNT

double last_tick = 0;
Vector2 cell_size = {CELLSIZE,CELLSIZE};

typedef enum {
    NORTH,
    EAST,
    WEST,
    SOUTH
} Direction;

typedef struct {
    Vector2 position;
} Node;

typedef struct {
    Vector2 head;
    Node nodes[CELLCOUNT*CELLCOUNT];
    unsigned int size;
} Snake;

typedef struct {
    Vector2 position;
} Fruit;

typedef struct {
    char up;
    char left;
    char down;
    char right;
} Controls;

Snake get_start_snake(){
    Snake snake = {{5,13}, { {{4,13}}, {{3,13}}, {{2,13}} }, 3};
    return snake;
}

void draw_snake(Snake snake){
    for(unsigned int i = 0; i < snake.size; i++){
        Vector2 draw_position = {snake.nodes[i].position.x*cell_size.x,snake.nodes[i].position.y*cell_size.y};
        DrawRectangleV(draw_position,cell_size,DARKGREEN);
    }
    Vector2 draw_position = {snake.head.x*cell_size.x,snake.head.y*cell_size.y};
    DrawRectangleV(draw_position,cell_size,BLUE);
}

int snake_should_move(){
    double time_now = GetTime();
    if(time_now - last_tick >= TICKTIME){
        last_tick = time_now;
        return 1;
    }
    return 0;
}

void snake_move(Snake* snake, Direction direction){
    for(int i = snake->size -1; i > 0; i--){
        snake->nodes[i].position = snake->nodes[i-1].position;
    }
    snake->nodes[0].position = snake->head;

    switch(direction){
        case NORTH:
            if(snake->head.y != 0){
                snake->head.y -= 1;
            } else {
                snake->head.y = 24;
            }
            break;
        case SOUTH:
            if(snake->head.y != 24){
                snake->head.y += 1;
            } else {
                snake->head.y = 0;
            }
            break;
        case EAST:
            if(snake->head.x != 24){
                snake->head.x += 1;
            } else {
                snake->head.x = 0;
            }
            break;
        case WEST:
            if(snake->head.x != 0){
                snake->head.x -= 1;
            } else {
                snake->head.x = 24;
            }
            break;
    }

}

int get_collision(Snake *snake, Vector2 *collision) {
    for(unsigned int i = 0; i < snake->size; i++){
        if(snake->head.x == snake->nodes[i].position.x && snake->head.y == snake->nodes[i].position.y){
            *collision = snake->head;
            return 1;
        }
    }
    return 0;
}

int generate_fruit(){

}

int init_game(){
    InitWindow(SCREENSIZE,SCREENSIZE,TITLE);
    SetTargetFPS(TARGETFPS);
    return 0;
}

int main() {
    init_game();
    Snake snake = get_start_snake();
    //Vector2 vector_collision;
    Direction direction = EAST;
    while(!WindowShouldClose()){
        if((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && direction != SOUTH){
            direction = NORTH;
        } else if((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && direction != NORTH){
            direction = SOUTH;
        } else if((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && direction != EAST){
            direction = WEST;
        } else if((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && direction != WEST){
            direction = EAST;
        }
        if(snake_should_move()){
            snake_move(&snake,direction);
        }
        BeginDrawing();
        ClearBackground(GREEN); 
        draw_snake(snake);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
    
