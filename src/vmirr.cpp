#include "ppm_image.h"

#include <algorithm>
#include <iostream>
#include <string_view>

using namespace std;

// реализуйте вертикальное отражение
void VMirrInplace(img_lib::Image& image) {
    img_lib::Image dst(image.GetWidth(), image.GetHeight(), img_lib::Color::Black());
    int new_y = 0;
    for (int y = image.GetHeight() - 1; y >= 0; --y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            img_lib::Color& new_pixel = dst.GetPixel(x, new_y);
            new_pixel = image.GetPixel(x, y);
        }
        new_y += 1;
    }
    image = dst;
}

int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <input image> <output image>"sv << endl;
        return 1;
    }

    auto image = img_lib::LoadPPM(argv[1]);
    if (!image) {
        cerr << "Error loading image"sv << endl;
        return 2;
    }

    VMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}