#include "sdk.hpp"
using namespace ung::sdk;

extern "C" auto load_plugin() -> std::unique_ptr<Plugin>;
