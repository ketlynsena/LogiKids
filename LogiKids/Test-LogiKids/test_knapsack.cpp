#include "pch.h"
//#include "../LogiKids/game.h"
#include "../LogiKids/knapsack.h"

TEST(TestKnapsack, TestInit)
{
	Knapsack* mochila = new Knapsack();
	EXPECT_TRUE(mochila);
}

TEST(TestKnapsack, TestCreateItem)
{
	Knapsack* mochila = new Knapsack();
	Item item;
	mochila->createItem(&item, "assets/knapsack/caderno.png", 450, 360, 12, 2);

	EXPECT_EQ(item.weight, 12);
	EXPECT_EQ(item.value, 2);
	EXPECT_FALSE(item.inside);
	EXPECT_TRUE(item.itemTexture);
}

TEST(TestKnapsack, TestPackItem)
{
	Knapsack* mochila = new Knapsack();
	Item item;
	mochila->createItem(&item, "assets/knapsack/caderno.png", 450, 360, 12, 2);

	mochila->packItem(&item);

	EXPECT_EQ(mochila->currWeight, 12);
	EXPECT_EQ(mochila->totValue, 2);
	EXPECT_TRUE(item.inside);
}

TEST(TestKnapsack, TestCheckWin)
{
	Knapsack* mochila = new Knapsack();
	EXPECT_FALSE(mochila->checkWin());

	mochila->packItem(&mochila->knapsackItem[REGUA]);
	mochila->packItem(&mochila->knapsackItem[TESOURA]);
	mochila->packItem(&mochila->knapsackItem[LAPIS]);

	EXPECT_TRUE(mochila->checkWin());
}

TEST(TestKnapsack, TestResetLevel)
{
	Knapsack* mochila = new Knapsack();

	mochila->packItem(&mochila->knapsackItem[REGUA]);
	mochila->resetLevel();

	EXPECT_EQ(mochila->currWeight, 0);
	EXPECT_EQ(mochila->totValue, 0);
}

TEST(TestKnapsack, TestUnpackItem)
{
	Knapsack* mochila = new Knapsack();

	mochila->packItem(&mochila->knapsackItem[REGUA]);

	EXPECT_TRUE(mochila->unpackItem(&mochila->knapsackItem[REGUA]));
}