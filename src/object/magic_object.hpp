//  SuperTux
//
//  Copyright (C) 2025 xornamed
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

#include "editor/editor.hpp"
#include "object/camera.hpp"
#include "sprite/sprite.hpp"
#include "supertux/constants.hpp"
#include "supertux/sector.hpp"
#include "util/reader_mapping.hpp"
#include "video/drawing_context.hpp"
#include "video/video_system.hpp"
#include "video/viewport.hpp"

static constexpr float MIN_INTENSITY = 0.8f;
static constexpr float ALPHA_SOLID = 0.7f;
static constexpr float ALPHA_NONSOLID = 0.3f;
static constexpr float MIN_SOLIDTIME = 1.0f;
static constexpr float SWITCH_DELAY = 0.0f; /**< seconds to wait for stable conditions until switching solidity */

template <typename Base>
class MagicObject : public Base
{
public:
  template <typename... Args>
  MagicObject(const ReaderMapping& reader, Args&&... args)
    : Base(reader, std::forward<Args>(args)...),
      m_is_solid(false),
      m_solid_time(0.f),
      m_color(),
      m_light(std::make_shared<Color>(0.0f, 0.0f, 0.0f)),
      m_center(0.0f, 0.0f),
      m_trigger_red(0.f),
      m_trigger_green(0.f),
      m_trigger_blue(0.f),
      m_switch_delay(0.f),
      m_solid_box(),
      m_black(false)
  {
    std::vector<float> v_color;
    if (reader.get("color", v_color))
      m_color = Color(v_color);
    else
      m_color = Color(0.f, 0.f, 0.f);

    if (!Editor::is_active())
    {
      // All alpha to make the sprite still visible
      m_color.alpha = ALPHA_SOLID;

      // Set trigger
      set_trigger_color();
    }

    m_center = m_col.m_bbox.get_middle();
    m_solid_box = get_bbox().grown(-SHIFT_DELTA);
  }

  virtual void
  update(float dt_sec) override
  {
    m_center = m_col.m_bbox.get_middle();
    m_solid_box = get_bbox().grown(-SHIFT_DELTA);

    // Check if center of this block is on screen.
    // Don't update if not, because there is no light off screen.
    const float screen_left = Sector::get().get_camera().get_translation().x;
    const float screen_top = Sector::get().get_camera().get_translation().y;
    const float screen_right = screen_left + static_cast<float>(SCREEN_WIDTH);
    const float screen_bottom = screen_top + static_cast<float>(SCREEN_HEIGHT);

    if ((m_center.x > screen_right) || (m_center.y > screen_bottom) ||
       (m_center.x < screen_left) || (m_center.y < screen_top))
    {
      m_switch_delay = SWITCH_DELAY;
      return;
    }

    bool lighting_ok;
    if (m_black)
    {
      lighting_ok = (m_light->red >= m_trigger_red     ||
                     m_light->green >= m_trigger_green ||
                     m_light->blue >= m_trigger_blue);
    }
    else
    {
      lighting_ok = (m_light->red >= m_trigger_red     &&
                     m_light->green >= m_trigger_green &&
                     m_light->blue >= m_trigger_blue);
    }

    // Overrule lighting_ok if switch_delay has not yet passed
    if (lighting_ok == m_is_solid)
    {
      m_switch_delay = SWITCH_DELAY;
    }
    else
    {
      if (m_switch_delay > 0.f)
      {
        lighting_ok = m_is_solid;
        m_switch_delay -= dt_sec;
      }
    }

    if (lighting_ok)
    {
      // Lighting suggests going solid
      if (!m_is_solid)
      {
        if (can_be_solid())
        {
          m_is_solid = true;
          m_solid_time = 0.f;
          m_switch_delay = SWITCH_DELAY;
        }
      }
    }
    else
    {
      // Lighting suggests going non-solid
      if (m_solid_time >= MIN_SOLIDTIME)
        m_is_solid = false;
    }

    Base::update(dt_sec);

    refresh(dt_sec);

    if (m_sprite)
      m_sprite->set_color(m_color);
  }

  virtual ObjectSettings
  get_settings() override
  {
    ObjectSettings result = Base::get_settings();

    result.add_rgb(_("Color"), &m_color, "color", Color::BLACK);

    result.reorder({ "color", "x", "y" });

    return result;
  }

  virtual void
  after_editor_set() override
  {
    Base::after_editor_set();
    set_trigger_color();

    if (m_sprite)
      m_sprite->set_color(m_color);
  }

protected:
  bool m_is_solid;
  float m_solid_time;
  Color m_color;
  std::shared_ptr<Color> m_light;
  Vector m_center;

  virtual void refresh(float dt_sec) = 0;

  inline virtual bool
  can_be_solid() const
  {
    return Sector::get().is_free_of_movingstatics(m_solid_box, this);
  }

  virtual void
  draw(DrawingContext& context) override
  {
    context.light().get_pixel(m_center, m_light);
    Base::draw(context);
  }

  void
  set_trigger_color()
  {
    if (m_color.red == 0.f && m_color.green == 0.f && m_color.blue == 0.f)
    {
      // Is it black?
      m_black = true;
      m_trigger_red = m_trigger_green = m_trigger_blue = MIN_INTENSITY;
    }
    else
    {
      m_black = false;
      m_trigger_red = m_color.red;
      m_trigger_green = m_color.green;
      m_trigger_blue = m_color.blue;
    }
  }

private:
  float m_trigger_red;
  float m_trigger_green;
  float m_trigger_blue;
  float m_switch_delay; /**< seconds until switching solidity */
  Rectf m_solid_box;
  bool m_black;

private:
  MagicObject(const MagicObject&) = delete;
  MagicObject& operator=(const MagicObject&) = delete;
};
