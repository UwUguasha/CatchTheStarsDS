#include <nds.h>
#include <nf_lib.h>
#include <filesystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// const definitions
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192
#define SPRITE_SIZE 64

// Character struct
typedef struct {
    s16 x, y;
    s8 speed;
} Character;

// Star struct
typedef struct {
    s16 x, y;
    s8 speed;
} Star;

// Global vars
Character character = {100, 50, 1};
Star star = {SCREEN_WIDTH, 0, 1};
u32 score = 0;
bool gameStarted = false;

// Functions to initialize graphics and backgrounds
void initGraphics() {
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);

    NF_InitTextSys(0);
    NF_InitTextSys(1);
}

//Function to load and show the background and title
void showTitleScreen() {
    NF_LoadTiledBg("bg/SpaceBackground", "SpaceBackground", 256, 256);
    NF_CreateTiledBg(0, 3, "SpaceBackground");
    NF_CreateTiledBg(1, 3, "SpaceBackground");

    NF_LoadTiledBg("bg/gameLogo", "gameLogo", 256, 256);
    NF_CreateTiledBg(0, 1, "gameLogo");
    NF_ScrollBg(0, 1, -32, -20);

    NF_LoadTextFont16("fnt/font16", "copyrightText", 256, 256, 0);
    NF_CreateTextLayer16(0, 0, 0, "copyrightText"); //for copyright hehe
    NF_WriteText16(0, 0, 7, 11, "Made by UwUguasho");

    NF_LoadTextFont16("fnt/font16", "startText", 256, 256, 0);
    NF_CreateTextLayer16(1, 0, 0, "startText");
    NF_WriteText16(1, 0, 3, 5, "Touch the screen to start!");
    NF_UpdateTextLayers();
}

// Function to load and create sprites
void loadSprites() {
    NF_LoadSpriteGfx("sprite/FlyingCat", 0, SPRITE_SIZE, SPRITE_SIZE);
    NF_LoadSpritePal("sprite/FlyingCat", 0);
    NF_VramSpriteGfx(0, 0, 0, true);
    NF_VramSpritePal(0, 0, 0);
    NF_CreateSprite(0, 0, 0, 0, character.x, character.y);

    NF_LoadSpriteGfx("sprite/Star", 1, SPRITE_SIZE, SPRITE_SIZE);
    NF_LoadSpritePal("sprite/Star", 1);
    NF_VramSpriteGfx(0, 1, 1, true);
    NF_VramSpritePal(0, 1, 1);
    star.y = rand() % (SCREEN_HEIGHT - SPRITE_SIZE);
    NF_CreateSprite(0, 1, 1, 1, star.x, star.y);
}

// Must i even define this lol
void moveCharacter() {
    scanKeys();
    int keys = keysHeld();

    if ((keys & KEY_LEFT) && (character.x >= character.speed)) {
        character.x -= character.speed;
    }
    if ((keys & KEY_RIGHT) && (character.x <= SCREEN_WIDTH - SPRITE_SIZE - character.speed)) {
        character.x += character.speed;
    }
    if ((keys & KEY_UP) && (character.y >= character.speed)) {
        character.y -= character.speed;
    }
    if ((keys & KEY_DOWN) && (character.y <= SCREEN_HEIGHT - SPRITE_SIZE - character.speed)) {
        character.y += character.speed;
    }

    NF_MoveSprite(0, 0, character.x, character.y);
}

// Same
void moveStar() {
    star.x -= star.speed;
    if (star.x < -SPRITE_SIZE) {
        star.x = SCREEN_WIDTH;
        star.y = rand() % (SCREEN_HEIGHT - SPRITE_SIZE);
    }
    NF_MoveSprite(0, 1, star.x, star.y);
}

// verifies the collision between the character and star
bool checkCollision() {
    // "Hitbox" margin
    int margin = 10;

    // Border coordinates with the margins
    int char_left = character.x + margin;
    int char_right = character.x + SPRITE_SIZE - margin;
    int char_top = character.y + margin;
    int char_bottom = character.y + SPRITE_SIZE - margin;

    int star_left = star.x + margin;
    int star_right = star.x + SPRITE_SIZE - margin;
    int star_top = star.y + margin;
    int star_bottom = star.y + SPRITE_SIZE - margin;

    // Checks the position of both sprites keeping the margin in mind
    return (char_right >= star_left && char_left <= star_right &&
            char_bottom >= star_top && char_top <= star_bottom);
}

// Shows score
void showScore() {
    char scoreStr[32];
    snprintf(scoreStr, sizeof(scoreStr), "Score: %lu", score);
    NF_WriteText16(1, 0, 0, 0, scoreStr);
    NF_UpdateTextLayers();
}

int main(int argc, char **argv) {
    // Initialize NitroFS
    consoleDemoInit();
    printf("\n Iniciando NitroFS, \n por favor, espere. \n\n");
    swiWaitForVBlank();
    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");

    initGraphics();
    showTitleScreen();

    // Wait until the user touches the bottom screen to start
    while (!gameStarted) {
        scanKeys();
        if (keysDown() & KEY_TOUCH) {
            gameStarted = true;
            NF_DeleteTiledBg(0, 1);
            NF_ClearTextLayer16(0, 0);
            NF_ClearTextLayer16(1, 0);
            loadSprites();
        }
        swiWaitForVBlank();
    }

    // Game main loop
    while (1) {
        moveCharacter();
        moveStar();

        if (checkCollision()) {
            score++;
            star.x = SCREEN_WIDTH;
            star.y = rand() % (SCREEN_HEIGHT - SPRITE_SIZE);
        }

        showScore();

        swiWaitForVBlank();
        NF_SpriteOamSet(0);
        oamUpdate(&oamMain);
    }

    return 0;
}
