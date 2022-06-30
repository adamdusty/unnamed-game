#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace pong {

struct Image {
private:
    struct ImageDeleter {
        auto operator()(uint8_t *data) -> void;
    };

public:
    int32_t width;
    int32_t height;
    int32_t depth;
    int32_t pitch;
    int32_t channels;
    std::unique_ptr<uint8_t, ImageDeleter> data;

    Image() = default;
    Image(int32_t w, int32_t h, int32_t d, int32_t p, int32_t c, uint8_t *data) :
        width(w), height(h), depth(d), pitch(p), channels(c), data(std::unique_ptr<uint8_t, ImageDeleter>(data)) {}
};

auto load_image(const std::string &path) -> Image;

} // namespace pong