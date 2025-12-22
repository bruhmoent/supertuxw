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
