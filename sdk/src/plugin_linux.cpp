#include "plugin.hpp"

#include <dlfcn.h>

namespace ung {
namespace sdk {

auto load_plugin(const char *path) -> std::unique_ptr<Plugin> {
    auto lib = dlopen(path, RTLD_LAZY);
    if(lib == nullptr) {
        // TODO
        dlerror();
    }

    auto load_plugin = reinterpret_cast<std::unique_ptr<Plugin> (*)()>(dlsym(lib, "load_plugin"));
    if(auto err = dlerror()) {
        // TODO
    }

    return load_plugin();
}

} // namespace sdk
} // namespace ung