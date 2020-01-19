/*
 * gnote
 *
 * Copyright (C) 2012,2017,2020 Aurimas Cernius
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




#ifndef __SHARP_DATETIME_HPP__
#define __SHARP_DATETIME_HPP__

#include <time.h>

#include <glibmm/datetime.h>
#include <glibmm/ustring.h>
#include <glibmm/timeval.h>

#include "timespan.hpp"

namespace sharp {


class DateTime
{
public:
  DateTime();
  explicit DateTime(time_t t, glong _usec = 0);
  explicit DateTime(const Glib::TimeVal & v);
 
  DateTime & add_days(int days);
  DateTime & add_hours(int hours);
  DateTime & add_seconds(int seconds);

  int day() const;
  int month() const;
  int year() const;
  int day_of_year() const;

  bool is_valid() const;

  Glib::ustring to_string(const char * format) const;
  Glib::ustring to_string(const Glib::ustring & format) const
    {
      return to_string(format.c_str());
    }
  Glib::ustring to_short_time_string() const;
  Glib::ustring to_iso8601() const;

  static DateTime now();
  static DateTime from_iso8601(const Glib::ustring &);
  static int compare(const DateTime &, const DateTime &);

  bool operator==(const DateTime & dt) const;
  bool operator!=(const DateTime & dt) const
    {
      return !(*this == dt);
    }
  bool operator>(const DateTime & dt) const;
  bool operator>=(const DateTime & dt) const
    {
      return (*this == dt) || (*this > dt);
    }
  bool operator<(const DateTime & dt) const
    {
      return !(*this >= dt);
    }
  bool operator<=(const DateTime & dt) const
    {
      return (*this < dt) || (*this == dt);
    }
  Glib::TimeSpan operator-(const DateTime & dt) const;
  DateTime operator-(const Glib::TimeSpan & ts) const;

  glong sec() const
    {
      return m_date.tv_sec;
    }
  glong usec() const
    {
      return m_date.tv_usec;
    }
  void set_usec(glong _usec) 
    {
      m_date.tv_usec = _usec;
    }
private:
  // return the string formatted according to strftime
  Glib::ustring _to_string(const char * format, struct tm *) const;
  Glib::TimeVal m_date;
};


Glib::ustring date_time_to_string(const Glib::DateTime & dt, const char *format);
Glib::ustring date_time_to_string(const Glib::DateTime & dt, const Glib::ustring & format);
Glib::ustring date_time_to_iso8601(const Glib::DateTime & dt);
Glib::DateTime date_time_from_iso8601(const Glib::ustring & dt);


}


bool operator==(const Glib::DateTime & x, const Glib::DateTime & y);
bool operator!=(const Glib::DateTime & x, const Glib::DateTime & y);
bool operator<(const Glib::DateTime & x, const Glib::DateTime & y);
bool operator<=(const Glib::DateTime & x, const Glib::DateTime & y);
bool operator>(const Glib::DateTime & x, const Glib::DateTime & y);
bool operator>=(const Glib::DateTime & x, const Glib::DateTime & y);

#endif
