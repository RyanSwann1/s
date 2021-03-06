#pragma once

#include "../Entity.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"

struct TileSheet
{
	TileSheet(const std::string& name, int tileSize, int columns);

	sf::IntRect getTileLocation(int tileID) const;

	const int m_tileSize;
	const int m_columns;
	sf::Texture m_texture;
};

class TileLayer
{
public:
	TileLayer(const std::vector<std::vector<int>>& tileLayer, const std::string& tileSheetName);

	const std::vector<std::vector<int>>& getTileLayer() const;
	const std::string& getName() const;
	void draw(const TileSheet& tileSheet, sf::RenderWindow& window, sf::Vector2i levelSize) const;

private:
	const std::string m_name;
	const std::vector<std::vector<int>> m_tileLayer;
};

class Level
{
public:
	Level(sf::Vector2i levelSize, std::vector<TileLayer> tileLayers, std::unordered_map<std::string, TileSheet> tileSheets,
		std::vector<sf::FloatRect>&& collisionLayer, std::vector<sf::Vector2f> entityStartingPositions);

	sf::Vector2i getSize() const;
	const TileLayer& getTileLayer() const;
	const std::vector<sf::FloatRect>& getCollisionLayer() const;
	const TileSheet& getTileSheet(const std::string& name) const;

	void update();
	void draw(sf::RenderWindow& window) const;

private:
	std::vector<Entity> m_entities;
	const sf::Vector2i m_levelSize;
	const std::vector<TileLayer> m_tileLayers;
	const std::unordered_map<std::string, TileSheet> m_tileSheets;
	const std::vector<sf::FloatRect> m_collisionLayer;
};