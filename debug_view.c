// #include "header.h"

// // Helper: Calculate max width of the map to determine scaling
// int get_map_width(char **map)
// {
//     int max_width = 0;
//     int y = 0;
//     int len;

//     while (map[y])
//     {
//         len = ft_strlen(map[y]);
//         if (len > max_width)
//             max_width = len;
//         y++;
//     }
//     return (max_width);
// }

// // Helper: Bresenham's Line Algorithm
// void debug_draw_line(t_data *data, int x0, int y0, int x1, int y1, uint32_t color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (1)
//     {
//         if (x0 >= 0 && x0 < screenWidth && y0 >= 0 && y0 < screenHeight)
//             mlx_put_pixel(data->img, x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = 2 * err;
//         if (e2 > -dy) { err -= dy; x0 += sx; }
//         if (e2 < dx) { err += dx; y0 += sy; }
//     }
// }

// // Helper: Draw a solid rectangle
// void debug_draw_rect(t_data *data, int x, int y, int size, uint32_t color)
// {
//     int i = 0; 
//     int j = 0;

//     // Add a 1px border for grid effect by drawing size - 1
//     int draw_size = size - 1; 
//     if (draw_size < 1) draw_size = 1;

//     while (i < draw_size)
//     {
//         j = 0;
//         while (j < draw_size)
//         {
//             if (x + j < screenWidth && y + i < screenHeight)
//                 mlx_put_pixel(data->img, x + j, y + i, color);
//             j++;
//         }
//         i++;
//     }
// }

// // The main debugging function
// void debug_view(t_data *data)
// {
//     int map_w = get_map_width(data->map);
//     int map_h = data->map_height;

//     // 1. Calculate Tile Size to fit the whole map in the window
//     // We use the smaller scale factor to ensure it fits both width and height
//     int scale_x = screenWidth / map_w;
//     int scale_y = screenHeight / map_h;
//     int scale = (scale_x < scale_y) ? scale_x : scale_y;
    
//     // Minimum scale safety
//     if (scale < 1) scale = 1;

//     // 2. Clear Screen (Fill with Black)
//     int y = 0;
//     int x = 0;
//     while (y < screenHeight)
//     {
//         x = 0;
//         while (x < screenWidth)
//         {
//             mlx_put_pixel(data->img, x, y, 0x000000FF);
//             x++;
//         }
//         y++;
//     }

//     // 3. Draw Map Grid
//     y = 0;
//     while (data->map[y])
//     {
//         x = 0;
//         while (data->map[y][x])
//         {
//             if (data->map[y][x] == '1')
//                 debug_draw_rect(data, x * scale, y * scale, scale, 0xFFFFFFFF); // White Walls
//             else if (data->map[y][x] != ' ')
//                 debug_draw_rect(data, x * scale, y * scale, scale, 0x333333FF); // Dark Grey Floor
//             x++;
//         }
//         y++;
//     }

//     // 4. Cast Rays & Draw them (Reusing your Raycasting Logic)
//     x = 0;
//     // We step by 10 to keep the view clean (drawing every single ray is too thick in 2D)
//     // Change x += 1 to x++ if you want to see every single ray
//     while (x < screenWidth) 
//     {
//         // --- YOUR RAYCASTING LOGIC START ---
//         initialize_parameters(x, data);
//         while (data->hit == 0)
//         {
//             if (data->side_dist_x < data->side_dist_y)
//             {
//                 data->side_dist_x += data->delta_dist_x;
//                 data->map_x += data->step_x;
//                 data->side = 0;
//             }
//             else
//             {
//                 data->side_dist_y += data->delta_dist_y;
//                 data->map_y += data->step_y;
//                 data->side = 1;
//             }
//             // Simple bounds check to prevent crash if ray leaves map
//             if (data->map_y < 0 || data->map_y >= (int)data->map_height || data->map_x < 0) 
//             {
//                 data->hit = 1; 
//             }
//             else if (data->map[data->map_y][data->map_x] != '0' && 
//                      !ft_strchr("NSWE", data->map[data->map_y][data->map_x]))
//             {
//                 data->hit = 1;
//             }
//         }
//         if(data->side == 0)
//             data->perp_wall_dist = (data->side_dist_x - data->delta_dist_x);
//         else
//             data->perp_wall_dist = (data->side_dist_y - data->delta_dist_y);
//         // --- YOUR RAYCASTING LOGIC END ---

//         // Calculate end point of the ray for drawing
//         // Note: perp_wall_dist is the projected distance, so we use it to calculate the end point
//         // strictly for visualization.
//         double end_x = data->position_x + (data->ray_dir_x * data->perp_wall_dist);
//         double end_y = data->position_y + (data->ray_dir_y * data->perp_wall_dist);

//         debug_draw_line(data, 
//             (int)(data->position_x * scale), 
//             (int)(data->position_y * scale), 
//             (int)(end_x * scale), 
//             (int)(end_y * scale), 
//             0x00FF00FF); // Green Rays

//         x += 20; // Draw every 20th ray
//     }

//     // 5. Draw Player (Red Dot)
//     int p_size = scale / 3;
//     if (p_size < 2) p_size = 2;
//     debug_draw_rect(data, 
//         (int)(data->position_x * scale) - p_size/2, 
//         (int)(data->position_y * scale) - p_size/2, 
//         p_size, 
//         0xFF0000FF); // Red Player

//     // Render to window
//     mlx_image_to_window(data->mlx, data->img, 0, 0);
// }