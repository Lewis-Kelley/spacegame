#ifndef MOCKWINDOW_H
#define MOCKWINDOW_H

#include <gmock/gmock.h>

#include "../../src/util/Window.hpp"

class MockWindow : public Window {
 public:
    MockWindow() : Window(0, 0) { }

    MOCK_METHOD0(get_rend, Renderer *());
};

#endif /* MOCKWINDOW_H */
