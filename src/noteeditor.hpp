/*
 * gnote
 *
 * Copyright (C) 2011,2013,2016-2017,2019-2020 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */




#ifndef __NOTE_EDITOR_HPP_
#define __NOTE_EDITOR_HPP_

#include <glibmm/refptr.h>
#include <gtkmm/textview.h>


namespace Gio {

class Settings;

}

namespace gnote {

class Preferences;


class NoteEditor
  : public Gtk::TextView
{
public:
  typedef Glib::RefPtr<NoteEditor> Ptr;

  NoteEditor(const Glib::RefPtr<Gtk::TextBuffer> & buffer, Preferences & preferences);
  static int default_margin()
    {
      return 8;
    }

protected:
  virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext> & context,
                                     int x, int y,
                                     const Gtk::SelectionData & selection_data,
                                     guint info,  guint time) override;

private:
  static void paste_started(GtkTextView*, NoteEditor *_this);
  static void paste_ended(GtkTextView*, NoteEditor *_this);

  Pango::FontDescription get_gnome_document_font_description();
  void on_gnome_font_setting_changed();
  void update_custom_font_setting();
  void modify_font_from_string (const Glib::ustring & fontString);
  bool key_pressed (GdkEventKey * ev);
  bool button_pressed (GdkEventButton * ev);
  void on_paste_start();
  void on_paste_end();

  Preferences & m_preferences;
};


}

#endif
