#pragma once

#define NON_COPYABLE(class) class(const class &) = delete; class &operator=(const class &) = delete;
#define NON_MOVABLE(class) class(class &&) = delete; class &operator=(class &&) = delete;