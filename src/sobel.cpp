#include "ppm_image.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string_view>

using namespace std;

int Sum(img_lib::Color c) {
    return to_integer<int>(c.r) + to_integer<int>(c.g) + to_integer<int>(c.b);
}

// реализуйте оператор Собеля
img_lib::Image Sobel(const img_lib::Image& image) {
    int width = image.GetWidth();
    int height = image.GetHeight();
    img_lib::Image result(width, height, img_lib::Color::Black());

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double gx = -Sum(image.GetPixel(x - 1, y - 1)) - 2 * Sum(image.GetPixel(x, y - 1)) - Sum(image.GetPixel(x + 1, y - 1))
                      + Sum(image.GetPixel(x - 1, y + 1)) + 2 * Sum(image.GetPixel(x, y + 1)) + Sum(image.GetPixel(x + 1, y + 1));

            double gy = -Sum(image.GetPixel(x - 1, y - 1)) - 2 * Sum(image.GetPixel(x - 1, y)) - Sum(image.GetPixel(x - 1, y + 1))
                      + Sum(image.GetPixel(x + 1, y - 1)) + 2 * Sum(image.GetPixel(x + 1, y)) + Sum(image.GetPixel(x + 1, y + 1));

            const double temp1 = std::sqrt(gx * gx + gy * gy);
            int temp2 = std::clamp<double>(temp1, 0.0, 255.0);
            std::byte temp3 = static_cast<std::byte>(temp2);

            img_lib::Color newColor = {temp3, temp3, temp3};
            result.GetPixel(x, y) = newColor;
        }
    }

    return result;
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

    image = Sobel(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}