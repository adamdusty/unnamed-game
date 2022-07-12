#include "plugin.hpp"

#include <windows.h>
#include <fmt/format.h>

namespace ung {
namespace sdk {

PluginService::~PluginService() {
    this->plugins = std::vector<Plugin>{};
    for(auto lib: this->plugin_libs) {
        FreeLibrary((HMODULE)lib);
    }
}

auto PluginService::load_plugin(const char *path) -> void {
    auto lib = LoadLibraryA(path);
    if (!lib) {
        fmt::print("ERROR LOADING LIB: {}", GetLastError());
        // TODO: Handle error
    }
    this->plugin_libs.emplace_back(lib);

    auto load_plugin = reinterpret_cast<Plugin (*)()>(GetProcAddress(lib, "load_plugin"));
    if (load_plugin == nullptr) {
        fmt::print("ERROR LOADING FUNC: {}", GetLastError());
        // TODO: Handle error
    }

    this->plugins.emplace_back(load_plugin());
}

auto PluginService::initialize_plugins(SDL_Window *window) -> void {
    for(auto &p: this->plugins) {
        for(auto &sys: p.systems) {
            sys->init(window);
        }
    }
}

}
}