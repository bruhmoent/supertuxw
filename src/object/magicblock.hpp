//  SuperTux - MagicBlock
//
//  Magic Blocks are tile-like game objects that are sensitive to
//  lighting conditions. They are rendered in a color and
//  will only be solid as long as light of the same color shines
//  on the block. The black block becomes solid, if any kind of
//  light is above MIN_INTENSITY.
//
//  Copyright (C) 2006 Wolfgang Becker <uafr@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "object/moving_sprite.hpp"
#include "object/magic_object.hpp"

class MagicBlock final : public MagicObject<MovingSprite>
{
public:
  MagicBlock(const ReaderMapping& reader);

  bool collides(MovingObject& other, const CollisionHit& hit) const override;
  HitResponse collision(MovingObject& other, const CollisionHit& hit) override;
  void draw(DrawingContext& context) override;
  static std::string class_name() { return "magicblock"; }
  std::string get_class_name() const override { return class_name(); }
  static std::string display_name() { return _("Magic Tile"); }
  std::string get_display_name() const override { return display_name(); }
  GameObjectClasses get_class_types() const override { return MovingSprite::get_class_types().add(typeid(MagicBlock)); }

  void on_flip(float height) override;

private:
  void refresh(float dt_sec) override;

private:
  MagicBlock(const MagicBlock&) = delete;
  MagicBlock& operator=(const MagicBlock&) = delete;
};
