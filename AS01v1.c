// ASSIGNMENT 1 - 2D PLATFORMER CODE
// by Neco Kriel
// gcc AS01v1.c -Wall -Werror -std=gnu99 -L./ZDK -I./ZDK -lzdk -lncurses -lm -o AS01v1 && ./AS01v1

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <curses.h>
#include <time.h>

#define DELAY (50)
#define CASTLE_WIDTH (57)
#define CASTLE_HEIGHT (9)
#define HERO_WIDTH (5)
#define HERO_HEIGHT (5)
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)
#define EXIT_WIDTH (9)
#define EXIT_HEIGHT (8)
#define PLAT_HEIGHT (1)
#define BOULDER_HEIGHT (2)
#define BOULDER_WIDTH (4)
#define TRI_HEIGHT (2)
#define TRI_WIDTH (3)

char * key_image =
/**/ "0-+";

char * key21_image =
/**/ " $*";

char * key22_image =
/**/ " $ ";

char * key23_image =
/**/ "*$ ";

char * hero_l_image =
/**/ "(0  )"
/**/ "\\/|\\ "
/**/ "  | \\"
/**/ " / \\_ "
/**/ "\\    ";

char * hero_ll_image =
/**/ "(0  )"
/**/ "\\||\\ "
/**/ "  |/ "
/**/ " / \\_ "
/**/ "\\    ";

char * hero_s_image =
/**/ "(0 0)"
/**/ " /|\\ "
/**/ "/ | \\"
/**/ " / \\ "
/**/ "/   \\";

char * hero_r_image =
/**/ "(  0)"
/**/ " /|\\/"
/**/ "/ |  "
/**/ "_/ \\ "
/**/ "   / ";

char * hero_rr_image =
/**/ "(  0)"
/**/ " /||/"
/**/ " \\|  "
/**/ "_/ \\ "
/**/ "   / ";

char * hero_ur_image =
/**/ "\\  0/"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ "/  / ";

char * hero_us_image =
/**/ "\\0 0/"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ "/   \\";

char * hero_ul_image =
/**/ "\\0  /"
/**/ " \\|/ "
/**/ "  |  "
/**/ " / \\ "
/**/ " \\  \\";

char * boulder_image =
/**/ "/''\\"
/**/ "\\__/";

char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

char * tri1_image =
/**/ " : "
/**/ "/ \\";

char * tri2_image =
/**/ "\\ /"
/**/ " : ";

char * door_image =
/**/  " _______ "
/**/	"|=======|"
/**/	"|E X I T|"
/**/	"|=======|"
/**/	"|       |"
/**/	"|o      |"
/**/	"|       |"
/**/	"|_______|";

char * opendoor_image =
/**/	" _______ "
/**/	"|     //|"
/**/	"|    // |"
/**/	"|   //  |"
/**/	"|   ||  |"
/**/	"|   ||o |"
/**/	"|   ||  |"
/**/	"|___||__|"; // 8x9

char * emrald1_image =
/**/	" * /\\    "
/**/	"  /  \\   "
/**/	" /    \\  "
/**/	"/  $$  \\ "
/**/	"\\  $$  / "
/**/	" \\    /  "
/**/	"  \\  /   "
/**/	"   \\/  * ";

char * emrald2_image =
/**/	"   /\\    "
/**/	"  /  \\ * "
/**/	" /*   \\  "
/**/	"/  $$  \\ "
/**/	"\\  $$  / "
/**/	" \\    /  "
/**/	"* \\  /   "
/**/	"   \\/    ";

char * emrald3_image =
/**/	" * /\\  * "
/**/	"  /  \\   "
/**/	" /    \\  "
/**/	"/  $$  \\ "
/**/	"\\* $$  / "
/**/	" \\    /  "
/**/	"  \\  /   "
/**/	"   \\/    ";

char * emrald4_image =
/**/	"   /\\  * "
/**/	"* /  \\   "
/**/	" /    \\  "
/**/	"/  $$  \\ "
/**/	"\\  $$  / "
/**/	" \\    /  "
/**/	"  \\  /*  "
/**/	"   \\/    ";

char * emrald5_image =
/**/	"   /\\    "
/**/	"  /  \\*  "
/**/	" /    \\  "
/**/	"/  $$  \\ "
/**/	"\\  $$  / "
/**/	" \\    /  "
/**/	"  \\  /   "
/**/	" * \\/    ";

char * plat_image =
/**/ "============================================================================================================================================================================================================================================================================================================"; // 300 characters long

char * plat2_image =
/**/ "============================================================================================================================================================================================================================================================================================================"; // 300 characters long

char * msg_image =
/**/	"                    GAME OVER!                  "
/**/	"  Thank you for playing! Better luck next time! "
/**/	"            Press any key to exit...            ";

char * castle_image =
/**/  "   ___    ___    ___    ___    ___    ___    ___    ___  "
/**/	"__|   |__|   |__|   |__|   |__|   |__|   |__|   |__|   |_"
/**/	"||     ||  |  ||     || |   ||   | ||    |||  |  ||  |   "
/**/	"||=====||=====||=====||=====||=====||=====||=====||====  "
/**/	"||  |  ||     ||     ||   | ||     ||     ||   | || |    "
/**/	"||=====||=====||=====||=====||=====||=====||=====||====  "
/**/	"||     ||  |  ||     ||     || |   ||  |  ||     ||      "
/**/	"||=====||=====||=====||=====||=====||=====||=====||====  "
/**/	"||     ||     ||     ||     ||     ||     ||     ||      "; // 9x57

char * castle2_image =
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
/**/	"                 ||: . || .     . .   .  ,   ||:   |       \\,/       "
/**/	"                 ||:   ||:  ,  _______   .   ||: , |            /`\\  "
/**/	"                 ||:   || .   /+++++++\\    . ||:   |                 "
/**/	"                 ||:   ||.    |+++++++| .    ||: . |                 "
/**/	"                 ||: . ||: ,  |+++++++|.  . _||_   |                  "; //16x69

char * castle3_image =
/**/ "                                                |>>>                 "
/**/ "                                                |	                   "
/**/ "                                            _  _|_  _                "
/**/ "                                           |;|_|;|_|;|               "
/**/ "                                           \\\\.    .  /               "
/**/ "                                            \\\\:  .  /                "
/**/ "                                             ||:   |                 "
/**/ "                                             ||:.  |                 "
/**/ "                                             ||:  .|                 "
/**/ "                                             ||:   |       \\,/       "
/**/ "                                             ||: . |           /`\\   "
/**/ "                                             ||:   |                 "
/**/ "                                             ||: . |                 "
/**/ "              __                            _||_   |                 "
/**/ "     ____....    .....__            __ .....    .....,              _"
/**/ "......                  ~---__ ,...'                  ......_____... "; // 16x69

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
/**/ "[ ]"; // 30x3

char * instructions_msg =
/**/ " By Neco Kriel                               "
/**/ " INSTRUCTIONS (CASE SENSITIVE):              "
/**/ "      'UP ARROW' or 'w' = JUMP               "
/**/ "    'LEFT ARROW' or 'a' = MOVE LEFT          "
/**/ "   'RIGHT ARROW' or 'd' = MOVE RIGHT         "
/**/ "                    'l' = NEXT LEVEL         "
/**/ "                    'b' = PREVIOUS LEVEL     "
/**/ "                    'p' = PAUSE              "; // 8x45

char * collision_msg =
/**/	"                    GAME OVER!                  "
/**/	"  Thank you for playing! Better luck next time! "
/**/	"            Press any key to exit...            ";

char * welcome_msg =
/**/ "        _       _    __                                  __                   _ _ "
/**/ "       | |     | |  / _|                                / _|                 (_) |"
/**/ "  _ __ | | __ _| |_| |_ ___  _ __ _ __ ___  ___    ___ | |_   _ __   ___ _ __ _| |"
/**/ " | '_ \\| |/ _` | __|  _/ _ \\| '__| '_ ` _ \\/ __|  / _ \\|  _| | '_ \\ / _ \\ '__| | |"
/**/ " | |_) | | (_| | |_| || (_) | |  | | | | | \\__ \\ | (_) | |   | |_) |  __/ |  | | |"
/**/ " | .__/|_|\\__,_|\\__|_| \\___/|_|  |_| |_| |_|___/  \\___/|_|   | .__/ \\___|_|  |_|_|"
/**/ " | |                                                         | |                  "
/**/ " |_|                                                         |_|                  "; // 8x82

char * level_msg =
/**/ "  _                _ "
/**/ " | |              | |"
/**/ " | | _____   _____| |"
/**/ " | |/ _ \\ \\ / / _ \\ |"
/**/ " | |  __/\\ V /  __/ |"
/**/ " |_|\\___| \\_/ \\___|_|"; //6x21

char * numer1 =
//**/ "  __     "
/**/ " /_ |    "
/**/ "  | |    "
/**/ "  | |    "
/**/ "  | |    "
/**/ "  |_|    ";

char * numer2 =
/**/ "  ___    "
/**/ " |__ \\   "
/**/ "    ) |  "
/**/ "   / /   "
/**/ "  / /_   "
/**/ " |____|  ";


char * numer3 =
/**/ "  ____   "
/**/ " |___ \\  "
/**/ "   __) | "
/**/ "  |__ <  "
/**/ "  ___) | "
/**/ " |____/  ";

char * numer4 =
/**/ "  _  _   "
/**/ " | || |  "
/**/ " | || |_ "
/**/ " |__   _|"
/**/ "    | |  "
/**/ "    |_|  ";

char * numer5 =
/**/ "  _____  "
/**/ " | ____| "
/**/ " | |__   "
/**/ " |___ \\  "
/**/ "  ___) | "
/**/ " |____/  "; //6x9



void setup_hero(void);
void setup_zombie(void);
void draw_game(void);
void draw_background(void);
void draw_platforms(void);
void exit_animation(void);
void hero_skin(void);
void update_hero(int key);
void func_platform_collision(sprite_id sprite1, sprite_id sprite2[], int platnumber);
void update_sprite(sprite_id sprite);
void update_sprites(sprite_id sprites[], int num_sprites);
bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2);
void do_game_over(void);
void zombie_eats_hero(void);
void draw_border(void);
void draw_wall(void);
void setup_obj(void);
void setup_moving_plat(void);
void setup_boulder(void);
void update_boulder(void);
void last_animation(void);
void setup_tri(void);
void display_stats(void);
void start_screen(void);
void do_pause(void);
void timefunc(void);
void emrald_animate(void);
void key_animate(void);
void func_wall_collision(sprite_id sprite1, sprite_id sprite2);
sprite_id sprite_collided_with_any(sprite_id sprite, sprite_id sprites[], int num_sprites);
sprite_id zombie;
sprite_id inst;
sprite_id title;
sprite_id tri;
sprite_id hero;
sprite_id door;
sprite_id opendoor;
sprite_id castle;
sprite_id castle2;
sprite_id castle3;
sprite_id wall;
sprite_id boulder;
sprite_id getkey;
sprite_id platforms[5];
sprite_id platformsmoving[2];
sprite_id level_msg1;
sprite_id level_msg2;
sprite_id emrald;
timer_id MyTimer;

bool game_over = false;
bool update_screen = true;
bool colplat = false;
bool next_level = false;
bool blablabla = false;
bool key_taken = false;
bool level_test = false;
bool bouldering = false;
bool lose_life = false;
bool image = false;
bool landed = true;
double xh = 0;
double yh = 0;
double dxh = 0;
double dyh = 0;
double xplat1 = 0;
double yplat1 = 0;
double xplat2 = 0;
double yplat2 = 0;
double hspeed = 0;
int abcdef = 0;
int level_difficulty = 0;
int platform_collision = 10;
int level = 1; // start at level 1. level name -> level = {1:5}.
int plats = 0;
int n = 0; // animation value for door
int key_x = 0;
int key_y = 0;
int key_w = 0;
int key_h = 0;
int score = 0;
int xz = 0;
int yz = 0;
int xb = 0;
int yb = 0;
int plat_m_width = 0;
int lives = 10; // 10 lives
int times = 0;
int exit_x = 0;
int exit_y = 0;
time_t ini_time = 0;
int min10 = 0;
int min1 = 0;
int sec10 = 0;
int sec1 = 0;
int times2 = 0;
int times3 = 0;

// FUNCTIONS START HERE:
void setup(void) {
  n = 1; // set door to closed (2 -> door open)
  level_test = false;
  lose_life = false;
  setup_hero();
  if (level != 5 && level != 2 && level != 4){
    setup_zombie();
  }
  if (level == 5) {
    setup_boulder();
  }
  if (level == 2) {
    setup_tri();
  }
  if (level == 2|| level == 3 || level == 4 ) {
    setup_obj();
  }
  if (level == 3 || level == 5) {
    setup_moving_plat();
  }
  draw_game();
}

void process() {
  if (level == 1){
    plats = 3;
  }
  else if (level == 2) {
    plats = 4;
  }
  else if (level == 3 || level == 5) {
    plats = 2;
  }
  else if (level == 4) {
    plats = 5;
  }
  if (level == 6) {
    last_animation();
    return;
  }
  int key = get_char();
  if ( key == 'q' ) {
    do_game_over();
    return;
  }
  if (key == 'l' && level != 5) {
    clear_screen();
    level ++;
    next_level = true;
    return;
  }
  if (key == 'b' && level != 1) {
    clear_screen();
    level --;
    next_level = true;
    return;
  }
  if (key == 'p'){
    clear_screen();
    do_pause();
  }
  update_hero(key);
  if (sprite_collided_with_any(hero, platforms, plats)) {
    colplat = true;
    func_platform_collision(hero, platforms, platform_collision);
  }
  if ((level == 2 || level == 3 ) && (sprites_collided(hero, getkey) || key_taken)) {
    key_taken = true;
    if (sprites_collided(hero, getkey) && !level_test) {
      score += 100;
      level_test = true;
    }
    sprite_hide(getkey);
  }
  if (level == 4) {
    if (sprites_collided(hero, getkey) || key_taken) {
      key_taken = true;
      sprite_hide(getkey);
    }
    if (sprites_collided(hero, wall)) {
      blablabla = true;
      if (!key_taken) {
        func_wall_collision(hero, wall);
      }
    }
  }
  if (level == 3 || level == 5) {
    update_sprites(platformsmoving, 2);
    if (sprite_collided_with_any(hero, platformsmoving, 2)) {
      colplat = true;
      func_platform_collision(hero, platformsmoving, platform_collision);
    }
  }
  if (level == 5) {
    update_boulder();
    update_sprites(platformsmoving, 2);
    if (sprite_collided_with_any(boulder, platformsmoving, 2)) {
      func_platform_collision(boulder, platformsmoving, platform_collision);
    }
    if (sprite_collided_with_any(boulder, platforms, plats)) {
      colplat = true;
      func_platform_collision(boulder, platforms, platform_collision);
    }
    if (sprites_collided(hero, boulder)) {
      lives --;
      lose_life = true;
    }
  }
  if (level != 5 && level != 2 && level != 4) {
    update_sprite(zombie);
    if ( sprites_collided(hero, zombie) ) {
      lives --;
      lose_life = true;
    }
  }
  if (level == 2) {
    update_sprite(tri);
    if ( sprites_collided(hero, tri) ) {
      lives --;
      lose_life = true;
    }
  }
  if (lives == 0) {
    zombie_eats_hero();
    return;
  }

  if (level != 5) {
    if ( sprites_collided(hero, door)) {
      exit_animation();
      level ++;
      next_level = true;
      score += 100;
      clear_screen();
    }
  }
  if (level == 5 && !next_level) {
    if ( sprites_collided(hero, emrald)) {
      score += 1000;
      last_animation();
      return;
      clear_screen();
    }
  }

  if ( sprite_y(hero) >= screen_height() ) {
    lives --;
    lose_life = true;
  }
  if (!next_level){
    draw_game();
  }
  display_stats();
}

void cleanup() {
}


// MAIN:
int main(void) {
  ini_time = time(0);
  setup_screen();
  start_screen();
  if (level_difficulty == 1) {
    hspeed = 0.5;
  }
  else if (level_difficulty == 2) {
    hspeed = 1;
  }
  clear_screen();
  setup();
  show_screen();
  while ( !game_over ) {
    if (next_level || lose_life) {
      clear_screen();
      setup();
      next_level = false;
    }
    clear_screen();
    colplat = false;
    blablabla = false;
    process();
    if ( update_screen ) {
      show_screen();
    }
    timer_pause(DELAY);
  }
  cleanup();
  return 0;
}


// SUBFUNCTIONS START HERE:
void timefunc() {
  time_t now = time(0);
  sec1 = now - ini_time;
  if (sec1 == 10 && sec1 != 0) {
    ini_time = time(0);
    sec1 = 0;
    sec10 ++;
    if (sec10 == 6 && sec10 != 0) {
      sec10 = 0;
      min1 ++;
      if (min1 == 10 && min1 != 0) {
        min1 = 0;
        min10 ++;
      }
    }
  }
}

void do_pause() {
  int center = (screen_width()-16)/2;
  bool end = false;
  draw_formatted(center, screen_height()/2 - 4, "GAME IS PAUSED:");
  draw_formatted(center - 3, screen_height()/2 +1, "TO UNPAUSE: PRESS p");
  draw_formatted(center - 13, screen_height()/2 - 2, " Level: %d ", level);
  draw_formatted(center + 2, screen_height()/2 - 2, " Lives: %d ", lives);
  draw_formatted(center + 17, screen_height()/2 - 2," Score: %d ", score);

  int plat_x0 = screen_width()/2 - 20;
  int plat_y0 = screen_height()/2 - 1;
  platforms[0] = sprite_create(plat_x0, plat_y0, 38, PLAT_HEIGHT, plat_image);
  sprite_draw(platforms[0]);

  show_screen();
  int key2 = wait_char();
  while (!end){
    if ('p' == key2) {
      end = true;
    }
  }
}


void start_screen(){
  int center = (screen_width()-16)/2;
  bool end = false;
  while (!end){
    draw_formatted(center - 15, screen_height()/2, "CHOOSE DIFFICULTY (EASY RECOMMENDED):");
    draw_formatted(center-5, screen_height()/2 + 1, "EASY: PRESS 1");
    draw_formatted(center-5, screen_height()/2 + 2, "HARD: PRESS 2");


    title = sprite_create(screen_width()/2 - 41, screen_height()/2 - 8, 82, 8, welcome_msg);
    sprite_draw(title);

    inst = sprite_create(screen_width()/2 - 22, screen_height()/2 + 8, 45, 8, instructions_msg);
    sprite_draw(inst);

    show_screen();
    int key1 = wait_char();
    if ('1' == key1) {
      level_difficulty = 1;
      end = true;
    }
    else if ('2' == key1) {
      level_difficulty = 2;
      end = true;
    }
  }
}

void setup_obj() {
  if (level == 2) {
    key_x = screen_width()/2 - 1;
    key_y = screen_height()/5;
    key_w = 3;
    key_h = 1;
  }
  else if (level == 3) {
    key_x = screen_width()/2 - 1;
    key_y = screen_height()/5;
    key_w = 3;
    key_h = 1;
  }
  else if (level == 4) {
    key_x = screen_width()*19/20;
    key_y = screen_height()/5;
    key_w = 3;
    key_h = 1;
  }
  if (level != 4) {
    getkey = sprite_create(key_x, key_y, key_w, key_h, key21_image);
    key_animate();
  }
  else {
    getkey = sprite_create(key_x, key_y, key_w, key_h, key_image);
  }
  sprite_draw(getkey);
  key_taken = false;
}

void key_animate() {
  times2 ++;
  if (times2 % 5 == 0) {
    times3 ++;
  }
  if (times3 % 3 == 1) {
    sprite_set_image(getkey, key21_image);
  }
  else if (times3 % 3 == 2) {
    sprite_set_image(getkey, key22_image);
  }
  else {
    sprite_set_image(getkey, key23_image);
  }
}

void draw_game() {
  clear_screen();
  timefunc();
  draw_border();
  draw_platforms();
  if (level == 3 || level == 5) {
    sprite_draw(platformsmoving[0]);
    sprite_draw(platformsmoving[1]);
  }
  if (level == 2|| level == 3 || level == 4 ) {
    if (!key_taken) {
      if (level == 4) {
        draw_wall();
      }
      setup_obj();
    }
  }
  if (level == 5) {
    sprite_draw(boulder);
  }
  if (level == 2) {
    sprite_draw(tri);
  }
  sprite_draw(hero);
  if (level != 5 && level != 2 && level != 4){
    sprite_draw(zombie);
  }
}

void draw_wall() {
  int wall_x = screen_width()*3/5;
  int wall_y = 3*(screen_height() - 3)/4 + 1;
  wall = sprite_create(wall_x, wall_y, 3, screen_height()/4 + 1, wall_image);
  sprite_draw(wall);
}

void draw_platforms() {
  int plat_x0 = 0;
  int plat_y0 = 0;
  int plat_x1 = 0;
  int plat_y1 = 0;
  int plat_x2 = 0;
  int plat_y2 = 0;
  int plat_x3 = 0;
  int plat_y3 = 0;
  int plat_x4 = 0;
  int plat_y4 = 0;
  int width = 0;
  if (level == 1) {
    width = (screen_width()-2)/3;
    plat_x0 = 1;
    plat_y0 = screen_height() - 1;
    plat_x1 = (screen_width() - width)/2;
    plat_y1 = 3*(screen_height() - 3)/4;
    plat_x4 = 1;
    plat_y4 = 4;
    platforms[0] = sprite_create(plat_x0, plat_y0, screen_width() - 2, PLAT_HEIGHT, plat_image);
    platforms[1] = sprite_create(plat_x1, plat_y1, width, PLAT_HEIGHT, plat_image);
    platforms[2] = sprite_create(plat_x4, plat_y4, screen_width() - 2, PLAT_HEIGHT, plat_image);
    sprite_draw(platforms[0]);
    sprite_draw(platforms[1]);
    sprite_draw(platforms[2]);
  }
  else if (level == 2) {
    width = (screen_width()-2)/3;
    plat_y0 = screen_height() - 1;
    plat_y1 = 3*(screen_height() - 3)/4;
    plat_y2 = (screen_height() - 3)/2;
    plat_y4 = 4;

    plat_x0 = 1;
    plat_x1 = (screen_width() - width)/2;
    plat_x2 = (screen_width() - width/3)/2;
    plat_x4 = 1;

    platforms[0] = sprite_create(plat_x0, plat_y0, screen_width() - 2, PLAT_HEIGHT, plat_image);
    platforms[1] = sprite_create(plat_x1, plat_y1, width, PLAT_HEIGHT, plat_image);
    platforms[2] = sprite_create(plat_x2, plat_y2, width/3, PLAT_HEIGHT, plat_image);
    platforms[3] = sprite_create(plat_x4, plat_y4, screen_width() - 2, PLAT_HEIGHT, plat_image);
    sprite_draw(platforms[0]);
    sprite_draw(platforms[1]);
    sprite_draw(platforms[2]);
    sprite_draw(platforms[3]);
  }
  else if (level == 3) {
    plat_x0 = 1;
    plat_y0 = screen_height() - 1;
    plat_x4 = 1;
    plat_y4 = 4;
    platforms[0] = sprite_create(plat_x0, plat_y0, screen_width() - 2, PLAT_HEIGHT, plat_image);
    platforms[1] = sprite_create(plat_x4, plat_y4, screen_width() - 2, PLAT_HEIGHT, plat_image);
    sprite_draw(platforms[0]);
    sprite_draw(platforms[1]);
  }
  else if (level == 4) {
    plat_x0 = 1;
    plat_y0 = screen_height() - 1;
    plat_x1 = (screen_width()*2/5);
    plat_y1 = 3*(screen_height() - 3)/4;
    plat_x2 = 1;
    plat_y2 = (screen_height() - 3)/2;
    plat_x3 = (screen_width()*2/5);
    plat_y3 = (screen_height() - 3)/4;
    plat_x4 = 1;
    plat_y4 = 4;
    platforms[0] = sprite_create(plat_x0, plat_y0, screen_width() - 2, PLAT_HEIGHT, plat_image);
    platforms[1] = sprite_create(plat_x1, plat_y1, screen_width()*3/5, PLAT_HEIGHT, plat_image);
    platforms[2] = sprite_create(plat_x2, plat_y2, screen_width()*3/5, PLAT_HEIGHT, plat_image);
    platforms[3] = sprite_create(plat_x3, plat_y3, screen_width()*3/5, PLAT_HEIGHT, plat_image);
    platforms[4] = sprite_create(plat_x4, plat_y4, screen_width() - 2, PLAT_HEIGHT, plat_image);
    sprite_draw(platforms[0]);
    sprite_draw(platforms[1]);
    sprite_draw(platforms[2]);
    sprite_draw(platforms[3]);
    sprite_draw(platforms[4]);
  }
  else if (level == 5) {
    plat_x0 = 1;
    plat_y0 = screen_height() - 1;
    plat_x4 = 1;
    plat_y4 = 4;
    platforms[0] = sprite_create(plat_x0, plat_y0, screen_width()/4, PLAT_HEIGHT, plat_image);
    platforms[1] = sprite_create(plat_x4, plat_y4, screen_width() - 2, PLAT_HEIGHT, plat_image);
    sprite_draw(platforms[0]);
    sprite_draw(platforms[1]);
  }
}

void do_game_over() {
  game_over = true;
  clear_screen();
  int msg_height = 3;
  int msg_width = strlen(msg_image) / msg_height;
  sprite_id msg_box = sprite_create(
    (screen_width() - msg_width) / 2,
    (screen_height() - msg_height) / 2,
    msg_width, msg_height, msg_image);
    sprite_draw(msg_box);
    show_screen();
    wait_char();
  }

  void draw_border() {
    int left = 0, right = screen_width() - 1, top = 0, bottom = screen_height() - 1;
    draw_line(left, top, right, top, '=');
    draw_line(left, top, left, bottom, '|');
    draw_line(right, top, right, bottom, '|');
    draw_background();
    if (level != 5) {
      exit_x = screen_width() - EXIT_WIDTH - 1;
      exit_y = screen_height() - EXIT_HEIGHT - 1;
    }
    else if (level == 5){
      exit_x = (screen_width() - EXIT_WIDTH - 1)/2;
      exit_y = (screen_height() - EXIT_HEIGHT - 1)/4;
    }
    if (level != 5) {
      if (n == 1) {
        door = sprite_create(exit_x, exit_y, EXIT_WIDTH, EXIT_HEIGHT, door_image);
        sprite_draw(door);
      }
      else {
        opendoor = sprite_create(exit_x, exit_y, EXIT_WIDTH, EXIT_HEIGHT, opendoor_image);
        sprite_draw(opendoor);
      }
    }
    else if (level == 5) {
      emrald = sprite_create(exit_x, exit_y, EXIT_WIDTH, EXIT_HEIGHT, emrald1_image);
      emrald_animate();
      sprite_draw(emrald);
    }
  }

  void emrald_animate() {
    times2 ++;
    if (times2 % 5 == 0) {
      times3 ++;
    }
    if (times3 % 5 == 1) {
      sprite_set_image(emrald, emrald1_image);
    }
    else if (times3 % 5 == 2) {
      sprite_set_image(emrald, emrald2_image);
    }
    else if (times3 % 5 == 3) {
      sprite_set_image(emrald, emrald3_image);
    }
    else if (times3 % 5 == 4) {
      sprite_set_image(emrald, emrald4_image);
    }
    else {
      sprite_set_image(emrald, emrald5_image);
    }
  }

  void draw_background() {
    int castle_x = screen_width() - CASTLE_WIDTH - EXIT_WIDTH - 1;
    int castle_y = screen_height() - CASTLE_HEIGHT - 1;
    if (level != 5) {
      castle = sprite_create(castle_x, castle_y, CASTLE_WIDTH, CASTLE_HEIGHT, castle_image);
      sprite_draw(castle);
      castle2 = sprite_create(castle_x, castle_y - 15, 69, 16, castle2_image);
      sprite_draw(castle2);
    }
    else {
      castle3 = sprite_create(castle_x - 3, screen_height() - 17, 69, 16, castle3_image);
      sprite_draw(castle3);
    }
  }

  void hero_skin() {
    if (dxh == 0) {
      if (dyh < 0) {
        sprite_set_image(hero, hero_us_image);
      }
      else {
        sprite_set_image(hero, hero_s_image);
      }
    }
    else if (dxh > 0) {
      if (dyh < 0) {
        sprite_set_image(hero, hero_ur_image);
      }
      else {
        if (sprite_dx(hero) == 2) {
          sprite_set_image(hero, hero_rr_image);
        }
        else {
          sprite_set_image(hero, hero_r_image);
        }
      }
    }
    else {
      if (dyh < 0) {
        sprite_set_image(hero, hero_ul_image);
      }
      else {
        if (sprite_dx(hero) == -2) {
          sprite_set_image(hero, hero_ll_image);
        }
        else {
          sprite_set_image(hero, hero_l_image);
        }
      }
    }
  }

  void update_sprites(sprite_id sprites[], int num_sprites) {
    for ( int i = 0; i < num_sprites; i++ ) {
      sprite_id current_sprite = sprites[i];
      update_sprite(current_sprite);
    }
  }

  void update_sprite(sprite_id sprite) {
    sprite_step(sprite);
    int x = round(sprite_x(sprite));
    int y = round(sprite_y(sprite));
    double dx = sprite_dx(sprite);
    double dy = sprite_dy(sprite);
    if ( (x <= 0) || (x >= screen_width() - sprite_width(sprite)) ) dx = -dx;
    if ( (y <= 2) || (y >= screen_height() - sprite_height(sprite)) ) dy = -dy;
    if ( dx != sprite_dx(sprite) || dy != sprite_dy(sprite) ) {
      sprite_back(sprite);
      sprite_turn_to(sprite, dx, 0);
    }
    if (sprite == tri) {
      times ++;
      if ( times % 3 == 0) {
        if (image) {
          image = false;
          sprite_set_image(tri, tri1_image);
        }
        else {
          image = true;
          sprite_set_image(tri, tri2_image);
        }
      }
    }
  }

  void update_boulder() {
    int x = round(sprite_x(boulder));
    int y = round(sprite_y(boulder));
    double dx = sprite_dx(boulder);
    double dy = sprite_dy(boulder);
    // if (x >= screen_width() - 1 - sprite_width(boulder)) {
    //   x = screen_width() - 2 - sprite_width(boulder);
    //   sprite_step(boulder);
    // }
    // else if (x <= 1) {
    //   x = 2;
    //   sprite_step(boulder);
    // }
    if ( dy < 2) {
      dy += 0.2;
    }
    if ( (x <= 2) || (x >= screen_width() - sprite_width(boulder) - 2) ) {
      if (x <= 1) {
        x = 2;
        sprite_move_to(boulder, x, y);
      }
      else if (x >= screen_width() - 1 - sprite_width(boulder)) {
        x = screen_width() - 2 - sprite_width(boulder);
        sprite_move_to(boulder, x, y);
      }
      dx = -dx;
    }
    if ( y >= screen_height() - 2) {
      y = 5;
      sprite_move_to(boulder, x, y);
    }
    sprite_turn_to(boulder, dx, dy);
    sprite_step(boulder);
  }

  sprite_id sprite_collided_with_any(sprite_id sprite, sprite_id sprites[], int num_sprites) {
    platform_collision = 10; // 10 is neutral
    for ( int i = 0; i < num_sprites; i++ ) {
      sprite_id current_sprite = sprites[i];
      if ( sprite != current_sprite && sprites_collided(sprite, current_sprite) ) {
        platform_collision = i;
        return current_sprite;
      }
    }
    return NULL;
  }

  bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2) {
    int sprite_1_top = round(sprite_y(sprite_1)),
    sprite_1_bottom = sprite_1_top + sprite_height(sprite_1) - 1,
    sprite_1_left = round(sprite_x(sprite_1)),
    sprite_1_right = sprite_1_left + sprite_width(sprite_1) - 1;
    int sprite_2_top = round(sprite_y(sprite_2)),
    sprite_2_bottom = sprite_2_top + sprite_height(sprite_2) - 1,
    sprite_2_left = round(sprite_x(sprite_2)),
    sprite_2_right = sprite_2_left + sprite_width(sprite_2) - 1;
    return !(
      sprite_1_bottom < sprite_2_top
      || sprite_1_top > sprite_2_bottom
      || sprite_1_right < sprite_2_left
      || sprite_1_left > sprite_2_right
    );
  }

  void zombie_eats_hero() {
    game_over = true;
    clear_screen();
    int msg_height = 3;
    int msg_width = strlen(collision_msg) / msg_height;
    sprite_id msg_box = sprite_create(
      (screen_width() - msg_width) / 2,
      (screen_height() - msg_height) / 2,
      msg_width,
      msg_height,
      collision_msg);
      sprite_draw(msg_box);
      show_screen();
      timer_pause(1000);
      while ( get_char() >= 0 ){
      }
      wait_char();
    }

    void exit_animation() {
      n = 2;
      int ani_cost = round(screen_width()/5) + 2;
      int hero_x_end = screen_width() - EXIT_WIDTH - HERO_WIDTH - 1;
      int hero_y_end = screen_height() - HERO_HEIGHT - 1;
      timer_pause(200);
      clear_screen();
      draw_border();
      int castle_x = screen_width() - CASTLE_WIDTH - EXIT_WIDTH - 1;
      int castle_y = screen_height() - CASTLE_HEIGHT - 1;
      int exit_x = screen_width() - EXIT_WIDTH - 1;
      int exit_y = screen_height() - EXIT_HEIGHT - 1;
      int left = 0, right = screen_width() - 1, top = 0, bottom = screen_height() - 1;
      int middle_x1 = screen_width()/2 - 17, y1 = screen_height()/5;
      int middle_x2 = screen_width()/2 + 5;

      int plat_x0 = screen_width()/2 - 20;
      platforms[0] = sprite_create(plat_x0, y1 + 7, 36, PLAT_HEIGHT, plat_image);
      sprite_draw(platforms[0]);

      //draw box
      for (int y_ctr = 0; y_ctr < 5; y_ctr ++) {
        draw_line(1, y_ctr, right -1, y_ctr, '=');
      }

      level_msg1 = sprite_create(middle_x1, y1, 21, 6, level_msg);
      if (level == 1) {
        level_msg2 = sprite_create(middle_x2, y1, 9, 6, numer2);
      }
      else if (level == 2) {
        level_msg2 = sprite_create(middle_x2, y1, 9, 6, numer3);
      }
      else if (level == 3) {
        level_msg2 = sprite_create(middle_x2, y1, 9, 6, numer4);
      }
      else if (level == 4) {
        level_msg2 = sprite_create(middle_x2, y1, 9, 6, numer5);
      }

      sprite_draw(level_msg1);
      sprite_draw(level_msg2);

      castle = sprite_create(castle_x, castle_y, CASTLE_WIDTH, CASTLE_HEIGHT, castle_image);
      sprite_draw(castle);
      castle2 = sprite_create(castle_x, castle_y - 15, 69, 16, castle2_image);
      sprite_draw(castle2);
      hero = sprite_create(hero_x_end, hero_y_end, HERO_WIDTH, HERO_HEIGHT, hero_s_image);
      sprite_draw(hero);
      show_screen();
      timer_pause(250);
      clear_screen();
      for (int i = 1; i<8; i++) {
        hero_x_end ++;
        clear_screen();
        for (int y_ctr = 0; y_ctr < 5; y_ctr ++) {
          draw_line(1, y_ctr, right -1, y_ctr, '=');
        }
        sprite_draw(level_msg1);
        sprite_draw(level_msg2);
        draw_line(left, top, right, top, '=');
        draw_line(left, top+4, right, top+4, '=');
        draw_line(left, top, left, bottom, '|');
        draw_line(right, top, right, bottom, '|');
        draw_border();
        hero = sprite_create(hero_x_end, hero_y_end, HERO_WIDTH, HERO_HEIGHT, hero_r_image);
        draw_line(left, bottom, right, bottom, '=');
        sprite_draw(hero);
        sprite_draw(platforms[0]);

        show_screen();
        timer_pause(100);
      }
      for (int i = 1; i < ani_cost; i++) {
        hero_x_end -= 4;
        castle_x -= 5;
        exit_x -= 5;
        clear_screen();
        for (int y_ctr = 0; y_ctr < 5; y_ctr ++) {
          draw_line(1, y_ctr, right -1, y_ctr, '=');
        }
        sprite_draw(level_msg1);
        sprite_draw(level_msg2);
        draw_line(left, top, right, top, '=');
        draw_line(left, top+4, right, top+4, '=');
        draw_line(left, top, left, bottom, '|');
        draw_line(right, top, right, bottom, '|');
        draw_line(left, bottom, right, bottom, '=');
        opendoor = sprite_create(exit_x, exit_y, EXIT_WIDTH, EXIT_HEIGHT, opendoor_image);
        sprite_draw(opendoor);
        castle = sprite_create(castle_x, castle_y, CASTLE_WIDTH, CASTLE_HEIGHT, castle_image);
        sprite_draw(castle);
        castle2 = sprite_create(castle_x, castle_y - 15, 69, 16, castle2_image);
        sprite_draw(castle2);
        hero = sprite_create(hero_x_end, hero_y_end, HERO_WIDTH, HERO_HEIGHT, hero_r_image);
        sprite_draw(hero);
        sprite_draw(platforms[0]);

        show_screen();
        timer_pause(100);
      }
    }

    void last_animation() {
      game_over = true;
      clear_screen();
      bool end = false;
      int center = screen_width()/2 - 12.5;
      int centery = screen_height()/2;
      while (!end){
        draw_formatted(center, centery-3, "CONGRADULATIONS! You WON!");
        draw_formatted(center, centery-1, "Your final score was: %d   ", score);
        draw_formatted(center + 3, centery +1, "You had %d lives left      ", lives);
        draw_formatted(center - 15, centery +3, "You also completed the game in %d%d minute(s) and %d%d seconds!", min10, min1, sec10, sec1);
        draw_formatted(center, centery-3, "Press any key to exit..");
        show_screen();
        if (wait_char()) {
          end = true;
        }
      }
    }

    void func_wall_collision(sprite_id sprite1, sprite_id sprite2) {
      double xhl = round(sprite_x(sprite1)),  yht = round(sprite_y(sprite1));
      double dxh1 = sprite_dx(sprite1), dyh1 = sprite_dy(sprite1);
      dxh1 = -dxh1;
      sprite_move_to(hero, xhl, yht);
      sprite_turn_to(hero, dxh1, dyh1);
      sprite_step(hero);
    }

    void func_platform_collision(sprite_id sprite1, sprite_id sprite2[], int platnumber) {
      double xhl = round(sprite_x(sprite1)),  yht = round(sprite_y(sprite1));
      double xhr = xhl + sprite_width(sprite1) -1, yhb = yht + sprite_height(sprite1) -1;
      double dxh1 = sprite_dx(sprite1), dyh1 = sprite_dy(sprite1);
      double xp1 = round(sprite_x(sprite2[platnumber])), yp1 = round(sprite_y(sprite2[platnumber]));
      if ((yht <= yhb) && dyh1 <= 0 ){
        dyh1 = -dyh1;
        sprite_move_to(sprite1, xhl, yp1);
      }
      else if (xhr - 1 == xp1 && dxh1 > 0){
        dxh1 = -dxh1;
        sprite_move_to(sprite1, xhl, yht);
      }
      else if (xhr == xp1 + sprite_width(sprite2[platnumber]) -1 && dxh1 < 0){
        dxh1 = -dxh1;
        sprite_move_to(sprite1, xhl, yht);
      }
      else {
        if (sprite1 == hero){
          landed = true;
        }
        dyh1 = 0;
        sprite_move_to(sprite1, xhl, yp1 - sprite_height(sprite1));
      }
      sprite_turn_to(sprite1, dxh1, dyh1);
      sprite_step(sprite1);
    }

    void update_hero(int key) {
      xh = sprite_x(hero);
      yh = sprite_y(hero);
      dxh = sprite_dx(hero);
      dyh = sprite_dy(hero);
      if (( 'a' == key || KEY_LEFT == key ) && xh > 1 && dxh >-2 && landed) {
        dxh -= hspeed;
      }
      else if (( 'd' == key || KEY_RIGHT == key ) && xh < screen_width() - sprite_width(hero) - 1 && dxh <2 && landed) {
        dxh += hspeed;
      }
      else if (( 'w' == key || KEY_UP == key) && yh > 3 && landed) {
        dyh = -2;
        landed = false;
      }
      sprite_turn_to(hero, dxh, dyh);
      sprite_step(hero);
      if ((dxh < 0 && xh <= 2) || (dxh > 0 && xh >= screen_width() - sprite_width(hero) - 3)) {
        dxh = 0;
        if (xh < 2) {
          xh = 2;
        }
        else if (xh > screen_width() - sprite_width(hero) - 3) {
          xh = screen_width() - sprite_width(hero) - 3;
        }
      }
      if (dyh < 0 && yh <= 5) {
        dyh = -dyh;
        yh = 5;
      }
      sprite_move_to(hero, xh, yh);
      sprite_step(hero);
      hero_skin();
      dyh += 0.15;
      sprite_turn_to(hero, dxh, dyh);
      sprite_step(hero);
    }

    void setup_moving_plat() {
      if (level == 3) {
        plat_m_width = screen_width()*2/5;
        xplat1 = 1, yplat1 = 3*(screen_height() - 3)/4;
        xplat2 = screen_width()*3/5, yplat2 = (screen_height() - 3)/2;
      }
      else if (level == 5) {
        xplat1 = 1, yplat1 = 3*(screen_height() - 3)/4;
        xplat2 = screen_width()/2, yplat2 = (screen_height() - 3)/2;
        plat_m_width = screen_width()/2;
      }
      platformsmoving[0] = sprite_create(xplat1, yplat1, plat_m_width, PLAT_HEIGHT, plat2_image);
      platformsmoving[1] = sprite_create(xplat2, yplat2, plat_m_width, PLAT_HEIGHT, plat2_image);
      sprite_turn_to(platformsmoving[0], 1.5*hspeed, 0);
      sprite_step(platformsmoving[0]);
      sprite_turn_to(platformsmoving[1], -1.5*hspeed, 0);
      sprite_step(platformsmoving[1]);
    }

    void setup_hero() {
      xh = 1, yh = (screen_height() - HERO_HEIGHT - 1);
      hero = sprite_create(xh, yh, HERO_WIDTH, HERO_HEIGHT, hero_s_image);
    }

    void setup_boulder() {
      xb = (screen_width() - BOULDER_WIDTH - 1)/2;
      // xb = screen_width() - 4;
      yb = screen_height()/10;
      boulder = sprite_create(xb, yb, BOULDER_WIDTH, BOULDER_HEIGHT, boulder_image);
      sprite_turn_to(boulder, 2.5*hspeed, 0);
      sprite_step(boulder);
      bouldering = true;
    }

    void setup_zombie() {
      xz = screen_width() - ZOMBIE_WIDTH - 1;
      yz = screen_height() - ZOMBIE_HEIGHT - 1;
      zombie = sprite_create(xz, yz, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);
      sprite_turn_to(zombie, hspeed, 0);
      sprite_step(zombie);
    }

    void setup_tri() {
      xz = screen_width() - TRI_WIDTH - 1;
      yz = screen_height() - TRI_HEIGHT - 2;
      tri = sprite_create(xz, yz, TRI_WIDTH, TRI_HEIGHT, tri1_image);
      sprite_turn_to(tri, 1.5*hspeed, 0);
      sprite_step(tri);
    }

    void display_stats() {
      if (level_difficulty == 1) {
        draw_formatted(2, 2, " Difficulty: EASY");
      }
      else {
        draw_formatted(2, 2, " Difficulty: HARD");
      }
      draw_formatted(30, 2, "Time: %d%d:%d%d", min10, min1, sec10, sec1);
      draw_formatted(50, 2," Score: %d ", score);
      draw_formatted(70, 2, " Level: %d ", level);
      draw_formatted(85, 2, " Lives:");
      for (int i = 0; i < lives; i++){
        draw_formatted(95 + 3*i, 1, " o ");
        draw_formatted(95 + 3*i, 2, "/|\\");
        draw_formatted(95 + 3*i, 3, "/ \\");
      }
    }
