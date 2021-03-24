#include "Grid.h"

Grid::Grid(Game* game)
	:Actor(game), mSelectedTile(nullptr)
{
	// 7 rows, 16 columns
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}

	// Create tiles
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
		}
	}
}

void Grid::ProcessClick(int x, int y)
{
}

bool Grid::FindPath(Tile* start, Tile* goal)
{
	return false;
}

void Grid::BuildTower()
{
}

Tile* Grid::GetStartTile()
{
	return nullptr;
}

Tile* Grid::GetEndTile()
{
	return nullptr;
}

void Grid::UpdateActor(float deltaTime)
{
}

void Grid::SelecTile(size_t row, size_t col)
{
}

void Grid::UpdatePathTiles(Tile* start)
{
}