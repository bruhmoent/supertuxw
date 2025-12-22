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

#include "magicspike.hpp"

#include "badguy/badguy.hpp"
#include "object/player.hpp"

MagicSpike::MagicSpike(const ReaderMapping& reader) :
  MagicBlock(reader, "images/objects/magicspike/magicspike.sprite")
{
  set_group(COLGROUP_TOUCHABLE);
}

void
MagicSpike::refresh(float dt_sec)
{
  if (m_is_solid)
  {
    m_solid_time += dt_sec;
    m_color.alpha = ALPHA_SOLID;
    set_action("solid");
    set_group(COLGROUP_TOUCHABLE);
  }
  else
  {
    m_color.alpha = ALPHA_NONSOLID;
    set_action("default");
    set_group(COLGROUP_DISABLED);
  }

  if (m_sprite)
    m_sprite->set_color(m_color);
}

HitResponse
MagicSpike::collision(MovingObject& other, const CollisionHit&)
{
  if (!m_is_solid) return ABORT_MOVE;

  auto player = dynamic_cast<Player*>(&other);
  if (player)
  {
    if (player->is_invincible())
      return ABORT_MOVE;

    player->kill(false);
  }

  auto badguy = dynamic_cast<BadGuy*>(&other);
  if (badguy)
    badguy->kill_fall();

  return FORCE_MOVE;
}

void
MagicSpike::draw(DrawingContext& context)
{
  context.light().get_pixel(m_center, m_light);

  MovingSprite::draw(context);
}
