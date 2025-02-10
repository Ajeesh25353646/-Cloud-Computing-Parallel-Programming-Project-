#include <SFML/Graphics.hpp>
#include <complex>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>
#include <tbb/partitioner.h>
#include <fstream>
#include <chrono>

using Complex = std::complex<double>;

int mandelbrot(Complex const& c) {
    int i = 0;
    auto z = c;
    for (; i != 256 && norm(z) < 4.; ++i) {
        z = z * z + c;
    }
    return i;
}

auto to_color(int k) {
    return k < 256 ? sf::Color{static_cast<sf::Uint8>(10 * k), 0, 0}
                   : sf::Color::Black;
}

void generate_mandelbrot(int grain_size, const std::string& output_image, const std::string& output_log) {
    int const display_width{800};
    int const display_height{800};

    Complex const top_left{-2.2, 1.5};
    Complex const lower_right{0.8, -1.5};
    auto const diff = lower_right - top_left;

    auto const delta_x = diff.real() / display_width;
    auto const delta_y = diff.imag() / display_height;

    sf::Image image;
    image.create(display_width, display_height);

    auto start_time = std::chrono::high_resolution_clock::now();

    tbb::parallel_for(
        tbb::blocked_range2d<int>(0, display_height, grain_size, 0, display_width, grain_size),
        [&](const tbb::blocked_range2d<int>& range) {
            for (int row = range.rows().begin(); row < range.rows().end(); ++row) {
                for (int col = range.cols().begin(); col < range.cols().end(); ++col) {
                    auto k = mandelbrot(top_left + Complex{delta_x * col, delta_y * row});
                    image.setPixel(col, row, to_color(k));
                }
            }
        },
        tbb::simple_partitioner{}
    );

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Save image
    image.saveToFile(output_image);

    // Save execution time to log
    std::ofstream log_file(output_log, std::ios_base::app);
    log_file << grain_size << "\t" << duration << " ms\n";
    log_file.close();
}

int main() {
    const std::string output_image = "mandelbrot.png";
    const std::string output_log = "mandelbrot_times.txt";

    // Clear the log file
    std::ofstream log_file(output_log, std::ios_base::trunc);
    log_file << "Grain Size\tExecution Time (ms)\n";
    log_file.close();

    // Test different grain sizes
    for (int grain_size : {1, 4, 8, 16, 32, 64, 128, 256}) {
        generate_mandelbrot(grain_size, output_image, output_log);
    }

    return 0;
}
