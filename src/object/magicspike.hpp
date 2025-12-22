//  SuperTux
//
//  Copyright (C) 2025 xornamed
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

#include "object/magicblock.hpp"

class MagicSpike final : public MagicBlock
{
public:
  MagicSpike(const ReaderMapping& reader);
  static std::string class_name() { return "magicspike"; }
  std::string get_class_name() const override { return class_name(); }
  static std::string display_name() { return _("Magic Spike"); }
  std::string get_display_name() const override { return display_name(); }

  inline GameObjectClasses get_class_types() const override
  {
    return MagicBlock::get_class_types().add(typeid(MagicSpike));
  }

  HitResponse collision(MovingObject& other, const CollisionHit& hit) override;
  void draw(DrawingContext& context) override;

private:
  void refresh(float dt_sec);
  inline bool can_be_solid() const override
  {
    return true;
  }

private:
  MagicSpike(const MagicSpike&) = delete;
  MagicSpike& operator=(const MagicSpike&) = delete;
};
