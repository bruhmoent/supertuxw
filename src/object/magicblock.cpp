//  SuperTux - MagicBlock
//
//  Magic Blocks are tile-like game objects that are sensitive to
//  lighting conditions. They are rendered in a color and
//  will only be solid as long as light of the same color shines
//  on the block.
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

#include "object/magicblock.hpp"

#include "supertux/flip_level_transformer.hpp"

MagicBlock::MagicBlock(const ReaderMapping& reader) :
  MagicObject(reader, "images/objects/magicblock/magicblock.sprite")
{
  set_group(COLGROUP_STATIC);
}

void
MagicBlock::refresh(float dt_sec)
{
  if (m_is_solid)
  {
    m_solid_time += dt_sec;
    m_color.alpha = ALPHA_SOLID;
    set_action("solid");
    set_group(COLGROUP_STATIC);
  }
  else
  {
    m_color.alpha = ALPHA_NONSOLID;
    set_action("default");
    set_group(COLGROUP_DISABLED);
  }
}

void
MagicBlock::draw(DrawingContext& context)
{
  MagicObject::draw(context);
  context.color().draw_filled_rect(m_col.m_bbox, m_color, m_layer);
}

bool
MagicBlock::collides(MovingObject& /*other*/, const CollisionHit& /*hit*/) const
{
  return m_is_solid;
}

HitResponse
MagicBlock::collision(MovingObject& /*other*/, const CollisionHit& /*hit*/)
{
  return FORCE_MOVE;
}

void
MagicBlock::on_flip(float height)
{
  MovingSprite::on_flip(height);
  FlipLevelTransformer::transform_flip(m_flip);
  m_center = m_col.m_bbox.get_middle();
}
