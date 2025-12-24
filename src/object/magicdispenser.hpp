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

#include "badguy/dispenser.hpp"
#include "object/magic_object.hpp"

class MagicDispenser final : public MagicObject<Dispenser>
{
public:
  MagicDispenser(const ReaderMapping& reader);

  void active_update(float dt_sec) override;
  static std::string class_name() { return "magicdispenser"; }
  std::string get_class_name() const override { return class_name(); }
  static std::string display_name() { return _("Magic Dispenser"); }
  std::string get_display_name() const override { return display_name(); }
  GameObjectClasses get_class_types() const override { return MovingSprite::get_class_types().add(typeid(MagicDispenser)); }

private:
  void refresh(float dt_sec) override;

private:
  MagicDispenser(const MagicDispenser&) = delete;
  MagicDispenser& operator=(const MagicDispenser&) = delete;
};
