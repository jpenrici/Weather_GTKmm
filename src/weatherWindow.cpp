/*
 * Reference:
 *    https://www.gtkmm.org
 *    https://github.com/open-source-parsers/jsoncpp
 *
 * Requeriment
 *    libgtkmm-3.0-dev
 *    libjsoncpp-dev
 */

#include "weatherWindow.hpp"

WeatherWindow::WeatherWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade)
    : Gtk::ApplicationWindow(cobject), m_refGlade(refGlade)
{
}

WeatherWindow::~WeatherWindow()
{
}