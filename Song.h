#pragma once
#include <iostream>
#include <vector>
#include <string>

enum class Genre
{
	ROCK,
	JAZZ,
	POP,
	CLASSICAL,
	ELECTRONIC,
	COUNT
};

static const std::vector<std::string> GENRES_NAMES = {
	"ROCK",
	"JAZZ",
	"POP",
	"CLASSICAL",
	"ELECTRONIC"
};

struct Song
{
	int m_id;
	std::string m_name;
	int m_album;
	Genre m_genre;

	friend std::ostream& operator << (std::ostream& p_out, const Song& song);
};

std::ostream& operator << (std::ostream& p_out, const Song& song);