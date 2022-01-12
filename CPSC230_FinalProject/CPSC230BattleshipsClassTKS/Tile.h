/********************************************************************************************************
// CPSC 230TR			Fall 2021			Final Project - Tile.h
// Twymun Safford
// Last Update Date: 11/15/2021
//
// * Battleships!!!
//
// * C++ Implementation of the Game 'Battleships' for the final project for
// * for CPSC 230.
//
// * This is the header file used to build and populate the board with different 'textures' for different
// *scenarios - for water, for the ships, for a hit, or for a miss
*****************************************************************************************************/
#pragma once
#ifndef TILE_H
#define TILE_H

#include <vector>

enum sea_type { sea, ship, hit, miss };

class Tile
{

private:
	int coord_x;
	int coord_y;
	sea_type type;

public:
	Tile();
	Tile(int coo_x, int coo_y, sea_type type);
	std::vector<int> getCoord();
	void setCoord(int xx, int yy);
	sea_type getType();
	void setType(sea_type type);
	void draw();
};

#endif
