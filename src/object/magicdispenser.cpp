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

#include "magicdispenser.hpp"

MagicDispenser::MagicDispenser(const ReaderMapping& reader) :
  MagicObject<Dispenser>(reader)
{
}

// TODO: Fix the dispenser's initialization bug.
void
MagicDispenser::active_update(float dt_sec)
{
  if (m_is_solid)
    Dispenser::active_update(dt_sec);
}

void
MagicDispenser::refresh(float dt_sec)
{
  if (m_is_solid)
  {
    m_solid_time += dt_sec;
    m_color.alpha = ALPHA_SOLID;
    Dispenser::set_correct_colgroup();
  }
  else
  {
    m_color.alpha = ALPHA_NONSOLID;
    set_group(COLGROUP_DISABLED);
  }
}
