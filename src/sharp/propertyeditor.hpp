/*
 * gnote
 *
 * Copyright (C) 2011,2013,2017,2019-2020 Aurimas Cernius
 * Copyright (C) 2009 Hubert Figuiere
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */





#ifndef __PROPERTYEDITOR_HPP_
#define __PROPERTYEDITOR_HPP_

#include <vector>

#include <giomm/settings.h>
#include <gtkmm/entry.h>
#include <gtkmm/togglebutton.h>

namespace sharp {

  class PropertyEditorBase
  {
  public:
    virtual ~PropertyEditorBase();
    virtual void setup() = 0;

  protected:
    explicit PropertyEditorBase(Gtk::Widget & w);

    Gtk::Widget &m_widget;
    sigc::connection m_connection;
  private:
    void static destroy_notify(gpointer data);
  };

  class PropertyEditor
      : public PropertyEditorBase
  {
  public:
    PropertyEditor(std::function<Glib::ustring()> getter, std::function<void(const Glib::ustring&)> setter, Gtk::Entry &entry);

    virtual void setup() override;

  private:
    void on_changed();
    std::function<Glib::ustring()> m_getter;
    std::function<void(const Glib::ustring&)> m_setter;
  };

  class PropertyEditorBool
    : public PropertyEditorBase
  {
  public:
    PropertyEditorBool(std::function<bool()> getter, std::function<void(bool)> setter, Gtk::ToggleButton &button);
    void add_guard(Gtk::Widget* w)
      {
        m_guarded.push_back(w);
      }

    virtual void setup() override;

  private:
    void guard(bool v);
    void on_changed();
    std::vector<Gtk::Widget*> m_guarded;
    std::function<bool()> m_getter;
    std::function<void(bool)> m_setter;
  };

}


#endif
