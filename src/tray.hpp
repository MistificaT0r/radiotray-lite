#ifndef __TRAY_HPP_INCLUDED__
#define __TRAY_HPP_INCLUDED__

#include <functional>
#include <iostream>
#include <memory>
#include <stack>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <gtkmm.h>

#ifndef AYATANA_APPINDICATOR
#include <libappindicator/app-indicator.h>
#else
#include <libayatana-appindicator/app-indicator.h>
#endif


#include "pugixml/pugixml.hpp"

#include "about.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "notification.hpp"
#include "player.hpp"
#include "options.hpp"

namespace radiotray
{

class RadioTrayLite
{
public:
    RadioTrayLite() = default;
    RadioTrayLite(const RadioTrayLite&) = delete;

    ~RadioTrayLite();

    bool init(int argc, char** argv, std::shared_ptr<CmdLineOptions>& opts);
    int run();

private:
    bool initialized = false;
    Glib::RefPtr<Gtk::Application> app;
    std::shared_ptr<Gtk::Menu> menu;

    Gtk::MenuItem* current_station_menu_entry = nullptr;
    Gtk::MenuItem* current_broadcast_menu_entry = nullptr;

    AppIndicator* indicator = nullptr;

    std::string bookmarks_file;
    pugi::xml_document bookmarks_doc;

    std::shared_ptr<Player> player;
    std::shared_ptr<EventManager> em;
    std::shared_ptr<Notification> notifier;
    std::shared_ptr<Config> config;
    std::shared_ptr<CmdLineOptions> cmd_line_options;

    class BookmarksWalker : public pugi::xml_tree_walker
    {
    public:
        BookmarksWalker() = delete;
        BookmarksWalker(const BookmarksWalker&) = delete;

        BookmarksWalker(RadioTrayLite& radiotray, Gtk::Menu* menu);

        bool for_each(pugi::xml_node& node) override;

    private:
        static constexpr char const* kSeparatorPrefix = "[separator-";
        static const size_t kSeparatorPrefixLength = strlen(kSeparatorPrefix);

        RadioTrayLite& radiotray;
        std::stack<Gtk::Menu*> menus;
        int level = 0; // TODO: for debug, remove.
    };

    void on_quit_button();
    void on_about_button();
    void on_station_button(const Glib::ustring& group_name, const Glib::ustring& station_name, const Glib::ustring& station_url);
    void on_reload_button();
    void on_current_station_button();

    bool resume(bool resume_last_station);

    void build_menu();
    void rebuild_menu();
    void clear_menu();
    bool parse_bookmarks_file();
    void load_configuration();
    void set_current_station(bool turn_on);
    void set_current_broadcast(const Glib::ustring& info = Glib::ustring("Idle"));

    void on_station_changed_signal(const Glib::ustring& station, StationState state);
    void on_broadcast_info_changed_signal(const Glib::ustring& station, const Glib::ustring& info);

    void copy_default_bookmarks(const std::string& src_file);

    bool file_exists(const std::string& dir, const std::string& file);
    bool dir_exists(const std::string& dir);
};

} // namespace radiotray

#endif
