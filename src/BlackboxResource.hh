// -*- mode: C++; indent-tabs-mode: nil; c-basic-offset: 2; -*-
// BlackboxResource.hh for Blackbox - an X11 Window manager
// Copyright (c) 2001 - 2003 Sean 'Shaleh' Perry <shaleh@debian.org>
// Copyright (c) 1997 - 2000, 2002 - 2003
//         Bradley T Hughes <bhughes at trolltech.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef   __BlackboxResource_hh
#define   __BlackboxResource_hh

#include <Bitmap.hh>
#include <Color.hh>
#include <Font.hh>
#include <Texture.hh>
#include <Timer.hh>
#include <Util.hh>

#include <vector>

class BScreen;
class Blackbox;

enum PlacementPolicy { RowSmartPlacement = 400, ColSmartPlacement,
                       CascadePlacement };
enum PlacementDirection { LeftRight = 403, RightLeft, TopBottom, BottomTop };

struct ScreenResource: public bt::NoCopy {
public:
  struct WindowStyle {
    bt::Color l_text_focus, l_text_unfocus, b_pic_focus,
      b_pic_unfocus;
    bt::Texture f_focus, f_unfocus, t_focus, t_unfocus, l_focus, l_unfocus,
      h_focus, h_unfocus, b_focus, b_unfocus, b_pressed, g_focus, g_unfocus;
    bt::Bitmap iconify, maximize, close;
    bt::Font font;
    bt::Alignment alignment;
    unsigned int handle_height, grip_width, frame_width, bevel_width,
      label_height, title_height, button_width;
  };

  struct ToolbarStyle {
    bt::Color l_text, w_text, c_text, b_pic;
    bt::Texture toolbar, label, window, button, pressed, clock;
    bt::Font font;
    bt::Alignment alignment;
  };

  void loadStyle(BScreen* screen, const std::string& style);
  void load(bt::Resource& res, unsigned int screen);
  void save(bt::Resource& res, BScreen* screen);

  // access functions
  WindowStyle* windowStyle(void)   { return &wstyle; }
  ToolbarStyle* toolbarStyle(void) { return &tstyle; }
  bt::Color* borderColor(void)     { return &border_color; }

  unsigned int bevelWidth(void) const         { return bevel_width;       }
  unsigned int borderWidth(void) const        { return border_width;      }
  unsigned int numberOfWorkspaces(void) const { return workspace_count;   }
  bool allowScrollLock(void) const            { return allow_scroll_lock; }
  const std::string& rootCommand(void) const  { return root_command;      }
  const std::string& nameOfWorkspace(unsigned int i) const;

  bool isSloppyFocus(void) const        { return wconfig.sloppy_focus;  }
  bool doAutoRaise(void) const          { return wconfig.auto_raise;    }
  bool doClickRaise(void) const         { return wconfig.click_raise;   }
  bool doOpaqueMove(void) const         { return wconfig.opaque_move;   }
  bool doFullMax(void) const            { return wconfig.full_max;      }
  bool placementIgnoresShaded(void) const
                                        { return wconfig.ignore_shaded; }
  bool doFocusNew(void) const           { return wconfig.focus_new;     }
  bool doFocusLast(void) const          { return wconfig.focus_last;    }
  int placementPolicy(void) const       { return wconfig.placement_policy; }
  unsigned int edgeSnapThreshold(void) const
                                        { return wconfig.edge_snap_threshold; }
  int rowPlacementDirection(void) const { return wconfig.row_direction; }
  int colPlacementDirection(void) const { return wconfig.col_direction; }

  bool isToolbarOnTop(void) const     { return tconfig.on_top;        }
  bool doToolbarAutoHide(void) const  { return tconfig.auto_hide;     }
  int toolbarPlacement(void) const    { return tconfig.placement;     }
  unsigned int toolbarWidthPercent(void) const
                                      { return tconfig.width_percent; }
  const char* strftimeFormat(void) const
                                    { return tconfig.strftime_format.c_str(); }

  bool isSlitOnTop(void) const    { return sconfig.on_top;    }
  bool doSlitAutoHide(void) const { return sconfig.auto_hide; }
  int slitPlacement(void) const   { return sconfig.placement; }
  int slitDirection(void) const   { return sconfig.direction; }

  // store functions
  void saveWorkspaces(unsigned int w)      { workspace_count = w;   }
  void saveAllowScrollLock(bool a)         { allow_scroll_lock = a; }
  void saveBorderColor(const bt::Color& c) { border_color = c;      }
  void saveBorderWidth(unsigned int i)     { border_width = i;      }
  void saveBevelWidth(unsigned int i)      { bevel_width = i;       }
  void saveWorkspaceName(unsigned int w, const std::string& name);

  void saveSlitPlacement(int i) { sconfig.placement = i; }
  void saveSlitDirection(int i) { sconfig.direction = i; }
  void saveSlitOnTop(bool b)    { sconfig.on_top = b;    }
  void saveSlitAutoHide(bool b) { sconfig.auto_hide = b; }

  void saveToolbarOnTop(bool b)       { tconfig.on_top = b;          }
  void saveToolbarAutoHide(bool b)    { tconfig.auto_hide = b;       }
  void saveToolbarWidthPercent(unsigned int i) { tconfig.width_percent = i; }
  void saveToolbarPlacement(int i)    { tconfig.placement = i;       }
  void saveStrftimeFormat(const std::string& f)
                                      { tconfig.strftime_format = f; }

  void saveOpaqueMove(bool o)             { wconfig.opaque_move = o;         }
  void saveFullMax(bool f)                { wconfig.full_max = f;            }
  void saveFocusNew(bool f)               { wconfig.focus_new = f;           }
  void saveFocusLast(bool f)              { wconfig.focus_last = f;          }
  void saveSloppyFocus(bool s)            { wconfig.sloppy_focus = s;        }
  void saveAutoRaise(bool a)              { wconfig.auto_raise = a;          }
  void saveClickRaise(bool c)             { wconfig.click_raise = c;         }
  void savePlacementPolicy(PlacementPolicy p)
                                          { wconfig.placement_policy = p;    }
  void saveRowPlacementDirection(PlacementDirection d)
                                          { wconfig.row_direction = d;       }
  void saveColPlacementDirection(PlacementDirection d)
                                          { wconfig.col_direction = d;       }
  void savePlacementIgnoresShaded(bool f) { wconfig.ignore_shaded = f;       }
  void saveEdgeSnapThreshold(unsigned int t)
                                          { wconfig.edge_snap_threshold = t; }

private:
  struct WindowConfig {
    bool sloppy_focus, auto_raise, opaque_move, full_max, ignore_shaded,
      focus_new, focus_last, click_raise;
    unsigned int edge_snap_threshold;
    PlacementPolicy placement_policy;
    PlacementDirection row_direction, col_direction;
  };

  struct ToolbarConfig {
    bool on_top, auto_hide;
    int placement;
    unsigned int width_percent;
    std::string strftime_format;
  };

  struct SlitConfig {
    bool on_top, auto_hide;
    int placement, direction;
  };

  WindowStyle wstyle;
  WindowConfig wconfig;
  ToolbarStyle tstyle;
  ToolbarConfig tconfig;
  SlitConfig sconfig;

  bool allow_scroll_lock;
  unsigned int workspace_count, bevel_width, border_width;
  bt::Color border_color;
  std::string root_command;
  std::vector<std::string> workspaces;
};

class BlackboxResource: public bt::NoCopy {
private:
  ScreenResource* screen_resources;

  struct BCursor {
    Cursor session, move, resize_bottom_left, resize_bottom_right;
  };
  BCursor cursor;

  std::string menu_file, style_file, rc_file;
  Time double_click_interval;
  bt::timeval auto_raise_delay;
  unsigned long cache_life, cache_max;

public:
  BlackboxResource(const std::string& rc);
  ~BlackboxResource(void);

  void load(Blackbox& blackbox);
  void save(Blackbox& blackbox);

  inline ScreenResource& screenResource(unsigned int screen)
  { return screen_resources[screen]; }

  inline Cursor sessionCursor(void) const
  { return cursor.session; }
  inline Cursor moveCursor(void) const
  { return cursor.move; }
  inline Cursor resizeBottomLeftCursor(void) const
  { return cursor.resize_bottom_left; }
  inline Cursor resizeBottomRightCursor(void) const
  { return cursor.resize_bottom_right; }

  inline const char* rcFilename(void) const
  { return rc_file.c_str(); }
  inline const char* menuFilename(void) const
  { return menu_file.c_str(); }
  inline const char* styleFilename(void) const
  { return style_file.c_str(); }

  inline void saveStyleFilename(const std::string& name)
  { style_file = name; }

  inline const Time& doubleClickInterval(void) const
  { return double_click_interval; }
  inline const bt::timeval& autoRaiseDelay(void) const
  { return auto_raise_delay; }
  inline unsigned long cacheLife(void) const
  { return cache_life; }
  inline unsigned long cacheMax(void) const
  { return cache_max; }
};

#endif
