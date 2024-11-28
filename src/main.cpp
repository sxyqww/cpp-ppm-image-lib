#include "ppm_image.h"

#include <iostream>
#include <string_view>

using namespace std;
void NegateInplace(img_lib::Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            img_lib::Color& pixel = image.GetPixel(x, y);
            pixel.r = byte(255 - std::to_integer<int>(pixel.r));
            pixel.g = byte(255 - std::to_integer<int>(pixel.g));
            pixel.b = byte(255 - std::to_integer<int>(pixel.b));
        
        }
    }
}
int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <input image> <output image>"sv << endl;
        return 1;
    }

    auto image = img_lib::LoadPPM(argv[1]);
    NegateInplace(image);
    if (!image) {
        cerr << "Error loading image"sv << endl;
        return 2;
    }

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}
