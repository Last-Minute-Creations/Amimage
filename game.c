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
extern tState g_sStateMenu;

#define Y_STARTING_POINT 100
#define NUMBER_OF_CARDS_IN_DECK 102

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
    "Sturdy Wall",
    "Innovations",
    "Foundations",
    "Tremors",
    "Secret Room",
    "Earthquake",
    "Big Wall",
    "Collapse",
    "New Equipment",
    "Strip Mine",
    "Reinforced Wall",
    "Porticulus",
    "Crystal Rocks",
    "Harmonic Ore",
    "MondoWall",
    "FocusedDesigns",
    "Great Wall",
    "Rock Launcher",
    "Dragon's Heart",
    "Forced Labor",
    "Rock Garden",
    "Flood Water",
    "Barracks",
    "Battlements",
    "Shift",
    "Quartz",
    "Smoky Quartz",
    "Amethyst",
    "Spell Weavers",
    "Prism",
    "Lodestone",
    "Solar Flare",
    "Crystal Matrix",
    "Gemstone Flaw",
    "Ruby",
    "Gem Spear",
    "Power Burn",
    "Harmonic Vibe",
    "Parity",
    "Emerald",
    "Pearl of Wisdom",
    "Shatterer",
    "Crumblestone",
    "Sapphire",
    "Discord",
    "Fire Ruby",
    "Quarry's Help",
    "Crystal Shield",
    "Empathy Gem",
    "Diamond",
    "Sanctuary",
    "Lava Jewel",
    "Dragon's Eye",
    "Crystalize",
    "Bag of Baubles",
    "Rainbow",
    "Apprentice",
    "Lightning Shard",
    "Phase Jewel",
    "MadCowDisease",
    "Faerie",
    "Moody Goblins",
    "Minotaur",
    "Elven Scout",
    "Goblin Mob",
    "Goblin Archers",
    "Shadow Faerie",
    "Orc",
    "Dwarves",
    "Little Snakes",
    "Troll Trainer",
    "Tower Gremlin",
    "Full Moon",
    "Slasher",
    "Ogre",
    "Rabid Sheep",
    "Imp",
    "Spizzer",
    "Werewolf",
    "Corrosion Cloud",
    "Unicorn",
    "Elven Archers",
    "Succubus",
    "Rock Stompers",
    "Thief",
    "Stone Giant",
    "Vampire",
    "Dragon",
    "Spearman",
    "Gnome",
    "Beserker",
    "Warlord",
    "Pegasus Lancer"};

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

UBYTE dealDamage = 0;

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

// keeping the place thats getting freed for drawing next card
UBYTE slotPlayed;

// keeping the number of recently selected and showed on screen card, for the confirmation of play
UBYTE selectedCard = 200;

// each card can be drawn once, so gonna set to 1 those that was drawn to avoid repetitions
extern ArrayOfCards[NUMBER_OF_CARDS_IN_DECK];
UBYTE CardSequenceCount = 0;

// misc
UBYTE musicPlay = 1;

void waitFrames(tVPort *pVPort, UBYTE ubHowMany, UWORD uwPosY)
{
  for (UBYTE i = 0; i < ubHowMany; ++i)
  {
    vPortWaitForPos(pVPort, uwPosY, 0);
  }
}

void drawNextCard(void)
{
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf(s_pConfirm, "Drawing a card...");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  ++CardSequenceCount;
  cardSlot[slotPlayed] = ArrayOfCards[CardSequenceCount];
  blitRect(s_pVpManager->pBack, 4, 128 + (slotPlayed * 10), 140, 10, 0);
  
  sprintf(s_pCardinHand, "%d. %s",  slotPlayed + 1, cardNames[cardSlot[slotPlayed]]);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pCardinHand);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 128 + (slotPlayed * 10), generatorColor, FONT_COOKIE);
}

void notEnoughBricks(void)
{
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf(s_pConfirm, "Not enough bricks to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
}

void notEnoughGems(void)
{
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf(s_pConfirm, "Not enough gems to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
}

void notEnoughBeasts(void)
{
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
  sprintf(s_pConfirm, "Not enough beasts to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
  waitFrames(s_pVp, txtWaitTime, 1);
  blitRect(s_pVpManager->pBack, 40, 115, 270, 10, 0);
}

void pleaseConfirm(void)
{
  sprintf(s_pConfirm, "Press Enter to play this card.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pConfirm);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 40, 116, generatorColor, FONT_COOKIE);
}

void playerAttack(void)
{
  if (oppWall == 0)
  {
    oppTower = oppTower - dealDamage;
  }
  else if (oppWall >= dealDamage)
  {
    oppWall = oppWall - dealDamage;
  }
  else if (oppWall < dealDamage)
  {
    UBYTE excessDamage = dealDamage - oppWall;
    oppWall = 0;
    oppTower = oppTower - excessDamage;
  }
}

void oppAttack(void)
{
  if (playerWall == 0)
  {
    playerTower = playerTower - dealDamage;
  }
  else if (playerWall >= dealDamage)
  {
    playerWall = playerWall - dealDamage;
  }
  else if (playerWall < dealDamage)
  {
    UBYTE excessDamage = dealDamage - playerWall;
    playerWall = 0;
    playerTower = playerTower - excessDamage;
  }
}

// RED CARDS

void brickShortage(void)
{
  brickCost = 0;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerBricks = playerBricks - 8;
    oppBricks = oppBricks - 8;
  }
}

void luckyCache(void)
{
  brickCost = 0;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerBricks = playerBricks + 2;
    playerGems = playerGems + 2;
    // dorobic play again
  }
}

void friendlyTerrain(void)
{
  brickCost = 1;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 1;
    playerBricks = playerBricks - 1;
    // dorobic play again
  }
}

void miners(void)
{
  brickCost = 3;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerQuarry = playerQuarry + 1;
    playerBricks = playerBricks - 3;
  }
}

void motherLode(void)
{
  brickCost = 4;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    if (playerQuarry < oppQuarry)
    {
      playerQuarry = playerQuarry + 2;
    }
    else
    {
      playerQuarry = playerQuarry + 1;
    }
    playerBricks = playerBricks - 4;
  }
}

void dwarvenMiners(void)
{
  brickCost = 7;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 4;
    playerQuarry = playerQuarry + 1;
    playerBricks = playerBricks - 7;
  }
}

void workOvertime(void)
{
  brickCost = 2;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 5;
    playerGems = playerGems - 6;
    playerBricks = playerBricks - 2;
  }
}

void coppingTheTech(void)
{
  brickCost = 5;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    if (playerQuarry < oppQuarry)
    {
      playerQuarry = oppQuarry;
    }
    playerBricks = playerBricks - 5;
  }
}

void basicWall(void)
{
  brickCost = 2;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 3;
    playerBricks = playerBricks - 2;
  }
}

void sturdyWall(void)
{
  brickCost = 3;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 4;
    playerBricks = playerBricks - 3;
  }
}

void innovations(void)
{
  brickCost = 2;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    ++playerQuarry;
    ++oppQuarry;
    playerGems = playerGems + 4;
    playerBricks = playerBricks - 2;
  }
}

void foundations(void)
{
  brickCost = 3;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    if (playerWall == 0)
    {
      playerWall = playerWall + 6;
    }
    else
    {
      playerWall = playerWall + 3;
    }
    playerBricks = playerBricks - 3;
  }
}

void tremors(void)
{
  brickCost = 7;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall - 5;
    oppWall = oppWall - 5;
    playerBricks = playerBricks - 7;
    // dorobic play again
  }
}

void secretRoom(void)
{
  brickCost = 8;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerMagic = playerMagic + 1;
    playerBricks = playerBricks - 8;
    // dorobic play again
  }
}

void earthquake(void)
{
  brickCost = 0;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    --playerQuarry;
    --oppQuarry;
    playerBricks = playerBricks - 0;
  }
}

void bigWall(void)
{
  brickCost = 5;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 6;
    playerBricks = playerBricks - 5;
  }
}

void collapse(void)
{
  brickCost = 4;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    oppQuarry = oppQuarry - 1;
    playerBricks = playerBricks - 4;
  }
}

void newEquipment(void)
{
  brickCost = 6;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    ++playerQuarry;
    ++playerQuarry;
    playerBricks = playerBricks - 6;
  }
}

void stripMine(void)
{
  brickCost = 0;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    --playerQuarry;
    playerWall = playerWall + 10;
    playerGems = playerGems + 5;
    playerBricks = playerBricks - 0;
  }
}

void reinforcedWall(void)
{
  brickCost = 8;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 8;
    playerBricks = playerBricks - 8;
  }
}

void porticulus(void)
{
  brickCost = 9;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 5;
    ++playerZoo;
    playerBricks = playerBricks - 9;
  }
}

void crystalRocks(void)
{
  brickCost = 9;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 7;
    playerGems = playerGems + 7;
    playerBricks = playerBricks - 9;
  }
}

void harmonicOre(void)
{
  brickCost = 11;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 6;
    playerTower = playerTower + 3;
    playerBricks = playerBricks - 11;
  }
}

void mondoWall(void)
{
  brickCost = 13;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 12;
    playerBricks = playerBricks - 13;
  }
}

void focusedDesigns(void)
{
  brickCost = 15;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 8;
    playerTower = playerTower + 5;
    playerBricks = playerBricks - 15;
  }
}

void greatWall(void)
{
  brickCost = 16;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 15;
    playerBricks = playerBricks - 16;
  }
}

void rockLauncher(void)
{
  brickCost = 18;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 6;
    dealDamage = 10;
    playerAttack();
    playerBricks = playerBricks - 18;
  }
}

void dragonsHeart(void)
{
  brickCost = 24;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 20;
    playerTower = playerTower + 8;
    playerBricks = playerBricks - 24;
  }
}

void forcedLabor(void)
{
  brickCost = 7;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 9;
    playerBeasts = playerBeasts - 5;
    playerBricks = playerBricks - 7;
  }
}

void rockGarden(void)
{
  brickCost = 1;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    ++playerWall;
    ++playerTower;
    ++playerBeasts;
    ++playerBeasts;
    playerBricks = playerBricks - 1;
  }
}

void floodWater(void)
{
  brickCost = 6;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    if (playerWall < oppWall)
    {
      --playerZoo;
      --playerTower;
      --playerTower;
    }
    else if (oppWall < playerWall)
    {
      --oppZoo;
      --oppTower;
      --oppTower;
    }
    else if (playerWall == oppWall)
    {
      --playerZoo;
      --playerTower;
      --playerTower;
      --oppZoo;
      --oppTower;
      --oppTower;
    }
    playerBricks = playerBricks - 6;
  }
}

void barracks(void)
{
  brickCost = 10;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerBeasts = playerBeasts + 6;
    playerWall = playerWall + 6;
    if (playerZoo < oppZoo)
    {
      ++playerZoo;
    }
    playerBricks = playerBricks - 10;
  }
}

void battlements(void)
{
  brickCost = 14;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    playerWall = playerWall + 7;
    dealDamage = 6;
    playerAttack();
    playerBricks = playerBricks - 14;
  }
}

void shift(void)
{
  brickCost = 17;
  if (brickCost > playerBricks)
  {
    notEnoughBricks();
    return;
  }
  else
  {
    UBYTE switching = playerWall;
    playerWall = oppWall;
    oppWall = switching;
    playerBricks = playerBricks - 17;
  }
}

// BLUE CARDS

void quartz(void)
{
  gemCost = 1;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 1;
    playerGems = playerGems - 1;
    // add play again
  }
}

void smokyQuartz(void)
{
  gemCost = 2;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    --oppTower;
    playerGems = playerGems - 2;
    // add play again
  }
}

void amethyst(void)
{
  gemCost = 2;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 3;
    playerGems = playerGems - 2;
  }
}

void spellWeavers(void)
{
  gemCost = 3;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    ++playerMagic;
    playerGems = playerGems - 3;
  }
}

void prism(void)
{
  gemCost = 2;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    // DOROBIC DRAW I PISAC DALEJ !!!!
  }
}

void lodestone(void)
{
  gemCost = 5;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 3;
    // DOROBIC CANT BE DISCARDED !!!!
    playerGems = playerGems - 5;
  }
}

void solarFlare(void)
{
  gemCost = 4;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 2;
    oppTower = oppTower - 2;
    playerGems = playerGems - 4;
  }
}

void crystalMatrix(void)
{
  gemCost = 6;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    ++playerMagic;
    playerTower = playerTower + 3;
    oppTower = oppTower + 1;
    playerGems = playerGems - 6;
  }
}

void gemstoneFlaw(void)
{
  gemCost = 2;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    oppTower = oppTower - 3;
    playerGems = playerGems - 2;
  }
}

void ruby(void)
{
  gemCost = 3;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 5;
    playerGems = playerGems - 3;
  }
}

void gemSpear(void)
{
  gemCost = 4;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    oppTower = oppTower - 5;
    playerGems = playerGems - 4;
  }
}

void powerBurn(void)
{
  gemCost = 3;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower - 5;
    playerMagic = playerMagic + 2;
    playerGems = playerGems - 3;
  }
}

void harmonicVibe(void)
{
  gemCost = 7;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    ++playerMagic;
    playerTower = playerTower + 3;
    playerWall = playerWall + 3;
    playerGems = playerGems - 7;
  }
}

void parity(void)
{
  gemCost = 7;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    if (playerMagic > oppMagic)
    {
      oppMagic = playerMagic;
    }
    else if (oppMagic > playerMagic)
    {
      playerMagic = oppMagic;
    }
    playerGems = playerGems - 7;
  }
}

void emerald(void)
{
  gemCost = 6;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 8;
    playerGems = playerGems - 6;
  }
}

void pearlOfWisdom(void)
{
  gemCost = 9;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 5;
    ++playerMagic;
    playerGems = playerGems - 9;
  }
}

void shatterer(void)
{
  gemCost = 8;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    --playerMagic;
    oppTower = oppTower - 9;
    playerGems = playerGems - 8;
  }
}

void crumblestone(void)
{
  gemCost = 7;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 5;
    oppBricks = oppBricks - 6;
    playerGems = playerGems - 7;
  }
}

void sapphire(void)
{
  gemCost = 10;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 11;
    playerGems = playerGems - 10;
  }
}

void discord(void)
{
  gemCost = 5;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower - 7;
    oppTower = oppTower - 7;
    --playerMagic;
    --oppMagic;
    playerGems = playerGems - 5;
  }
}

void fireRuby(void)
{
  gemCost = 13;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 6;
    oppTower = oppTower - 4;
    playerGems = playerGems - 13;
  }
}

void quarrysHelp(void)
{
  gemCost = 4;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 7;
    playerBricks = playerBricks - 10;
    playerGems = playerGems - 4;
  }
}

void crystalShield(void)
{
  gemCost = 12;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 8;
    playerWall = playerWall + 3;
    playerGems = playerGems - 12;
  }
}

void empathyGem(void)
{
  gemCost = 14;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 8;
    ++playerZoo;
    playerGems = playerGems - 14;
  }
}

void diamond(void)
{
  gemCost = 16;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 15;
    playerGems = playerGems - 16;
  }
}

void sanctuary(void)
{
  gemCost = 15;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 10;
    playerWall = playerWall + 5;
    playerBeasts = playerBeasts + 5;
    playerGems = playerGems - 15;
  }
}

void lavaJewel(void)
{
  gemCost = 17;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 12;
    dealDamage = 6;
    playerAttack();
    playerGems = playerGems - 17;
  }
}

void dragonsEye(void)
{
  gemCost = 21;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 20;
    playerGems = playerGems - 21;
  }
}

void crystalize(void)
{
  gemCost = 8;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 11;
    playerWall = playerWall - 6;
    playerGems = playerGems - 8;
  }
}

void bagOfBaubles(void)
{
  gemCost = 0;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    if (playerTower < oppTower)
    {
      playerTower = playerTower + 2;
    }
    else
    {
      ++playerTower;
    }
    playerGems = playerGems - 0;
  }
}

void rainbow(void)
{
  gemCost = 0;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    ++playerTower;
    ++oppTower;
    playerGems = playerGems + 3;
    playerGems = playerGems - 0;
  }
}

void apprentice(void)
{
  gemCost = 5;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 4;
    playerBeasts = playerBeasts - 3;
    oppTower = oppTower - 2;
    playerGems = playerGems - 5;
  }
}

void lightningShard(void)
{
  gemCost = 11;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    if (playerTower > oppWall)
    {
      oppTower = oppTower - 8;
    }
    else
    {
      dealDamage = 8;
      playerAttack();
    }
    playerGems = playerGems - 11;
  }
}

void phaseJewel(void)
{
  gemCost = 18;
  if (gemCost > playerGems)
  {
    notEnoughGems();
    return;
  }
  else
  {
    playerTower = playerTower + 13;
    playerBeasts = playerBeasts + 6;
    playerBricks = playerBricks + 6;
    playerGems = playerGems - 18;
  }
}

// GREEN CARDS

void madCowDisease(void)
{
  beastCost = 0;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    playerBeasts = playerBeasts - 6;
    oppBeasts = oppBeasts - 6;
    playerBeasts = playerBeasts - 0;
  }
}

void faerie(void)
{
  beastCost = 1;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 2;
    playerAttack();
    // dorobic play again
    playerBeasts = playerBeasts - 1;
  }
}

void moodyGoblins(void)
{
  beastCost = 1;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 4;
    playerAttack();
    playerGems = playerGems - 3;
    playerBeasts = playerBeasts - 1;
  }
}

void minotaur(void)
{
  beastCost = 3;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    ++playerZoo;
    playerBeasts = playerBeasts - 3;
  }
}

void elvenScout(void)
{
  beastCost = 2;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    // DRAW DISCARD PLAY AGAIN
    playerBeasts = playerBeasts - 2;
  }
}

void goblinMob(void)
{
  beastCost = 3;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 6;
    playerAttack();
    dealDamage = 3;
    oppAttack();
    playerBeasts = playerBeasts - 3;
  }
}

void goblinArchers(void)
{
  beastCost = 4;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    oppTower = oppTower - 3;
    dealDamage = 1;
    oppAttack();
    playerBeasts = playerBeasts - 4;
  }
}

void shadowFaerie(void)
{
  beastCost = 6;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    oppTower = oppTower - 2;
    // PLAY AGAIN
    playerBeasts = playerBeasts - 6;
  }
}

void orc(void)
{
  beastCost = 3;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 5;
    playerAttack();
    playerBeasts = playerBeasts - 3;
  }
}

void dwarves(void)
{
  beastCost = 5;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 4;
    playerAttack();
    playerWall = playerWall + 3;
    playerBeasts = playerBeasts - 5;
  }
}

void littleSnakes(void)
{
  beastCost = 6;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    oppTower = oppTower - 4;
    playerBeasts = playerBeasts - 6;
  }
}

void trollTrainer(void)
{
  beastCost = 7;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    playerZoo = playerZoo + 2;
    playerBeasts = playerBeasts - 7;
  }
}

void towerGremlin(void)
{
  beastCost = 8;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 2;
    playerAttack();
    playerWall = playerWall + 4;
    playerTower = playerTower + 2;
    playerBeasts = playerBeasts - 8;
  }
}

void fullMoon(void)
{
  beastCost = 0;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    ++playerZoo;
    ++oppZoo;
    playerBeasts = playerBeasts + 3;
    playerBeasts = playerBeasts - 0;
  }
}

void slasher(void)
{
  beastCost = 5;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 6;
    playerAttack();
    playerBeasts = playerBeasts - 5;
  }
}

void ogre(void)
{
  beastCost = 6;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 7;
    playerAttack();
    playerBeasts = playerBeasts - 6;
  }
}

void rabidSheep(void)
{
  beastCost = 6;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 6;
    playerAttack();
    oppBeasts = oppBeasts - 3;
    playerBeasts = playerBeasts - 6;
  }
}

void imp(void)
{
  beastCost = 5;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 6;
    playerAttack();
    playerBricks = playerBricks - 5;
    playerBeasts = playerBeasts - 5;
    playerGems = playerGems - 5;
    oppBricks = oppBricks - 5;
    oppBeasts = oppBeasts - 5;
    oppGems = oppGems - 5;

    playerBeasts = playerBeasts - 5;
  }
}
void spizzer(void)
{
  beastCost = 8;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    if (oppWall == 0)
    {
      dealDamage = 10;
      playerAttack();
    }
    else
    {
      dealDamage = 6;
      playerAttack();
    }
    playerBeasts = playerBeasts - 8;
  }
}

void werewolf(void)
{
  beastCost = 9;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    dealDamage = 9;
    playerAttack();
    playerBeasts = playerBeasts - 9;
  }
}

void corrosionCloud(void)
{
  beastCost = 11;
  if (beastCost > playerBeasts)
  {
    notEnoughBeasts();
    return;
  }
  else
  {
    if (oppWall > 0)
    {
      dealDamage = 10;
      playerAttack();
    }
    else
    {
      dealDamage = 7;
      playerAttack();
    }
    playerBeasts = playerBeasts - 11;
  }
}

void unicorn(void){
   beastCost = 9;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
    if(playerMagic > oppMagic){
      dealDamage = 12;
      playerAttack();
    }
    else{
      dealDamage = 8;
      playerAttack();
    }
  playerBeasts = playerBeasts - 9;
  }
}

void elvenArchers(void){
   beastCost = 10;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
    if (playerWall > oppWall){
      oppTower = oppTower - 6;
    }
    else{
      dealDamage = 6;
      playerAttack();
    }
  playerBeasts = playerBeasts - 10;
  }
}

void succubus(void){
   beastCost = 14;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  oppTower = oppTower - 5;
  oppBeasts = oppBeasts - 8;
  playerBeasts = playerBeasts - 14;
  }
}

void rockStompers(void){
   beastCost = 11;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 8;
  --oppQuarry;
  playerBeasts = playerBeasts - 11;
  }
}

void thief(void){
   beastCost = 12;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  // SYNEK TU TRZA NA SPOKOJNIE POMYSLEC
  playerBeasts = playerBeasts - 12;
  }
}

void stoneGiant(void){
   beastCost = 15;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 10;
  playerAttack();
  playerWall = playerWall + 4;
  playerBeasts = playerBeasts - 15;
  }
}

void vampire(void){
   beastCost = 17;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 10;
  playerAttack();
  oppBeasts = oppBeasts - 5;
  --oppZoo;
  playerBeasts = playerBeasts - 17;
  }
}

void dragon(void){
   beastCost = 25;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 20;
  playerAttack();
  oppGems = oppGems - 10;
  --oppZoo; 
  playerBeasts = playerBeasts - 25;
  }
}

void spearman(void){
   beastCost = 2;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
    if (playerWall > oppWall){
      dealDamage = 3;
      playerAttack();
    }
    else {
      dealDamage = 2;
      playerAttack();
    }
  playerBeasts = playerBeasts - 2;
  }
}

void gnome(void){
   beastCost = 2;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 3;
  playerAttack();
  ++playerGems;
  playerBeasts = playerBeasts - 2;
  }
}

void beserker(void){
   beastCost = 4;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 8;
  playerAttack();
  playerTower = playerTower - 3;
  playerBeasts = playerBeasts - 4;
  }
}

void warlord(void){
   beastCost = 13;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  dealDamage = 13;
  playerAttack();
  playerGems = playerGems - 3;
  playerBeasts = playerBeasts - 13;
  }
}

void pegasusLancer(void){
   beastCost = 18;
  if (beastCost > playerBeasts){
  notEnoughBeasts();
  return;
  }
  else {
  oppTower = oppTower - 12;
  playerBeasts = playerBeasts - 18;
  }
}




void ScreenSetup(void)
{
  blitRect(s_pVpManager->pBack, 0, 0, 320, 128, 0); // black background
  blitRect(s_pVpManager->pBack, 2, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 2, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 2, 68, 32, 32, greenSquare);                                      // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 40, Y_STARTING_POINT - playerTower, 32, playerTower, towercolor); // player tower drawing
  blitRect(s_pVpManager->pBack, 76, Y_STARTING_POINT - playerWall, 32, playerWall, wallcolor);    // player wall drawing
  blitRect(s_pVpManager->pBack, 286, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 286, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 286, 68, 32, 32, greenSquare);                               // // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 250, Y_STARTING_POINT - oppTower, 32, oppTower, towercolor); // PC tower
  blitRect(s_pVpManager->pBack, 214, Y_STARTING_POINT - oppWall, 32, oppWall, wallcolor);    // PC wall
}

void PrintPlayerResources(void)
{
  blitRect(s_pVpManager->pBack, 2, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 2, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 2, 68, 32, 32, greenSquare);                                      // trzy kwadraty na surowce gracza
  blitRect(s_pVpManager->pBack, 40, Y_STARTING_POINT - playerTower, 32, playerTower, towercolor); // wieza gracza
  blitRect(s_pVpManager->pBack, 76, Y_STARTING_POINT - playerWall, 32, playerWall, wallcolor);    // mur gracza
  sprintf(s_pPlayerTower, "%d", playerTower);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerTower);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 44, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf(s_pPlayerWall, "%d", playerWall);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerWall);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 78, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf(s_pPlayerZoo, "%d", playerZoo);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerZoo);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 70, generatorColor, FONT_COOKIE);
  sprintf(s_pPlayerMagic, "%d", playerMagic);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerMagic);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 36, generatorColor, FONT_COOKIE);
  sprintf(s_pPlayerQuarry, "%d", playerQuarry);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerQuarry);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 2, generatorColor, FONT_COOKIE);

  sprintf(s_pPlayerBeasts, "%d", playerBeasts);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerBeasts);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 90, resourceColor, FONT_COOKIE);
  sprintf(s_pPlayerGems, "%d", playerGems);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerGems);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 56, resourceColor, FONT_COOKIE);
  sprintf(s_pPlayerBricks, "%d", playerBricks);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pPlayerBricks);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 22, resourceColor, FONT_COOKIE);
}

void PrintOpponentResources(void)
{
  blitRect(s_pVpManager->pBack, 286, 0, 32, 32, redSquare);
  blitRect(s_pVpManager->pBack, 286, 34, 32, 32, blueSquare);
  blitRect(s_pVpManager->pBack, 286, 68, 32, 32, greenSquare);                               // // squares for resources bgnd temporary
  blitRect(s_pVpManager->pBack, 250, Y_STARTING_POINT - oppTower, 32, oppTower, towercolor); // PC tower
  blitRect(s_pVpManager->pBack, 214, Y_STARTING_POINT - oppWall, 32, oppWall, wallcolor);    // PC wall
  sprintf(s_pOppTower, "%d", oppTower);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppTower);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 252, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf(s_pOppWall, "%d", oppWall);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppWall);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 216, Y_STARTING_POINT - 10, onTowerPrintColor, FONT_COOKIE);
  sprintf(s_pOppZoo, "%d", oppZoo);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppZoo);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 70, generatorColor, FONT_COOKIE);
  sprintf(s_pOppMagic, "%d", oppMagic);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppMagic);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 36, generatorColor, FONT_COOKIE);
  sprintf(s_pOppQuarry, "%d", oppQuarry);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppQuarry);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 2, generatorColor, FONT_COOKIE);

  sprintf(s_pOppBeasts, "%d", oppBeasts);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppBeasts);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 90, resourceColor, FONT_COOKIE);
  sprintf(s_pOppGems, "%d", oppGems);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppGems);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 56, resourceColor, FONT_COOKIE);
  sprintf(s_pOppBricks, "%d", oppBricks);
  fontFillTextBitMap(s_pFont, s_pBmText, s_pOppBricks);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 288, 22, resourceColor, FONT_COOKIE);
}

void DrawStartingHand(void)
{
  for (CardSequenceCount = 0; CardSequenceCount < 6; ++CardSequenceCount)
  {
    cardSlot[CardSequenceCount] = ArrayOfCards[CardSequenceCount]; // put card in a slot
    sprintf(s_pCardinHand, "%d. %s", CardSequenceCount + 1, cardNames[cardSlot[CardSequenceCount]]);
    fontFillTextBitMap(s_pFont, s_pBmText, s_pCardinHand);
    fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 4, 128 + (CardSequenceCount * 10), generatorColor, FONT_COOKIE);
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

  s_pCards = bitmapCreateFromFile("data/arco32.bm", 0); // z pliku tileset.bm, nie lokuj bitmapy w pami�ci FAST

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

  

  ScreenSetup();
  PrintPlayerResources();
  PrintOpponentResources();
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

  if (keyUse(KEY_1))
  {
    blitCopy(s_pCards, 0, cardSlot[0] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY); // narysujmy se karte
    selectedCard = cardSlot[0];
    slotPlayed = 0;
    pleaseConfirm();
  }
  else if (keyUse(KEY_2))
  {
    blitCopy(s_pCards, 0, cardSlot[1] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY);
    selectedCard = cardSlot[1];
    slotPlayed = 1;
    pleaseConfirm();
  }
  else if (keyUse(KEY_3))
  {
    blitCopy(s_pCards, 0, cardSlot[2] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY);
    selectedCard = cardSlot[2];
    slotPlayed = 2;
    pleaseConfirm();
  }
  else if (keyUse(KEY_4))
  {
    blitCopy(s_pCards, 0, cardSlot[3] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY);
    selectedCard = cardSlot[3];
    slotPlayed = 3;
    pleaseConfirm();
  }
  else if (keyUse(KEY_5))
  {
    blitCopy(s_pCards, 0, cardSlot[4] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY);
    selectedCard = cardSlot[4];
    slotPlayed = 4;
    pleaseConfirm();
  }
  else if (keyUse(KEY_6))
  {
    blitCopy(s_pCards, 0, cardSlot[5] * 128, s_pVpManager->pBack, 224, 128, 95, 127, MINTERM_COPY);
    selectedCard = cardSlot[5];
    slotPlayed = 5;
    pleaseConfirm();
  }
  else if (keyUse(KEY_RETURN) && selectedCard != 200)
  {
    switch (selectedCard)
    {
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

    case 10:
      innovations();
      break;

    case 11:
      foundations();
      break;

    case 12:
      tremors();
      break;

    case 13:
      secretRoom();
      break;

    case 14:
      earthquake();
      break;

    case 15:
      bigWall();
      break;

    case 16:
      collapse();
      break;

    case 17:
      newEquipment();
      break;

    case 18:
      stripMine();
      break;

    case 19:
      reinforcedWall();
      break;

    case 20:
      porticulus();
      break;

    case 21:
      crystalRocks();
      break;

    case 22:
      harmonicOre();
      break;

    case 23:
      mondoWall();
      break;

    case 24:
      focusedDesigns();
      break;

    case 25:
      greatWall();
      break;

    case 26:
      rockLauncher();
      break;

    case 27:
      dragonsHeart();
      break;

    case 28:
      forcedLabor();
      break;

    case 29:
      rockGarden();
      break;

    case 30:
      floodWater();
      break;

    case 31:
      barracks();
      break;

    case 32:
      battlements();
      break;

    case 33:
      shift();
      break;

    case 34:
      quartz();
      break;

    case 35:
      smokyQuartz();
      break;

    case 36:
      amethyst();
      break;

    case 37:
      spellWeavers();
      break;

    case 38:
      prism();
      break;

    case 39:
      lodestone();
      break;

    case 40:
      solarFlare();
      break;

    case 41:
      crystalMatrix();
      break;

    case 42:
      gemstoneFlaw();
      break;

    case 43:
      ruby();
      break;

    case 44:
      gemSpear();
      break;

    case 45:
      powerBurn();
      break;

    case 46:
      harmonicVibe();
      break;

    case 47:
      parity();
      break;

    case 48:
      emerald();
      break;

    case 49:
      pearlOfWisdom();
      break;

    case 50:
      shatterer();
      break;

    case 51:
      crumblestone();
      break;

    case 52:
      sapphire();
      break;

    case 53:
      discord();
      break;

    case 54:
      fireRuby();
      break;

    case 55:
      quarrysHelp();
      break;

    case 56:
      crystalShield();
      break;

    case 57:
      empathyGem();
      break;

    case 58:
      diamond();
      break;

    case 59:
      sanctuary();
      break;

    case 60:
      lavaJewel();
      break;

    case 61:
      dragonsEye();
      break;

    case 62:
      crystalize();
      break;

    case 63:
      bagOfBaubles();
      break;

    case 64:
      rainbow();
      break;

    case 65:
      apprentice();
      break;

    case 66:
      lightningShard();
      break;

    case 67:
      phaseJewel();
      break;

    case 68:
      madCowDisease();
      break;

    case 69:
      faerie();
      break;

    case 70:
      moodyGoblins();
      break;

    case 71:
      minotaur();
      break;

    case 72:
      elvenScout();
      break;

    case 73:
      goblinMob();
      break;

    case 74:
      goblinArchers();
      break;

    case 75:
      shadowFaerie();
      break;

    case 76:
      orc();
      break;

    case 77:
      dwarves();
      break;

    case 78:
      littleSnakes();
      break;

    case 79:
      trollTrainer();
      break;

    case 80:
      towerGremlin();
      break;

    case 81:
      fullMoon();
      break;

    case 82:
      slasher();
      break;

    case 83:
      ogre();
      break;

    case 84:
      rabidSheep();
      break;

    case 85:
      imp();
      break;

    case 86:
      spizzer();
      break;

    case 87:
      werewolf();
      break;

    case 88:
      corrosionCloud();
      break;

    case 89:
      unicorn();
      break;

    case 90:
      elvenArchers();
      break;

    case 91:
      succubus();
      break;

    case 92:
      rockStompers();
      break;

    case 93:
      thief();
      break;

    case 94:
      stoneGiant();
      break;

    case 95:
      vampire();
      break;

    case 96:
      dragon();
      break;

    case 97:
      spearman();
      break;

    case 98:
      gnome();
      break;

    case 99:
      beserker();
      break;

    case 100:
      warlord();
      break;

    case 101:
      pegasusLancer();
      break;
    }
    PrintPlayerResources();
    PrintOpponentResources();
    drawNextCard();
  }

  else if (keyUse(KEY_ESCAPE))
  {
    ptplayerStop();

    stateChange(g_pStateMachineGame, &g_sStateMenu);
    return;
  }

  else if (keyUse(KEY_M))
  {
    if (musicPlay == 1)
    {
      musicPlay = 0;
      
    }
    else if (musicPlay == 0)
    {
      musicPlay = 1;
      
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
  bitmapDestroy(s_pCards);
}

// pod funkcjami bo kompilator czyta od g�ry do do�u i musi najpierw napotka� funkcje by wiedzie� �e istniej�
tState g_sStateGame = {
    .cbCreate = stateGameCreate,
    .cbLoop = stateGameLoop,
    .cbDestroy = stateGameDestroy,
    .cbSuspend = 0,
    //.cbResume = gameOnResume,
    .pPrev = 0};
