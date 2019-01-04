// ASSIGNMENT 1 - 2D PLATFORMER CODE
// by Neco Kriel
// cd onedrive/nk-projects/cgame
// gcc StreetFighter.c -Wall -Werror -std=gnu99 -L./ZDK -I./ZDK -lzdk -lncurses -lm -o StreetFighter && ./StreetFighter

// PACKAGES
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <curses.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// CONSTANTS
#define DELAY (50)
// player
#define PLAYER_WIDTH (5)
#define PLAYER_HEIGHT (5)
#define DASH (10)
#define JUMP (4)
#define VERTDRAG (0.3)
#define HORDRAG (0.2)
// fireball
#define SHOOT (5)
// castle
#define CASTLE_WIDTH (57)
#define CASTLE_HEIGHT (9)


// SPRITES
char * player_s_image =
/**/ "(0 0)"
/**/ " /|\\ "
/**/ "/ | \\"
/**/ " / \\ "
/**/ "/   \\";

char * player_l1_image =
/**/ "(0  )"
/**/ "\\/|\\ "
/**/ "  |/ "
/**/ " / \\_ "
/**/ "\\    ";

char * player_l2_image =
/**/ "(0  )"
/**/ " /|\\ "
/**/ "/ | |"
/**/ " / \\_ "
/**/ "\\    ";

char * player_l3_image =
/**/ "(0  )"
/**/ "  \\  "
/**/ " /|| "
/**/ " / \\_ "
/**/ "\\    ";

char * player_l4_image =
/**/ "(0  )"
/**/ " /\\  "
/**/ "/ /  "
/**/ " / \\_ "
/**/ "\\    ";

char * player_r1_image =
/**/ "(  0)"
/**/ " /|\\/"
/**/ " \\|  "
/**/ "_/ \\ "
/**/ "   / ";

char * player_r2_image =
/**/ "(  0)"
/**/ " /|| "
/**/ " ||\\ "
/**/ "_/ \\ "
/**/ "   / ";

char * player_r3_image =
/**/ "(  0)"
/**/ "  /  "
/**/ " ||\\ "
/**/ "_/ \\ "
/**/ "   / ";

char * player_r4_image =
/**/ "(  0)"
/**/ "  /\\ "
/**/ "  \\ \\"
/**/ "_/ \\ "
/**/ "   / ";

char * player_ur_image =
/**/ "\\  0/"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ "/  / ";

char * player_us_image =
/**/ "\\0 0/"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ "/   \\";

char * player_ul_image =
/**/ "\\0  /"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ " \\  \\";

char * fire_ball_l = 
/**/ "/~\\ "
/**/ "| ~~"
/**/ "\\~/ "; // 3x4

char * fire_ball_r = 
/**/ " /~\\"
/**/ "~~ |"
/**/ " \\~/"; // 3x4

char * fire_ball_u = 
/**/ " /~\\"
/**/ " | |"
/**/ " \\ /"; // 3x4

char * castle_image =
/**/	"	                                |>>>                                "
/**/	"      		                         |                                  "
/**/	"                    |>>>      _  _|_  _         |>>>                 "
/**/	"                    |        |;| |;| |;|        |                    "
/**/	"                _  _|_  _    \\\\.    .  /    _  _|_  _                "
/**/	"               |;|_|;|_|;|    \\\\:. ,  /    |;|_|;|_|;|               "
/**/	"               \\\\..      /    ||;   . |    \\\\.    .  /               "
/**/	"                \\\\.  ,  /     ||:  .  |     \\\\:  .  /                "
/**/	"                 ||:   |_   _ ||_ . _ | _   _||:   |                 "
/**/	"                 ||:  .|||_|;|_|;|_|;|_|;|_|;||:.  |                 "
/**/	"                 ||:   ||.    .     .      . ||:  .|                 "
/**/	"                 ||: . || .     . .   .  ,   ||:   |                 "
/**/	"                 ||:   ||:  ,  _______   .   ||: , |                 "
/**/	"                 ||:   || .   /+++++++\\    . ||:   |                 "
/**/	"                 ||:   ||.    |+++++++| .    ||: . |                 "
/**/	"                 ||: . ||: ,  |+++++++|.  . _||_   |                  ";  //16x69

char * plat_image =
/**/ "============================================================================================================================================================================================================================================================================================================"; // 300 characters 

char * wall_image =
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"
/**/ "[ ]"; // 30x3


// FUNCTION DEFINITIONS
int openingScreen(void);
void setup_game(void);
void game_process(void);
void draw_scene(void);
void update_player(int);
bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2);
void draw_time(void);

// STRUCT DEFINED
typedef struct Character {
    bool landed; // is the player grounded?
    double xh;   // player's x coordinate 
    double yh;   // player's y coordinate
    double dxh;  // player's x velocity
    double dyh;  // player's y velocity
    int itter;
} Character;
struct Character player1;
struct Character fireball;


// VARIABLE INITIALISATION
// sprites
sprite_id castle;
sprite_id platform1;
sprite_id wall1;
sprite_id wall2;
sprite_id player1_sprite;
sprite_id fireball_sprite;
// bool 
bool game_over = false;
// timer
time_t time_start;
time_t time_end;


// MAIN
int main(void) {
    setup_screen();

    int screen_opt = openingScreen();
    setup_game();
    time_start = time(NULL);

    while ((screen_opt == 1) && !game_over) {
        clear_screen();
        game_process();
        show_screen();
        timer_pause(DELAY);
    } // opt 2 and 3

    return 0;
}


// GAME OPENING SCREEN
int openingScreen() {
    char str1[] = "WELCOME";
    char str2[] = "Press 1 to play";
    char str3[] = "Press 2 to exit";

    // draw messages to screen
    clear_screen();
    draw_formatted((screen_width() - strlen(str1))/2, screen_height()/2, str1);
    draw_formatted((screen_width() - strlen(str2))/2, screen_height()/2 + 2, str2);
    draw_formatted((screen_width() - strlen(str3))/2, screen_height()/2 + 3, str3);
    show_screen();

    // receive input
    while (true) {
        int key = wait_char();
        if (key == '1') {
            return 1;
        } else if (key == '2') {
            return 2;
        } else if (key == '3') {
            return 3;
        }
    }
}


// INITIALISE EVERYTHING
void setup_game() {
    // initialise player 1
    player1.xh = screen_width()/2;
    player1.yh = screen_height() - PLAYER_HEIGHT - 1;
    player1.dxh = 0;
    player1.dyh = 0;
    player1.landed = true;
    player1.itter = 0;
    // create player sprite
    player1_sprite = sprite_create(player1.xh, player1.yh, PLAYER_WIDTH, PLAYER_HEIGHT, player_s_image);

    // initialise fire ball
    fireball.xh = screen_width()/2;
    fireball.yh = screen_height() - PLAYER_HEIGHT - 1;
    fireball.dxh = 0;
    fireball.dyh = 0;
    fireball.landed = false; // here landed means shot
    fireball.itter = 0;
    // create fireball sprite
    fireball_sprite = sprite_create(screen_width() + 5, screen_height() + 5, 4, 3, fire_ball_r);

    // create castle sprite
    castle = sprite_create(screen_width() - CASTLE_WIDTH, screen_height() - CASTLE_HEIGHT - 8, 69, 16, castle_image);

    // create platform/wall sprites
    platform1 = sprite_create(1, screen_height() - 1, screen_width() - 2, 1, plat_image);
    wall1 = sprite_create(0, 1, 3, screen_height() - 2, wall_image);
    wall2 = sprite_create(screen_width() - 3, 1, 3, screen_height() - 2, wall_image);

    
}


// GAME'S PROCESS FUNCTION
void game_process() {
    // draw scene
    draw_scene();

    // get user input
    int key = get_char();

    // update and draw player
    update_player(key);
    draw_time();

    player1.itter++;
    if (player1.itter == 100) {
        player1.itter = 0;
    }
}


// DRAW EVERYTHING IN THE SCENE
void draw_scene() {
    // draw castle
    sprite_draw(castle);

    // draw wall/platform
    sprite_draw(platform1);
    sprite_draw(wall1);
    sprite_draw(wall2);
}


// PLAYER MOVEMENT
void update_player(key) {
    // read player's previous position
    player1.xh = sprite_x(player1_sprite);
    player1.yh = sprite_y(player1_sprite);
    player1.dxh = sprite_dx(player1_sprite);
    player1.dyh = sprite_dy(player1_sprite);

    // interpret user input
    if (( 'a' == key || KEY_LEFT == key ) && player1.xh > 1) {
        // move left
        player1.dxh -= DASH;
    } else if (( 'd' == key || KEY_RIGHT == key ) && player1.xh < screen_width() - sprite_width(player1_sprite) - 1) {
        // move right
        player1.dxh += DASH;
    } else if (( 'w' == key || KEY_UP == key) && player1.landed) {
        // jump
        player1.dyh -= JUMP;
        player1.landed = false;
    }
    
    // shoot fireball
    if ('\n' == key) {
        // shoot
        fireball.landed = true;
        if (player1.dxh > 0) {
            // shoot right
            fireball.xh = player1.xh + PLAYER_WIDTH;
            fireball.yh = player1.yh + 1;
            fireball.dxh += SHOOT;
            sprite_move_to(fireball_sprite, fireball.xh, fireball.yh);
            sprite_set_image(fireball_sprite, fire_ball_r);
        } else if (player1.dxh < 0) {
            // shoot left
            fireball.xh = player1.xh - 4;
            fireball.yh = player1.yh + 1;
            fireball.dxh -= SHOOT;
            sprite_move_to(fireball_sprite, fireball.xh, fireball.yh);
            sprite_set_image(fireball_sprite, fire_ball_l);
        } else {
            // shoot up
            fireball.xh = player1.xh;
            fireball.yh = player1.yh - 3;
            fireball.dyh -= SHOOT;
            sprite_move_to(fireball_sprite, fireball.xh, fireball.yh);
            sprite_set_image(fireball_sprite, fire_ball_u);
        }
    }

    // apply drag
    player1.dxh -= HORDRAG*player1.dxh;
    if ((!player1.landed) && (player1.dyh <= JUMP)) {
        player1.dyh += VERTDRAG;
    }

    // move player horizontally
    if (sprites_collided(player1_sprite, wall1) || player1.xh < sprite_x(wall1) + 3) {
        sprite_move_to(player1_sprite, sprite_x(wall1) + 3, player1.yh);
        player1.dxh = 0;
        sprite_turn_to(player1_sprite, player1.dxh, player1.dyh);
        sprite_step(player1_sprite);
    } else if (sprites_collided(player1_sprite, wall2) || player1.xh > sprite_x(wall2)) {
        sprite_move_to(player1_sprite, sprite_x(wall2) - PLAYER_WIDTH, player1.yh);
        player1.dxh = 0;
        sprite_turn_to(player1_sprite, player1.dxh, player1.dyh);
        sprite_step(player1_sprite);
    }

    // move player vertically
    if (sprites_collided(player1_sprite, platform1)) {
        player1.yh = screen_height() - PLAYER_HEIGHT - 1;
        player1.dxh = 0;
        player1.dyh = 0;
        player1.landed = true;
        sprite_turn_to(player1_sprite, player1.dxh, player1.dyh);
        sprite_move_to(player1_sprite, player1.xh, player1.yh);
    } else {
        sprite_turn_to(player1_sprite, player1.dxh, player1.dyh);
        sprite_step(player1_sprite);
    }

    // change player's skin
    if (player1.dxh > 0) {
        if (player1.dyh == 0) {
            // if moving right and on the ground
            if (player1.itter % 20 < 5) {
                sprite_set_image(player1_sprite, player_r1_image);
            } else if (player1.itter % 20 < 10) {
                sprite_set_image(player1_sprite, player_r2_image);
            }  else if (player1.itter % 20 < 15) {
                sprite_set_image(player1_sprite, player_r3_image);
            } else {
                sprite_set_image(player1_sprite, player_r4_image);
            }
        } else {
            // if in the air and moving right
            sprite_set_image(player1_sprite, player_ur_image);
        }
    } else if (player1.dxh < 0) {
        if (player1.dyh == 0) {
            // if moving left and on the ground
            if (player1.itter % 20 < 5) {
                sprite_set_image(player1_sprite, player_l1_image);
            } else if (player1.itter % 20 < 10) {
                sprite_set_image(player1_sprite, player_l2_image);
            }  else if (player1.itter % 20 < 15) {
                sprite_set_image(player1_sprite, player_l3_image);
            } else {
                sprite_set_image(player1_sprite, player_l4_image);
            }
        } else {
            // if in the air and moving left
            sprite_set_image(player1_sprite, player_ul_image);
        }
    } else {
        if (player1.dyh > 0) {
            // if jumping directly up
            sprite_set_image(player1_sprite, player_us_image);
        } else {
            // if standing still up
            sprite_set_image(player1_sprite, player_s_image);
        }
    }

    // move fireball
    sprite_turn_to(fireball_sprite, 0, 0);
    sprite_step(fireball_sprite);

    // draw player
    sprite_draw(player1_sprite);
    sprite_draw(fireball_sprite);

    draw_formatted(screen_width()/8, screen_height()/8, "shot: %d", '\n' == key);
    draw_formatted(screen_width()/8, screen_height()/8 + 1, "x: %f", fireball.xh);
    draw_formatted(screen_width()/8, screen_height()/8 + 2, "y: %f", fireball.xh);
    draw_formatted(screen_width()/8, screen_height()/8 + 3, "vx: %f", fireball.dxh);
    draw_formatted(screen_width()/8, screen_height()/8 + 4, "vy: %f", fireball.dyh);
}


// SPRITE COLLISION CHECK
bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2) {
    int sprite_1_top = round(sprite_y(sprite_1));
    int sprite_1_bottom = sprite_1_top + sprite_height(sprite_1) - 1;
    int sprite_1_left = round(sprite_x(sprite_1));
    int sprite_1_right = sprite_1_left + sprite_width(sprite_1) - 1;
    int sprite_2_top = round(sprite_y(sprite_2));
    int sprite_2_bottom = sprite_2_top + sprite_height(sprite_2) - 1;
    int sprite_2_left = round(sprite_x(sprite_2));
    int sprite_2_right = sprite_2_left + sprite_width(sprite_2) - 1;
    return !(sprite_1_bottom < sprite_2_top || sprite_1_top > sprite_2_bottom || sprite_1_right < sprite_2_left || sprite_1_left > sprite_2_right);
}


// TIME
void draw_time() {
    double time_elap = difftime(time(NULL), time_start);
    int mins = floor(time_elap/60);
    int secs = (int) time_elap % 60;

    draw_formatted(screen_width()/8, screen_height()/8 - 1, "Game Timer: %02d:%02d", mins, secs);
}