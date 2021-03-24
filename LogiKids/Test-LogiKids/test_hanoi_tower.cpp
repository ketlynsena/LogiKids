#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"


Hanoi_Tower* torre = new Hanoi_Tower();

TEST(TestHanoiTower, TestInit)
{
	EXPECT_TRUE(torre);
}

TEST(TestHanoiTower, TestGameWon)
{
	bool game = torre->gameWon();
	EXPECT_EQ(game, false);
}

TEST(TestHanoiTower, TestCheckwin)
{
	for (int i = 0; i < N_LAYERS; i++){
		torre->tower[i][N_TOWERS - 1] = 0;
	}
	bool game = torre->checkWin();
	EXPECT_EQ(game, false);

	for (int i = 0; i < N_LAYERS; i++) {
		torre->tower[i][N_TOWERS - 1] = 1;
	}
	game = torre->checkWin();
	EXPECT_EQ(game, true);
}

TEST(TestHanoiTower, TestGetTowerIndex)
{
	TowerIndex ind = torre->getTowerIndex(torre->cake_layer[0]);
	EXPECT_EQ(ind.n_tower,0);
	EXPECT_EQ(ind.layer, 0);
	torre->cake_layer[0]->setPosition(0, 0);
	ind = torre->getTowerIndex(torre->cake_layer[0]);
	EXPECT_EQ(ind.layer, -1);
	EXPECT_EQ(ind.n_tower, -1);
	torre->cake_layer[0]->resetPosition();

}

TEST(TestHanoiTower, TestHandleEvent)
{

}

TEST(TestHanoiTower, TestLayerBelowIsLarger)
{
	TowerIndex idx;
	idx.layer = 2;
	idx.n_tower = 0;
	EXPECT_TRUE(torre->layerBelowIsLarger(2, idx));
	EXPECT_FALSE(torre->layerBelowIsLarger(5, idx));
}

TEST(TestHanoiTower, TestNoLayerOnTop)
{
	TowerIndex idx;
	idx.layer = 1;
	idx.n_tower = 1;
	EXPECT_TRUE(torre->noLayerOnTop(idx));
	idx.n_tower = 0;
	EXPECT_FALSE(torre->noLayerOnTop(idx));
}

TEST(TestHanoiTower, TestPlaceLayerOnTower)
{
	TowerIndex idx;
	idx.layer = 3;
	idx.n_tower = 1;
	EXPECT_TRUE(torre->placeLayeronTower(torre->cake_layer[3], 3, idx));
	EXPECT_FALSE(torre->placeLayeronTower(torre->cake_layer[2], 5, idx));
}

TEST(TestHanoiTower, TestPrintTower)
{
	torre->printTower();
}

TEST(TestHanoiTower, TestRender)
{
	torre->render();
}

TEST(TestHanoiTower, TestResetLevel)
{
	torre->resetLevel();
	bool game = torre->checkWin();
	EXPECT_EQ(game, false);
}

TEST(TestHanoiTower, TestUpdate)
{
	torre->update();
	bool game = torre->checkWin();
	EXPECT_EQ(game, false);

	for (int i = 0; i < N_LAYERS; i++) {
		torre->tower[i][N_TOWERS - 1] = 1;
	}
	game = torre->checkWin();
	EXPECT_EQ(game, true);
	torre->update();
}

TEST(TestHanoiTower, TestUpdateLayers)
{

}