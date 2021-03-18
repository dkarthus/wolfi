cmake_minimum_required(VERSION 3.17)

project(wolfi)

set(CMAKE_C_STANDARD 99)

add_executable(wolfi
        cub3d.h
        ./parser/ft_map_parser.c
        ./parser/ft_parse_legend.c
        ./parser/ft_parse_legend_utils.c
        ./parser/ft_parse_legend_utils2.c
        ./parser/ft_parse_legend_utils3.c
        render/sprite_utils.c
        render/ft_draw_sprites.c
        render/draw_utils.c
        render/bitmap.c
        etc/init_params.c
        etc/keys.c
        main.c
        render/ft_draw_walls.c
        render/ft_draw_walls2.c etc/init_txt.c)

target_link_libraries(wolfi PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libft.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libmlx.a
        X11 Xext bsd m)
