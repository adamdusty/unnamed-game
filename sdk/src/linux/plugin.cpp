#ifdef __linux__

#include "plugin.hpp"

#include "fmt/format.h"
#include <dlfcn.h>

namespace ung {
namespace sdk {

PluginService::~PluginService() {
    this->plugins = std::vector<Plugin>{};
    for(auto lib: this->plugin_libs) {
        dlclose(lib);
    }
}

auto PluginService::load_plugin(const char *path) -> void {
    auto lib = dlopen(path, RTLD_LAZY);
    if(lib == nullptr) {
        // TODO
        fmt::print("ERROR LOADING LIB: {}\n", dlerror());
    }

    this->plugin_libs.emplace_back(lib);

    auto load_plugin = reinterpret_cast<Plugin (*)()>(dlsym(lib, "load_plugin"));
    if(auto err = dlerror()) {
        fmt::print("ERROR LOADING FUNC: {}\n", err);
        // TODO
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

} // namespace sdk
} // namespace ung

#endif