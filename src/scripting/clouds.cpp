//  SuperTux
//  Copyright (C) 2020 A. Semphris <semphris@protonmail.com>
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

#include "object/cloud_particle_system.hpp"
#include "scripting/clouds.hpp"

namespace scripting {

  void Clouds::set_enabled(bool enable)
  {
    SCRIPT_GUARD_VOID;
    object.set_enabled(enable);
  }

  bool Clouds::get_enabled() const
  {
    SCRIPT_GUARD_DEFAULT;
    return object.get_enabled();
  }

  void Clouds::fade_speed(float speed, float time)
  {
    SCRIPT_GUARD_VOID;
    object.fade_speed(speed, 0.f, time);
  }

  void Clouds::fade_speed(float speed_x, float speed_y, float time)
  {
    SCRIPT_GUARD_VOID;
    object.fade_speed(speed_x, speed_y, time);
  }

  void Clouds::fade_amount(int amount, float time, float time_between)
  {
    SCRIPT_GUARD_VOID;
    object.fade_amount(amount, time, time_between);
  }

  void Clouds::set_amount(int amount, float time)
  {
    SCRIPT_GUARD_VOID;
    object.fade_amount(amount, time);
  }

  void Clouds::set_x_speed(float speed)
  {
    SCRIPT_GUARD_VOID;
    object.set_x_speed(speed);
  }

  float Clouds::get_x_speed() const
  {
    SCRIPT_GUARD_DEFAULT;
    return object.get_x_speed();
  }

  void Clouds::set_y_speed(float speed)
  {
    SCRIPT_GUARD_VOID;
    object.set_y_speed(speed);
  }

  float Clouds::get_y_speed() const
  {
    SCRIPT_GUARD_DEFAULT;
    return object.get_y_speed();
  }

} // namespace scripting

/* EOF */
