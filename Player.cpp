// Copyright 2020 Chou, Dechathaweewat, Hollis-London

#include "Player.h"

#include <sstream>

Player::Player() { this->mosaic = std::make_shared<Mosaic>(); };

Player::~Player(){

};

Player::Player(const std::string name, int points, MosaicPtr&& mosaic)
    : name(name), points(points), mosaic(std::move(mosaic)){};

Player::Player(const std::string name, int points)
    : name(name), points(points) {
  this->mosaic = std::make_shared<Mosaic>();
}

Player::Player(Player&& other)
    : name(other.name), points(other.points), mosaic(std::move(other.mosaic)) {}

std::string Player::GetName() { return this->name; }

void Player::SetPoints(int points) { this->points = points; }

int Player::GetPoints() { return this->points; }

MosaicPtr Player::GetMosaic() { return this->mosaic; }

std::string Player::ToString() {
  std::stringstream ss;
  ss << "Mosaic for Player " << this->name << " - points: " << this->points
     << std::endl;
  ss << this->mosaic->ToString() << std::endl;
  return ss.str();
};