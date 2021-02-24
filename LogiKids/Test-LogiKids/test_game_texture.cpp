#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"

TEST(TestGameTexture, TestInitPosition) {

	GameTexture* GameTest;
	SDL_Point originalPosition;
	int xpos = 0;
	int ypos = 0;

	GameTest = new GameTexture("a", xpos, ypos, false, false);
	originalPosition = GameTest->getOriginalPosition();
	EXPECT_EQ(xpos, originalPosition.x);
	EXPECT_EQ(ypos, originalPosition.y);

}

TEST(TestGameTexture, TestUpdatePosition) {

	GameTexture* GameTest;
	SDL_Point currentPosition;
	int xpos = 2;
	int ypos = 2;

	GameTest = new GameTexture("a", 0, 0, false, false);
	GameTest->setPosition(xpos, ypos);
	currentPosition = GameTest->getCurrentPosition();
	EXPECT_EQ(xpos, currentPosition.x);
	EXPECT_EQ(ypos, currentPosition.y);

}

TEST(TestGameTexture, TestResetPosition) {

	GameTexture* GameTest;
	SDL_Point currentPosition;
	int xpos = 2;
	int ypos = 2;

	GameTest = new GameTexture("a", xpos, ypos, false, false);
	GameTest->setPosition(0, 0);
	GameTest->resetPosition();
	currentPosition = GameTest->getCurrentPosition();
	EXPECT_EQ(xpos, currentPosition.x);
	EXPECT_EQ(ypos, currentPosition.y);

}

TEST(TestGameTexture, TestLoadTexture) {

	GameTexture* GameTest;
	SDL_Texture* Texture;

	GameTest = new GameTexture("assets/cursors/seta.png", 0, 0, false, false);
	Texture = GameTest->loadTexture("assets/cursors/seta.png");
	int w = GameTest->getWidth();
	printf("Width: %d\n", w);

	EXPECT_EQ(true, true);

}

TEST(TestGameTexture, TestIsNotGrabbed) {
	GameTexture* texture = new GameTexture("assets/overlay.png", 0, 0, false, true);
	bool isGrabbed;

	isGrabbed = texture->isGrabbed();

	EXPECT_FALSE(isGrabbed);
}

TEST(TestGameTexture, TestNotDropped)
{
	GameTexture* texture = new GameTexture("assets/overlay.png", 0, 0, false, true);
	bool dropped;

	dropped = texture->dropped();

	EXPECT_FALSE(dropped);
}

TEST(TestGameTexture, TestNotGrabbed)
{
	GameTexture* texture = new GameTexture("assets/overlay.png", 0, 0, false, true);
	bool grabbed;

	grabbed = texture->grabbed();

	EXPECT_FALSE(grabbed);
}

TEST(TestGameTexture, TestSetGrabPosition)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	SDL_Point grabPos, expectedGrabPos;
	grabPos.x = 10;
	grabPos.y = 20;

	texture->setGrabPosition(grabPos);
	expectedGrabPos = texture->getGrabPosition();

	EXPECT_EQ(grabPos.x, expectedGrabPos.x);
	EXPECT_EQ(grabPos.y, expectedGrabPos.y);

}

TEST(TestGameTexture, TestNotPressed)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	EXPECT_FALSE(texture->isPressed());
}

TEST(TestGameTexture, TestNotWithinBoundaries)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	EXPECT_FALSE(texture->isWithinBoundaries());
}

TEST(TestGameTexture, TestGetPixelColor)
{
	GameTexture* texture = new GameTexture("assets/tabuleiro.png", 0, 0, false, true);
	SDL_Color expectedColor = {249, 249, 249, 255};
	SDL_Color color;

	color = texture->getPixelColor(1, 1);

	EXPECT_EQ(color.r, expectedColor.r);
	EXPECT_EQ(color.g, expectedColor.g);
	EXPECT_EQ(color.b, expectedColor.b);
	EXPECT_EQ(color.a, expectedColor.a);
	
}

TEST(TestGameTexture, TestGetCurrentPosition) {
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	texture->setPosition(10, 20);

	SDL_Point currPos;
	currPos = texture->getCurrentPosition();

	EXPECT_EQ(currPos.x, 10);
	EXPECT_EQ(currPos.y, 20);
}

TEST(TestGameTexture, TestGetGrabPosition) {
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	SDL_Point grabPos;
	grabPos.x = 10;
	grabPos.y = 20;
	texture->setGrabPosition(grabPos);

	SDL_Point currPos;
	currPos = texture->getGrabPosition();

	EXPECT_EQ(currPos.x, 10);
	EXPECT_EQ(currPos.y, 20);
}

TEST(TestGameTexture, TestGrabbed)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	texture->setGrab(true);
	texture->setDropState(true);
	bool isGrabbed;

	isGrabbed = texture->grabbed();

	EXPECT_TRUE(isGrabbed);
}

TEST(TestGameTexture, TestDropped)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	texture->setGrab(false);
	texture->setGrabState(true);
	bool isDropped;

	isDropped = texture->dropped();

	EXPECT_TRUE(isDropped);
}

TEST(TestGameTexture, TestGetMouseState)
{
	GameTexture* texture = new GameTexture("assets/rainha.png", 0, 0, false, true);
	SDL_MouseButtonEvent mouseEvent;
	mouseEvent.type = SDL_MOUSEBUTTONDOWN;
	mouseEvent.x = 10;
	mouseEvent.y = 20;
	SDL_Point mouseState;

	mouseState = texture->getMouseState(&mouseEvent);

	EXPECT_EQ(10, mouseState.x);
	EXPECT_EQ(20, mouseState.y);
}

TEST(TestGameTexture, TestSetColor)
{
	GameTexture* texture = new GameTexture("assets/map_coloring/venda_nova.png", 0, 0, false, false);
	SDL_Color transparente = { 0, 0, 0, 0 };
	SDL_Color currColor;

	texture->resetColor();
	texture->setColor(transparente);
	currColor = texture->getPixelColor(0, 0);

	EXPECT_EQ(currColor.r, transparente.r);
	EXPECT_EQ(currColor.g, transparente.g);
	EXPECT_EQ(currColor.b, transparente.b);
	EXPECT_EQ(currColor.a, transparente.a);
}

TEST(TestGameTexture, TestResetColor)
{
	GameTexture* texture = new GameTexture("assets/map_coloring/venda_nova.png", 0, 0, false, false);
	SDL_Color currColor;
	SDL_Color branco = { 251, 251, 251, 251 };

	texture->setColor(branco);
	texture->resetColor();
	currColor = texture->getPixelColor(0, 0);

	EXPECT_EQ(currColor.r, 0);
	EXPECT_EQ(currColor.g, 0);
	EXPECT_EQ(currColor.b, 0);
	EXPECT_EQ(currColor.a, 0);
}

TEST(TestGameTexture, TestSpriteNotPressed)
{
	GameTexture* texture = new GameTexture("assets/map_coloring/venda_nova.png", 0, 0, false, false);
	SDL_Event event;

	EXPECT_FALSE(texture->handleEvent(&event));
}