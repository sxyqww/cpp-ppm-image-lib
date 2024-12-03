#include <ppm_image.h>

#include <iostream>
#include <string_view>

using namespace std;

// реализуйте горизонтальное отражение
void HMirrInplace(img_lib::Image& image) {
    img_lib::Image dst(image.GetWidth(), image.GetHeight(), img_lib::Color::Black());
    for (int y = 0; y < image.GetHeight(); ++y) {
        int new_x = 0;  
        for (int x = image.GetWidth() - 1; x >= 0; --x) {
            img_lib::Color& new_pixel = dst.GetPixel(new_x, y);
            new_pixel = image.GetPixel(x, y);
            new_x += 1;
        }
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

    HMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}