#ifndef PALLETE_H
#define PALLETE_H

#include <stdio.h>

// https://github.com/janleigh/dotfiles#art-colorscheme

#define COLOR_BACKGROUND "#0B0F10"
#define COLOR_FOREGROUND "#C5C8C9"

#define COLOR_BLACK "#131718"
#define COLOR_RED "#DF5B61"
#define COLOR_GREEN "#87C7A1"
#define COLOR_YELLOW "#DE8F78"
#define COLOR_BLUE "#6791C9"
#define COLOR_PURPLE "#BC83E3"
#define COLOR_CYAN "#70B9CC"
#define COLOR_WHITE "#C4C4C4"

#define COLOR_BRIGHT_BLACK "#151A1C"
#define COLOR_BRIGHT_RED "#EE6A70"
#define COLOR_BRIGHT_GREEN "#96D6B0"
#define COLOR_BRIGHT_YELLOW "#FFB29B"
#define COLOR_BRIGHT_BLUE "#7BA5DD"
#define COLOR_BRIGHT_PURPLE "#CB92F2"
#define COLOR_BRIGHT_CYAN "#7FC8DB"
#define COLOR_BRIGHT_WHITE "#CCCCCC"

#define COLOR_WRITE(hex, color) sscanf(hex, "#%2hhx%2hhx%2hhx", &color[0], &color[1], &color[2])

#endif // PALLETE_H
