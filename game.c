#include <ace/managers/viewport/simplebuffer.h>
#include <ace/managers/joy.h>
#include <ace/managers/key.h>
#include <ace/managers/system.h>
#include <ace/managers/game.h>
#include <ace/utils/palette.h>
#include <ace/utils/font.h>
#include <stdio.h>
#include <ace/managers/rand.h>
#include <ace/managers/state.h>
#include <ace/utils/custom.h>
#include <ace/utils/ptplayer.h>
#include <ace/utils/file.h>

//------------------------------------------------------- gdzie� przed funkcjami
// zmienne trzymaj�ce adresy do viewa, viewporta, simple buffer managera
static tView *s_pView;
static tVPort *s_pVp;
static tSimpleBufferManager *s_pVpManager;
static tBitMap *s_pCards;

static tPtplayerMod *s_pMod;

static tFont *s_pFont;
static tTextBitMap *s_pBmText;

extern tStateManager *g_pStateMachineGame;


#define Y_STARTING_POINT 100
#define NUMBER_OF_CARDS_IN_DECK 10

const char *cardNames[NUMBER_OF_CARDS_IN_DECK] = {
  "Brick Shortage",
  "Lucky Cache",
  "Friendly Terrain",
  "Miners",
  "Mother Lode",
  "Dwarven Miners",
  "Work Overtime",
  "Copping the Tech",
  "Basic Wall",
  "Sturdy Wall"};

// printing resources on screen 
char s_pPlayerTower[4];
char s_pPlayerWall[4];
char s_pPlayerZoo[4];  
char s_pPlayerMagic[4]; 
char s_pPlayerQuarry[4];  

char s_pPlayerBeasts[4];
char s_pPlayerGems[4];
char s_pPlayerBricks[4];

char s_pCardinHand[6];
char s_pConfirm[35];

// as above, PC opponent
char s_pOppTower[4];
char s_pOppWall[4];
char s_pOppZoo[4];
char s_pOppMagic[4];
char s_pOppQuarry[4];  

char s_pOppBeasts[4];
char s_pOppGems[4];
char s_pOppBricks[4];

// handy variables 
UBYTE redSquare = 2;
UBYTE blueSquare = 9;
UBYTE greenSquare = 1;
UBYTE towercolor = 16;
UBYTE wallcolor = 15;
UBYTE generatorColor = 21;
UBYTE resourceColor = 0;
UBYTE onTowerPrintColor = 28;
UBYTE txtWaitTime = 100; 

// starting settings
UBYTE playerTower = 50;
UBYTE playerWall = 25;
UBYTE oppTower = 50;
UBYTE oppWall = 25;

UBYTE playerZoo = 3;
int playerBeasts = 12;
UBYTE playerMagic = 3;
int playerGems = 10;
UBYTE playerQuarry = 3;
int playerBricks = 10;

UBYTE oppZoo = 3;
int oppBeasts = 12;
UBYTE oppMagic = 3;
int oppGems = 10;
UBYTE oppQuarry = 3;
int oppBricks = 10;

// if cost will be higher than resource deny playing card, to be rearranged with structs
UBYTE gemCost = 0;
UBYTE beastCost = 0;
UBYTE brickCost = 0;


// six slots for cards hand, remember 0 to 5  !!!one
UBYTE cardSlot[6];

// keeping the number of recently selected and showed on screen card, for the confirmation of play
UBYTE selectedCard = 99;

// each card can be drawn once, so gonna set to 1 those that was drawn to avoid repetitions
UBYTE ArrayOfCards[NUMBER_OF_CARDS_IN_DECK];

// misc
UBYTE musicPlay = 1;

void waitFrames(tVPort *pVPort, UBYTE ubHowMany, UWORD uwPosY)
{
  for (UBYTE i = 0; i < ubHowMany; ++i)
  {
    vPortWaitForPos(pVPort, uwPosY);
  }
}






void brickShortage(void){
  brickCost = 0;
  if (brickCost > playerBricks){
   blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerBricks = playerBricks - 8;
  oppBricks = oppBricks - 8;  
  }
}

void luckyCache(void){
  brickCost = 0;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerBricks = playerBricks + 2;
  playerGems = playerGems + 2;
  // dorobic play again
  }
}

void friendlyTerrain (void){
  brickCost = 1;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerWall = playerWall + 1;
  playerBricks = playerBricks - 1;
  // dorobic play again
  }
}

void miners(void){
  brickCost = 3;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerQuarry = playerQuarry  + 1;
  playerBricks = playerBricks - 3;
  }
}

void motherLode(void) {
  brickCost = 4;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
    if (playerQuarry < oppQuarry){
      playerQuarry = playerQuarry + 2;
    }
    else
    {
     playerQuarry = playerQuarry + 1;
    }
    playerBricks = playerBricks - 4; 
  }
}

void dwarvenMiners(void){
  brickCost = 7;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerWall = playerWall + 4;
  playerQuarry = playerQuarry + 1;
  playerBricks = playerBricks - 7;
  }
}

void workOvertime(void){
  brickCost = 2;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerWall = playerWall + 5;
  playerGems = playerGems - 6;
  playerBricks = playerBricks - 2;
  }
} 

void coppingTheTech(void){
  brickCost = 5;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  if (playerQuarry < oppQuarry){
    playerQuarry = oppQuarry;
  }
  playerBricks = playerBricks- 5;
  }
}

void basicWall(void){
  brickCost = 2;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerWall = playerWall + 3;
  playerBricks = playerBricks - 2;
  }
}

void sturdyWall(void){
  brickCost = 3;
  if (brickCost > playerBricks){
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf (s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE); 
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  return;
  }
  else {
  playerWall = playerWall + 4;
  playerBricks = playerBricks - 3;
  }
}


void deckShuffle (void){
  for (UBYTE i = 0; i < NUMBER_OF_CARDS_IN_DECK ; ++i){
    ArrayOfCards[i] = i;
  }
  for (UBYTE i = 0; i < NUMBER_OF_CARDS_IN_DECK - 1; ++i){
    size_t j = i + uwRandMinMax(0, NUMBER_OF_CARDS_IN_DECK) / (NUMBER_OF_CARDS_IN_DECK / (NUMBER_OF_CARDS_IN_DECK - i) + 1);
    int t = ArrayOfCards[j];
    ArrayOfCards[j] = ArrayOfCards[i];
    ArrayOfCards[i] = t;
  }
}

void ScreenSetup(void)
{
  blitRect(s_pVpManager->pBack, 0, 0, 320, 128, 0);   // black background
  blitRect(s_pVpManager->pBack, 2, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 2, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 2, 68, 32, 32, greenSquare); // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 40, Y_STARTING_POINT - playerTower, 32, playerTower, towercolor); // player tower drawing
  blitRect(s_pVpManager->pBack, 76, Y_STARTING_POINT - playerWall, 32, playerWall, wallcolor); // player wall drawing
  blitRect(s_pVpManager->pBack, 286, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 286, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 286, 68, 32, 32, greenSquare); // // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 250, Y_STARTING_POINT - oppTower, 32, oppTower, towercolor); // PC tower
  blitRect(s_pVpManager->pBack, 214, Y_STARTING_POINT - oppWall, 32, oppWall, wallcolor); // PC wall
  
}

void PrintPlayerResources(void)
{
  blitRect(s_pVpManager->pBack, 2, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 2, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 2, 68, 32, 32, greenSquare); // trzy kwadraty na surowce gracza
  blitRect(s_pVpManager->pBack, 40, Y_STARTING_POINT - playerTower, 32, playerTower, towercolor); // wieza gracza
  blitRect(s_pVpManager->pBack, 76, Y_STARTING_POINT - playerWall, 32, playerWall, wallcolor); // mur gracza
  sprintf (s_pPlayerTower, "%d", playerTower);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerTower);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 44, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf (s_pPlayerWall, "%d", playerWall);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerWall);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 78, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf (s_pPlayerZoo, "%d", playerZoo);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerZoo);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 70, generatorColor, FONT_COOKIE);
  sprintf (s_pPlayerMagic, "%d", playerMagic);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerMagic);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 36, generatorColor, FONT_COOKIE);
  sprintf (s_pPlayerQuarry, "%d", playerQuarry);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerQuarry);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 2, generatorColor, FONT_COOKIE);

  sprintf (s_pPlayerBeasts, "%d", playerBeasts);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerBeasts);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 90, resourceColor, FONT_COOKIE);
  sprintf (s_pPlayerGems, "%d", playerGems);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerGems);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 56, resourceColor, FONT_COOKIE);
  sprintf (s_pPlayerBricks, "%d", playerBricks);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerBricks);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 22, resourceColor, FONT_COOKIE);
}

void PrintOpponentResources(void)
{
  blitRect(s_pVpManager->pBack, 286, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 286, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 286, 68, 32, 32, greenSquare); // // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 250, Y_STARTING_POINT - oppTower, 32, oppTower, towercolor); // PC tower
  blitRect(s_pVpManager->pBack, 214, Y_STARTING_POINT - oppWall, 32, oppWall, wallcolor); // PC wall
  sprintf (s_pOppTower, "%d", oppTower);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppTower);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 252, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf (s_pOppWall, "%d", oppWall);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppWall);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 216, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf (s_pOppZoo, "%d", oppZoo);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppZoo);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 70, generatorColor, FONT_COOKIE);
  sprintf (s_pOppMagic, "%d", oppMagic);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppMagic);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 36, generatorColor, FONT_COOKIE);
  sprintf (s_pOppQuarry, "%d", oppQuarry);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppQuarry);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 2, generatorColor, FONT_COOKIE);

  sprintf (s_pOppBeasts, "%d", oppBeasts);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppBeasts);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 90, resourceColor, FONT_COOKIE);
  sprintf (s_pOppGems, "%d", oppGems);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppGems);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 56, resourceColor, FONT_COOKIE);
  sprintf (s_pOppBricks, "%d", oppBricks);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppBricks);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 22, resourceColor, FONT_COOKIE);
}

void DrawStartingHand(void){
  for (UBYTE i = 0; i < 6; ++i){
  cardSlot[i] = ArrayOfCards[i];           // put card in a slot
  sprintf (s_pCardinHand, "%d. %s", i+1, cardNames[cardSlot[i]]);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pCardinHand);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 128 + (i * 10), generatorColor, FONT_COOKIE);
  }
};


void stateGameCreate(void)
{
  // Here goes your startup code
  //-------------------------------------------------------------- gdzie� w create
  s_pView = viewCreate(0,
                       TAG_VIEW_COPLIST_MODE, COPPER_MODE_BLOCK, // spos�b u�ywania coppera - ten jest najprostszy bo nic z nim nie musisz wi�cej robi�
                       TAG_VIEW_GLOBAL_CLUT, 1,                  // globalna paleta dla wszystkich viewport�w
                       TAG_END                                   // wi�cej argument�w nie ma
  );

  s_pVp = vPortCreate(0,
                      TAG_VPORT_VIEW, s_pView, // parent view
                      TAG_VPORT_BPP, 5,        // bits per pixel: 4bpp = 16col, 5pp = 32col, etc.
                      TAG_END);

  ptplayerCreate(1);
  s_pMod = ptplayerModCreate("data/placeholdermod.mod");
  ptplayerLoadMod(s_pMod, 0, 0);

  // Paleta 
  paletteLoad("data/amimage.plt", s_pVp->pPalette, 32);

  g_pCustom->color[0] = 0x0FFF; // zmie� kolor zero aktualnie u�ywanej palety na 15,15,15

  s_pCards = bitmapCreateFromFile("data/arco32.bm", 0);          // z pliku tileset.bm, nie lokuj bitmapy w pami�ci FAST
 

  

  s_pFont = fontCreate("data/topaz.fnt");
  s_pBmText = fontCreateTextBitMap(300, s_pFont->uwHeight); // bitmapa robocza długa na 200px, wysoka na jedną linię tekstu

  // proste wy�wietlanie bitmapy na viewporcie
  s_pVpManager = simpleBufferCreate(0,
                                    TAG_SIMPLEBUFFER_VPORT, s_pVp,                              // parent viewport
                                    TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED, // wst�pne czyszczenie bitmapy, przyspieszenie rysowania grafiki
                                    TAG_SIMPLEBUFFER_IS_DBLBUF, 0,                              // nie potrzebujemy double buffering
                                    TAG_SIMPLEBUFFER_BOUND_WIDTH, 320 + 16,
                                    TAG_END);

  cameraSetCoord(s_pVpManager->pCamera, 0, 0);

 
  
  joyOpen(); // b�dziemy u�ywa� d�oja w grze
  keyCreate();
  // na koniec create:

  randInit(1537);

  
  
  ScreenSetup();
  PrintPlayerResources();
  PrintOpponentResources();
  deckShuffle();
  DrawStartingHand();
  


  

  viewProcessManagers(s_pView);
  viewLoad(s_pView);

  ptplayerEnableMusic(0);
  systemUnuse(); // system w trakcie loop nie jest nam potrzebny
}

void stateGameLoop(void)
{
 
  joyProcess();
  keyProcess();

  
  if (keyUse(KEY_1) )
  {
  blitCopy(s_pCards, cardSlot[0] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF); // narysujmy se karte  
  selectedCard = cardSlot[0];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_2) )
  {
  blitCopy(s_pCards, cardSlot[1] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF); 
  selectedCard = cardSlot[1];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_3))
  {
  blitCopy(s_pCards, cardSlot[2] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF);
  selectedCard = cardSlot[2];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_4))
  {
  blitCopy(s_pCards, cardSlot[3] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF); 
  selectedCard = cardSlot[3];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_5))
  {
  blitCopy(s_pCards, cardSlot[4] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF); 
  selectedCard = cardSlot[4];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_6))
  {
   blitCopy(s_pCards, cardSlot[5] * 96, 0, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY, 0xFF);
  selectedCard = cardSlot[5];
  sprintf (s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  }
  else if (keyUse(KEY_RETURN) && selectedCard != 99){
    switch (selectedCard){
      case 0:
      brickShortage();
      
      break;
      case 1:
      luckyCache();
      break;

      case 2:
      friendlyTerrain();     
      break;

      case 3:
      miners();   
      break;

      case 4:
      motherLode();     
      break;

      case 5:
      dwarvenMiners();
      break;

      case 6:
      workOvertime();
      break;

      case 7:
      coppingTheTech();
      break;

      case 8:
      basicWall();
      break;

      case 9:
      sturdyWall();
      break;
      

    }
    PrintPlayerResources();
    PrintOpponentResources();
  }



  else if (keyUse(KEY_ESCAPE))
  {
    ptplayerStop();
    
 
    // stateChange(g_pStateMachineGame, &g_sStateMenu);
    return;
  }
  
  else if (keyUse(KEY_M))
  {
    if (musicPlay == 1)
    {
      musicPlay = 0;
      mt_mastervol(0);
    }
    else if (musicPlay == 0)
    {
      musicPlay = 1;
      mt_mastervol(64);
    }
  }


  

  

  viewProcessManagers(s_pView); // obliczenia niezb�dne do poprawnego dzia�ania viewport�w
  copProcessBlocks();           // obliczenia niezb�dne do poprawnego dzia�ania coppera
  
}

void stateGameDestroy(void)
{
  // Here goes your cleanup code
  systemUse(); // w��cz grzecznie system
  ptplayerModDestroy(s_pMod);
  ptplayerDestroy();
  

  fontDestroy(s_pFont);
  fontDestroyTextBitMap(s_pBmText);

  viewDestroy(s_pView); // zwolnij z pami�ci view, wszystkie do��czone do niego viewporty i wszystkie do��czone do nich mened�ery
  joyClose();
  keyDestroy();
}

// pod funkcjami bo kompilator czyta od g�ry do do�u i musi najpierw napotka� funkcje by wiedzie� �e istniej�
tState g_sStateGame = {
    .cbCreate = stateGameCreate,
    .cbLoop = stateGameLoop,
    .cbDestroy = stateGameDestroy,
    .cbSuspend = 0,
    //.cbResume = gameOnResume,
    .pPrev = 0};
