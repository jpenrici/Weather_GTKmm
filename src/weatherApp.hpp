/*
 * Reference:
 *    https://www.gtkmm.org
 *    https://github.com/open-source-parsers/jsoncpp
 *
 * Requeriment
 *    libgtkmm-3.0-dev
 *    libjsoncpp-dev
 */

#ifndef __WEATHERAPP_H__
#define __WEATHERAPP_H__

#include "weatherWindow.hpp"
#include "connect.h"

#include <iostream>
#include <vector>
#include <string>

#include <jsoncpp/json/json.h>

using namespace std;

constexpr int MAX_WEATHERBOXES = 5;
const string IMGPATH = "../Images/";

struct Locale {
    string latitude = "-22.9110137";    // Default
    string longitude = "-43.2093727";   // Rio de Janeiro - RJ, Brasil
};

class WeatherApp {

public:
    int Gui(vector<Locale> geographic_coordinates);
    void apiKey(string key);

private:
    // custom widget
    class WeatherBox : public Gtk::Box {

    public:
        WeatherBox();
        virtual ~WeatherBox() {};

        void status(string city, string temperature, string weather);

    private:
        Gtk::Label city;
        Gtk::Label temperature;
        Gtk::Image weatherImage;
    };

    // Glade file references
    WeatherWindow *pGui;
    Gtk::Label *pLbl_inform;
    Gtk::Button *pBtn_update;
    Gtk::Button *pBtn_quit;
    Gtk::Box *pBox_weather;

    // Data
    string key;
    vector<Locale> cities;
    vector<WeatherBox *> weateherBoxes;

    void update();
    void quit();
};

#endif // __WEATHERAPP_H__