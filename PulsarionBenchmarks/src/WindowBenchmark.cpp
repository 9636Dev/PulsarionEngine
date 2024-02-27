#include <benchmark/benchmark.h>

#include "PulsarionWindowing/Window.hpp"

using namespace Pulsarion::Windowing;
static void BM_WindowCreation(benchmark::State& state) {
    WindowBounds bounds = { 0, 0, 800, 600 };
    WindowStyles style = WindowStyles::TitleBar | WindowStyles::CloseButton | WindowStyles::Resizable;
    WindowConfig config { false, false }; // We don't want to show the window
    auto window = CreateUniqueWindow("Window", bounds, style, config); // We need to make sure that the application is not recreated every time

    for (auto _ : state) {
        benchmark::DoNotOptimize(CreateUniqueWindow("Window", bounds, style, config));
    }
}

BENCHMARK(BM_WindowCreation);

static void BM_WindowFrameTime(benchmark::State& state) {
    WindowBounds bounds = { 0, 0, 800, 600 };
    WindowStyles style = WindowStyles::TitleBar | WindowStyles::CloseButton | WindowStyles::Resizable;
    WindowConfig config { false, false }; // We don't want to show the window
    auto window = CreateUniqueWindow("Window", bounds, style, config); // We need to make sure that the application is not recreated every time

    for (auto _ : state) {
        if (!window->ShouldClose())
            window->PollEvents();
    }
}

BENCHMARK(BM_WindowFrameTime);
