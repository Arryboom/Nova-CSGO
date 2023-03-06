#pragma once

#define CONCAT(a, b) a##b
#define PAD_NAME(n) CONCAT(pad, n)
#define PAD(size) unsigned char PAD_NAME(__LINE__) [size]

struct ViewRender {
    PAD(1416);
    float smokeOverlayAmount;
};