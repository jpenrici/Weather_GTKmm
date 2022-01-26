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

int WeatherApp::Gui(vector<Locale> geographic_coordinates)
{
    cities = geographic_coordinates;
    if (cities.empty()) {
        cities.push_back(Locale());
    }

    auto app = Gtk::Application::create("org.gtkmm.example");

    auto refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file("weatherWindow.glade");
    }
    catch (const Glib::FileError &ex) {
        cerr << "FileError: " << ex.what() << endl;
        return EXIT_FAILURE;
    }
    catch (const Glib::MarkupError &ex) {
        cerr << "MarkupError: " << ex.what() << endl;
        return EXIT_FAILURE;
    }
    catch (const Gtk::BuilderError &ex) {
        cerr << "BuilderError: " << ex.what() << endl;
        return EXIT_FAILURE;
    }

    pGui = nullptr;
    pLbl_inform = nullptr;
    pBtn_update = nullptr;
    pBtn_quit = nullptr;
    pBox_weather = nullptr;

    refBuilder->get_widget_derived("appWindow", pGui);
    refBuilder->get_widget("lbl_inform", pLbl_inform);
    refBuilder->get_widget("btn_update", pBtn_update);
    refBuilder->get_widget("btn_quit", pBtn_quit);
    refBuilder->get_widget("vbox_weather", pBox_weather);

    if (pBtn_update) {
        pBtn_update->signal_clicked().connect(sigc::mem_fun(*this,
                                              &WeatherApp::update));
    }

    if (pBtn_quit) {
        pBtn_quit->signal_clicked().connect(sigc::mem_fun(*this,
                                            &WeatherApp::quit));
    }

    if (pBox_weather) {
        for (int i = 0; i < MAX_WEATHERBOXES; ++i) {
            weateherBoxes.push_back(new WeatherBox());
            pBox_weather->pack_start(*weateherBoxes[i], Gtk::PACK_SHRINK);
        }
    }

    update();   // initial weather

    if (pGui) {
        cout << "GUI started." << endl;
        pGui->show_all();
        app->run(*pGui);
        cout << "GUI stoped." << endl;
    }

    // Memory
    for (auto i = 0; i < MAX_WEATHERBOXES; ++i) {
        delete weateherBoxes[i];
    }

    delete pLbl_inform;
    delete pBtn_update;
    delete pBox_weather;
    delete pGui;

    return EXIT_SUCCESS;
}

void WeatherApp::apiKey(string key)
{
    this->key = key;
}

void WeatherApp::update()
{
    // By geographic coordinates: https://openweathermap.org/current
    auto url = [](string latitude, string longitude, string apikey) {
        return (
                   "https://api.openweathermap.org/data/2.5/weather?"
                   "lat=" + latitude +
                   "&lon=" + longitude +
                   "&appid=" + apikey +
                   "&units=metric"
                   "&lang=pt-br"
               );
    };

    // Weather condition codes: https://openweathermap.org/weather-conditions
    const vector<string> image_weather {
        "0.png",  // Empty
        "0.png",  // Empty
        "2.png",  // Group 2xx: Thunderstorm - Trovoada
        "5.png",  // Group 3xx: Drizzle      - Chuvisco
        "0.png",  // Empty
        "5.png",  // Group 5xx: Rain         - Chuva
        "0.png",  // Group 6xx: Snow         - Neve
        "0.png",  // Group 7xx: Atmosphere   - Neblina
        "8.png",  // Group 800: Clear        - Claro
        "9.png"   // Group 80x: Clouds       - Nuvens
    };

    int index = 0;
    for (size_t i = 0; i < MAX_WEATHERBOXES; ++i) {
        if (i < cities.size()) {
            // Search
            auto owm = url(cities[i].latitude, cities[i].longitude, this->key);
            struct MemoryStruct data;
            data = getData(owm.c_str());

            // JSON - https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            Json::Value value;
            std::string errs;

            auto reader = std::unique_ptr<Json::CharReader>(rbuilder.newCharReader());
            const auto is_parsed = reader->parse(data.memory,
                                                 data.memory + (unsigned long)data.size * sizeof(char),
                                                 &value,
                                                 &errs);
            if (is_parsed) {
                // cout << "Parsed JSON:\n" << value << "\n";
                try {
                    auto city = value["name"].asString();
                    auto temperature = value["main"]["temp"].asString();
                    auto id_weather = value["weather"][0]["id"].asInt();

                    int cod = id_weather;
                    if (cod >= 200 && cod <= 800) {
                        cod /= 100;
                    }
                    else if (cod > 800 && cod < 805) {
                        cod = 9;
                    }
                    else {
                        cod = 0;
                    }

                    cout << "name: " << city << '\n';
                    cout << "temperature: " << temperature << '\n';
                    cout << "weather : " << id_weather << '\n';
                    if (!city.empty()) {
                        weateherBoxes[index++]->status(city, temperature, image_weather[cod]);
                    }
                }
                catch (const Json::Exception &e) {
                    cerr << "Error: " << e.what() << '\n';
                }
            }

            value.clear();
        }
    }
}

void WeatherApp::quit()
{
    pGui->hide();
}

WeatherApp::WeatherBox::WeatherBox()
{
    // Default setting
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    set_homogeneous(true);

    // Add widgets
    add(city);
    add(temperature);
    add(weatherImage);
}

void WeatherApp::WeatherBox::status(string city, string temperature, string image_weather)
{
    // Label
    this->city.set_markup("<i><b><span font=\"24\" >" + city + "</span></b></i>");
    this->temperature.set_markup("<i><b><span font=\"20\" >" + temperature + " &#176;C</span></b></i>");

    // Icon
    weatherImage.set(IMGPATH + image_weather);
}