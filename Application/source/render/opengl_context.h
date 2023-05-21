#pragma once

#include "render_base.h"

class OpenGL_Context : public RenderContext
{
public:

  bool init(IWindow* window) override;

  void pre_render() override;

  void post_render() override;

  void end() override;
};

