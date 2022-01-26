/*
 * Reference:
 *    https://www.gtkmm.org
 *    https://github.com/open-source-parsers/jsoncpp
 *
 * Requeriment
 *    libgtkmm-3.0-dev
 *    libjsoncpp-dev
 */

#include "weatherApp.hpp"

int main(int argc, char **argv)
{
    WeatherApp app;
    // app.apiKey("your_key");
    app.apiKey("774e7dc4a18fc56df6669e22e795341a");

    vector<Locale> geographic_coordinates {
        Locale{"-15.7797", "-47.9297"},         // Brasília - DF, Brasil
        Locale{"-22.9110137", "-43.2093727"},   // Rio de Janeiro - RJ, Brasil
        Locale{"-12.9822499", "-38.4812772"},   // Salvador - BA, Brasil
        Locale{"-22.5266308", "-42.9790687"},   // Guapimirim - RJ, Brasil
        Locale{"-20.7538586", "-42.8815888"}    // Viçosa - MG, Brasil
    };

    return app.Gui(geographic_coordinates);
}