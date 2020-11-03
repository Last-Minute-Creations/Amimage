#include <ace/managers/viewport/simplebuffer.h>
#include <ace/managers/joy.h>
#include <ace/managers/key.h>
#include <ace/managers/system.h>
#include <ace/managers/game.h>
#include <ace/utils/palette.h>
#include <ace/utils/font.h>
#include <stdio.h>
#include <ace/managers/state.h>
#include <ace/managers/rand.h>

static tView *s_pView;
static tVPort *s_pVp;
static tSimpleBufferManager *s_pVpManager;

static tFont *s_pFont;
static tTextBitMap *s_pBmText;

extern tState g_sStateGame;
extern tStateManager *g_pStateMachineGame;

char s_pText[60];

UBYTE losowo;

#define NUMBER_OF_CARDS_IN_DECK 102
int ArrayOfCards[NUMBER_OF_CARDS_IN_DECK];


void deckShuffle(void)
{
  for (UBYTE i = 0; i < NUMBER_OF_CARDS_IN_DECK; ++i)
  {
    ArrayOfCards[i] = i;
  }
  for (UBYTE i = 0; i < NUMBER_OF_CARDS_IN_DECK - 1; ++i)
  {
    size_t j = i + uwRandMinMax(0, NUMBER_OF_CARDS_IN_DECK) / (NUMBER_OF_CARDS_IN_DECK / (NUMBER_OF_CARDS_IN_DECK - i) + 1);
    int t = ArrayOfCards[j];
    ArrayOfCards[j] = ArrayOfCards[i];
    ArrayOfCards[i] = t;
  }
}


void stateMenuCreate(void){
	s_pView = viewCreate(0,
		TAG_VIEW_COPLIST_MODE, COPPER_MODE_BLOCK,
		TAG_VIEW_GLOBAL_CLUT, 1,
		TAG_END
	);
	s_pVp = vPortCreate(0,
		TAG_VPORT_VIEW, s_pView,
		TAG_VPORT_BPP, 5,
		TAG_END
	);

	
	paletteLoad("data/amimage.plt", s_pVp->pPalette, 32);

	s_pVpManager = simpleBufferCreate(0,
			TAG_SIMPLEBUFFER_VPORT, s_pVp,
			TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_CLEAR | BMF_INTERLEAVED,
			TAG_SIMPLEBUFFER_IS_DBLBUF, 0,
			TAG_END
	);

	s_pFont = fontCreate("data/topaz.fnt");
  s_pBmText = fontCreateTextBitMap(300, s_pFont->uwHeight);


	//bitmapLoadFromFile(s_pVpManager->pBack, "data/title.bm", 0, 0);
	sprintf(s_pText, "Menu, shuflling. Press RETURN to start.");
  fontFillTextBitMap(s_pFont, s_pBmText, s_pText);
  fontDrawTextBitMap(s_pVpManager->pBack, s_pBmText, 2, 2, 2, FONT_COOKIE);

	randInit(461);
	joyOpen();
	keyCreate();
	systemUnuse();
	viewLoad(s_pView);


}

void stateMenuLoop(void){
	volatile UWORD uwTmp = uwRandMinMax(0, NUMBER_OF_CARDS_IN_DECK);
	uwRandMinMax(0, NUMBER_OF_CARDS_IN_DECK);
	
	joyProcess();
	keyProcess();

	if(keyUse(KEY_ESCAPE)) {
		gameExit();
		return;
	}

	if(joyUse(JOY1_FIRE) || keyUse(KEY_RETURN)) {
		deckShuffle();
		stateChange(g_pStateMachineGame, &g_sStateGame);
		return;
	}
	logWrite("Current random: %hu\n", uwTmp);
	
	viewProcessManagers(s_pView);
	copProcessBlocks();
	vPortWaitForEnd(s_pVp);
}

void stateMenuDestroy(void){
	systemUse();
	viewDestroy(s_pView);
	joyClose();
	keyDestroy();
}


tState g_sStateMenu = {
  .cbCreate = stateMenuCreate,
  .cbLoop = stateMenuLoop,
  .cbDestroy = stateMenuDestroy,
  .cbSuspend = 0,
  .cbResume = 0,
  .pPrev = 0
};
