#include "image.h"

#include "fmt/format.h"
#include "stb_image.h"

namespace pong {

auto Image::ImageDeleter::operator()(uint8_t *data) -> void {
    stbi_image_free(data);
}

auto load_image(const std::string &path) -> Image {
    int32_t w, h, c;
    auto img_data = stbi_load(path.c_str(), &w, &h, &c, STBI_rgb_alpha);
    if(img_data == nullptr) {
        fmt::print("STB failed to load img: {}", stbi_failure_reason());
        return Image{};
    }

    return Image{w, h, 32, 4 * w, c, img_data};
}

} // namespace pong