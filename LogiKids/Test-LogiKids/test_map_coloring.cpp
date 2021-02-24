#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"

TEST(TestMapColoring, TestInit)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	EXPECT_TRUE(colorindo_bh);
}

TEST(TestMapColoring, TestAddRegion)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	Regiao regiao;
	SDL_Color color = { 204, 204, 204 };
	colorindo_bh->addRegion(BARREIRO, 420, 392, "assets/map_coloring/barreiro.png");
	regiao = colorindo_bh->getRegion(BARREIRO);

	EXPECT_EQ(regiao.nome, BARREIRO);
	EXPECT_EQ(regiao.cor.r, color.r);
	EXPECT_EQ(regiao.cor.g, color.g);
	EXPECT_EQ(regiao.cor.b, color.b);
	EXPECT_EQ(regiao.nome_cor, BRANCO);
	EXPECT_TRUE(regiao.mapa);
}

TEST(TestMapColoring, TestResetMap) {
	Map_Coloring* colorindo_bh = new Map_Coloring();
	Regiao regiao;
	SDL_Color color = { 204, 204, 204 };
	Nome nome_regioes[N_REGIOES_BH] = {VENDA_NOVA,NORTE,PAMPULHA,NORDESTE,NOROESTE,LESTE,OESTE,CENTRO_SUL,BARREIRO};

	colorindo_bh->setRegionColorByIndex(1, AZUL);
	colorindo_bh->setRegionColorByIndex(0, AZUL);

	colorindo_bh->resetMap();

	for (int i = 0; i < N_REGIOES_BH; i++)
	{
		regiao = colorindo_bh->getRegion(nome_regioes[i]);
		EXPECT_EQ(regiao.nome, nome_regioes[i]);
		EXPECT_EQ(regiao.nome_cor, BRANCO);
		EXPECT_EQ(regiao.cor.r, color.r);
		EXPECT_EQ(regiao.cor.g, color.g);
		EXPECT_EQ(regiao.cor.b, color.b);
	}
}

TEST(TestMapColoring, TestGameNotWon) {
	Map_Coloring* colorindo_bh = new Map_Coloring();
	EXPECT_FALSE(colorindo_bh->gameWon());
}

TEST(TestMapColoring, TestGetColorFromName)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	SDL_Color azul = { 0, 158, 161 };
	SDL_Color roxo = { 96, 62, 149 };
	SDL_Color amarelo = { 250, 195, 43 };
	SDL_Color rosa = { 215, 38, 93 };
	SDL_Color branco = { 204, 204, 204 };

	SDL_Color color;

	color = colorindo_bh->getColorFromName(AZUL);
	EXPECT_EQ(azul.r, color.r);
	EXPECT_EQ(azul.g, color.g);
	EXPECT_EQ(azul.b, color.b);

	color = colorindo_bh->getColorFromName(ROXO);
	EXPECT_EQ(roxo.r, color.r);
	EXPECT_EQ(roxo.g, color.g);
	EXPECT_EQ(roxo.b, color.b);

	color = colorindo_bh->getColorFromName(AMARELO);
	EXPECT_EQ(amarelo.r, color.r);
	EXPECT_EQ(amarelo.g, color.g);
	EXPECT_EQ(amarelo.b, color.b);

	color = colorindo_bh->getColorFromName(ROSA);
	EXPECT_EQ(rosa.r, color.r);
	EXPECT_EQ(rosa.g, color.g);
	EXPECT_EQ(rosa.b, color.b);

	color = colorindo_bh->getColorFromName(BRANCO);
	EXPECT_EQ(branco.r, color.r);
	EXPECT_EQ(branco.g, color.g);
	EXPECT_EQ(branco.b, color.b);
}

TEST(TestMapColoring, TestSetRegionColor)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	Regiao regiao; 
	Nome nome_regioes[N_REGIOES_BH] = { VENDA_NOVA,NORTE,PAMPULHA,NORDESTE,NOROESTE,LESTE,OESTE,CENTRO_SUL,BARREIRO };
	SDL_Color color = colorindo_bh->getCurrentColor();

	regiao = colorindo_bh->getRegion(BARREIRO);
	colorindo_bh->setRegionColor(&regiao);
	regiao = colorindo_bh->getRegion(BARREIRO);

	EXPECT_EQ(regiao.cor.r, color.r);
	EXPECT_EQ(regiao.cor.g, color.g);
	EXPECT_EQ(regiao.cor.b, color.b);
}

TEST(TestMapColoring, TestIsSafe)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();

	EXPECT_TRUE(colorindo_bh->isSafe());

	colorindo_bh->setRegionColorByIndex(1, AZUL);
	colorindo_bh->setRegionColorByIndex(0, AZUL);

	EXPECT_FALSE(colorindo_bh->isSafe());
}

TEST(TestMapColoring, TestSetToCurrentColor)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	SDL_Color color = colorindo_bh->getCurrentColor();
	Regiao regiao;
	regiao = colorindo_bh->getRegion(BARREIRO);
	colorindo_bh->setToCurrentColor(&regiao);

	EXPECT_EQ(regiao.cor.r, color.r);
	EXPECT_EQ(regiao.cor.g, color.g);
	EXPECT_EQ(regiao.cor.b, color.b);
}

TEST(TestMapColoring, TestCurrentColor)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	SDL_Color color = colorindo_bh->getCurrentColor();
	SDL_Color expectedColor = colorindo_bh->getColorFromName(BRANCO);

	EXPECT_EQ(expectedColor.r, color.r);
	EXPECT_EQ(expectedColor.g, color.g);
	EXPECT_EQ(expectedColor.b, color.b);

}

TEST(TestMapColoring, TestCheckWin)
{
	//setRegionColorByIndex(int i, Cor color)
	Map_Coloring* colorindo_bh = new Map_Coloring();
	Nome nome_regioes[N_REGIOES_BH] = { VENDA_NOVA,NORTE,PAMPULHA,NORDESTE,NOROESTE,LESTE,OESTE,CENTRO_SUL,BARREIRO };

	// Barreiro, Noroeste e Norte
	colorindo_bh->setRegionColorByIndex(8, AZUL);
	colorindo_bh->setRegionColorByIndex(4, AZUL);
	colorindo_bh->setRegionColorByIndex(1, AZUL);

	// Pampulha, Oeste e Leste
	colorindo_bh->setRegionColorByIndex(2, ROXO);
	colorindo_bh->setRegionColorByIndex(6, ROXO);
	colorindo_bh->setRegionColorByIndex(5, ROXO);

	EXPECT_FALSE(colorindo_bh->checkWin());

	// Venda Nova, Nordeste e Centro-Sul
	colorindo_bh->setRegionColorByIndex(0, ROSA);
	colorindo_bh->setRegionColorByIndex(3, ROSA);
	colorindo_bh->setRegionColorByIndex(7, ROSA);

	EXPECT_TRUE(colorindo_bh->checkWin());

	colorindo_bh->setRegionColorByIndex(0, AZUL);

	EXPECT_FALSE(colorindo_bh->checkWin());
}

TEST(TestMapColoring, TestSetCurrentColor)
{
	Map_Coloring* colorindo_bh = new Map_Coloring();
	SDL_Color color = colorindo_bh->getColorFromName(BRANCO);
	colorindo_bh->setCurrentColor(BRANCO);
	SDL_Color currColor = colorindo_bh->getCurrentColor();

	EXPECT_EQ(currColor.r, color.r);
	EXPECT_EQ(currColor.g, color.g);
	EXPECT_EQ(currColor.b, color.b);
}