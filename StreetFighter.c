// ASSIGNMENT 1 - 2D PLATFORMER CODE
// by Neco Kriel
// cd onedrive/nk-projects/cgame
// gcc StreetFighter.c -Wall -Werror -std=gnu99 -L./ZDK -I./ZDK -lzdk -lncurses -lm -o StreetFighter && ./StreetFighter

// PACKAGES
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <curses.h>
#include <time.h>


// CONSTANTS
#define DELAY (50)

// player
#define PLAYER_WIDTH (5)
#define PLAYER_HEIGHT (5)
#define DASH (10)
#define JUMP (3)
#define VERTDRAG (0.3)
#define HORDRAG (0.4)

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


// FUNCTION DEFINITIONS
int openingScreen(void);
void setup_game(void);
void game_process(void);
void draw_scene(void);
void update_player(int);


// STRUCT DEFINED
typedef struct Player {
    bool landed; // is the player grounded?
    double xh;      // player's x coordinate 
    double yh;      // player's y coordinate
    double dxh;  // player's x velocity
    double dyh;  // player's y velocity
} Player;
struct Player player1;


// VARIABLE INITIALISATION
// sprites
sprite_id castle;
sprite_id platform1;
sprite_id player1_sprite;
// timer
time_t ini_time = 0;
// bool 
bool game_over = false;


// MAIN
int main(void) {
ini_time = time(0);
    setup_screen();

    int screen_opt = openingScreen();
    setup_game();

    while ((screen_opt == 1) && !game_over) {
        clear_screen();
        game_process();
        show_screen();
        timer_pause(DELAY);
    } // opt 2 and 3

    return 0;
}


// FUNCTION DEFINITIONS
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


void setup_game() {
    // initialise player 1
    player1.xh = screen_width()/2;
    player1.yh = screen_height() - PLAYER_HEIGHT - 1;
    player1.dxh = 0;
    player1.dyh = 0;
    player1.landed = true;

    // create castle sprite
    castle = sprite_create(screen_width() - CASTLE_WIDTH, screen_height() - CASTLE_HEIGHT - 8, 69, 16, castle_image);

    // create platform sprite
    platform1 = sprite_create(1, screen_height() - 1, screen_width() - 2, 1, plat_image);

    // create player sprite
    player1_sprite = sprite_create(player1.xh, player1.yh, PLAYER_WIDTH, PLAYER_HEIGHT, player_s_image);
}


void game_process() {
    // draw scene
    draw_scene();

    // get user input
    int key = get_char();

    // update and draw player
    update_player(key);
}


void draw_scene() {
    // draw castle
    sprite_draw(castle);

    // draw platform
    sprite_draw(platform1);
}


void update_player(key) {
    draw_formatted(screen_width()/4, screen_height()/4, "<-: %d", KEY_LEFT == key && player1.xh > 1);
    draw_formatted(screen_width()/4, screen_height()/4 + 1, "^^: %d", KEY_UP == key && player1.landed);
    draw_formatted(screen_width()/4, screen_height()/4 + 2, "->: %d", KEY_RIGHT == key && player1.xh < screen_width() - sprite_width(player1_sprite) - 1);
    draw_formatted(screen_width()/4, screen_height()*3/4 + 3, "landed: %d", player1.landed);

    // read player's previous position
    player1.xh = sprite_x(player1_sprite);
    player1.yh = sprite_y(player1_sprite);
    player1.dxh = sprite_dx(player1_sprite);
    player1.dyh = sprite_dy(player1_sprite);

    // interpret user input
    if (( 'a' == key || KEY_LEFT == key ) && player1.xh > 1) {
        player1.dxh -= DASH;
    } else if (( 'd' == key || KEY_RIGHT == key ) && player1.xh < screen_width() - sprite_width(player1_sprite) - 1) {
        player1.dxh += DASH;
    } else if (( 'w' == key || KEY_UP == key) && player1.landed) {
        player1.dyh -= JUMP;
        player1.landed = false;
    }

    // apply drag
    player1.dxh -= HORDRAG*player1.dxh;
    if ((!player1.landed) && (player1.dyh <= JUMP)) {
        player1.dyh += VERTDRAG;
    }

    // move player
    if (player1.yh > screen_height() - PLAYER_HEIGHT - 1) {
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

    // draw player
    sprite_draw(player1_sprite);

    draw_formatted(screen_width()/4, screen_height()*3/4 + 4, "x-pos %f", player1.xh);
    draw_formatted(screen_width()/4, screen_height()*3/4 + 5, "y-pos %f", player1.yh);
    draw_formatted(screen_width()/4, screen_height()*3/4 + 6, "h-vel %f", player1.dxh);
    draw_formatted(screen_width()/4, screen_height()*3/4 + 7, "v-vel %f", player1.dyh);
}