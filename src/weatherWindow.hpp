/*
 * Reference:
 *    https://www.gtkmm.org
 *    https://github.com/open-source-parsers/jsoncpp
 *
 * Requeriment
 *    libgtkmm-3.0-dev
 *    libjsoncpp-dev
 */

#ifndef __WEATHER_GTKMM_H_
#define __WEATHER_GTKMM_H_

#include <gtkmm.h>

class WeatherWindow : public Gtk::ApplicationWindow {

public:
    WeatherWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);
    virtual ~WeatherWindow();

protected:
    Glib::RefPtr<Gtk::Builder> m_refGlade;
};

#endif // __WEATHER_GTKMM_H_