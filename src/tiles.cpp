module tiles;
import sdl2;
import std;

using sdl2::Renderer;
using sdl2::Texture;
using sdl2::Point;

using std::size_t;
using std::uint32_t;
using std::int32_t;
using std::uint8_t;
using std::filesystem::path;

Tiles::Tiles(const Renderer& ren, path path_to_bmp, TilesInitData&& init_data) :
	TilesInitData(init_data), tex(ren.texture(path_to_bmp))
{
	for (uint32_t z = 0; z < num_layers; z++) {
		for (uint32_t y = 0; y < num_rows; y++) {
			int32_t x_offset = y % 2 == 0 ? 0 : dstrect_size / 2;
			for (uint32_t x = 0; x < num_cols; x++) {
				Tile tile {};

				tile.dstrect.x = static_cast<int32_t>(x * dstrect_size) + x_offset;
				tile.dstrect.y =
					static_cast<int32_t>(y) * y_offset - z_offset *
					static_cast<int32_t>(z);
				tile.dstrect.w = dstrect_size;
				tile.dstrect.h = dstrect_size;

				tile.srcrect.x = 0;
				tile.srcrect.y = 0;
				tile.srcrect.w = srcrect_size;
				tile.srcrect.h = srcrect_size;

				tile.is_staggered = x_offset ? true : false;

				tile.hitbox.w = hitbox_size;
				tile.hitbox.h = hitbox_size;
				switch(hitbox_position) {
					case HitboxPosition::TOP_CENTER:
						tile.hitbox.x = tile.dstrect.x + 
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						tile.hitbox.y = tile.dstrect.y;
						break;
					case HitboxPosition::TOP_RIGHT:
						tile.hitbox.x = tile.dstrect.x + 
							static_cast<int32_t>(dstrect_size - hitbox_size);
						tile.hitbox.y = tile.dstrect.y;
						break;
					case HitboxPosition::RIGHT_CENTER:
						tile.hitbox.x = tile.dstrect.x + 
							static_cast<int32_t>(dstrect_size - hitbox_size);
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						break;
					case HitboxPosition::BOTTOM_RIGHT:
						tile.hitbox.x = tile.dstrect.x + 
							static_cast<int32_t>(dstrect_size - hitbox_size);
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size);
						break;
					case HitboxPosition::BOTTOM_CENTER:
						tile.hitbox.x = tile.dstrect.x + 
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size);
						break;
					case HitboxPosition::BOTTOM_LEFT:
						tile.hitbox.x = tile.dstrect.x;
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size);
						break;
					case HitboxPosition::LEFT_CENTER:
						tile.hitbox.x = tile.dstrect.x;
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						break;
					case HitboxPosition::TOP_LEFT:
						tile.hitbox.x = tile.dstrect.x;
						tile.hitbox.y = tile.dstrect.y;
						break;
					case HitboxPosition::CENTER:
						tile.hitbox.x = tile.dstrect.x +
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						tile.hitbox.y = tile.dstrect.y +
							static_cast<int32_t>(dstrect_size - hitbox_size) / 2;
						break;
				}
				tiles.push_back(tile);
			}
		}
	}
}

void Tiles::update(Point mouse_pos, bool left_click) {
	size_t i = 0;
	size_t num_tiles_per_layer = num_cols * num_rows;
	for (auto& tile : tiles) {
		size_t tile_down_left_index =
			i + num_cols -
			(tile.is_staggered ? 0 : 1);
		size_t tile_down_right_index =
			i + num_cols +
			(tile.is_staggered ? 1 : 0);
		size_t tile_above_index =
			i + num_tiles_per_layer;
		size_t tile_above_up_right_index =
			i + num_tiles_per_layer - num_cols -
			(tile.is_staggered ? 1 : 0);

		// Update blocking bools

		if (tile_down_left_index < tiles.size() &&
			tiles.at(tile_down_left_index).is_active &&
			tiles.at(tile_down_left_index).dstrect.y ==
				tile.dstrect.y + y_offset
		) {
			tile.is_blocked_left = true;
		} else {
			tile.is_blocked_left = false;
		}

		if (tile_down_right_index < tiles.size() &&
			tiles.at(tile_down_right_index).is_active &&
			tiles.at(tile_down_right_index).dstrect.y ==
				tile.dstrect.y + y_offset
		) {
			tile.is_blocked_right = true;
		} else {
			tile.is_blocked_right = false;
		}

		if (tile_above_index < tiles.size() &&
			tiles.at(tile_above_index).is_active
		) {
			tile.is_blocked_above = true;
		} else {
			tile.is_blocked_above = false;
		}

		// Update visibility
		
		if (tile.is_blocked_above &&
			tile.is_blocked_left &&
			tile.is_blocked_right
		) {
			tile.is_visible = false;
		} else {
			tile.is_visible = true;
		}

		// Update exposure
		
		if (!tile.is_blocked_above) {
			tile.is_exposed = true;
		} else {
			tile.is_exposed = false;
		}

		// Update highlight
		
		if (tile.is_exposed &&
			mouse_pos.has_intersection(tile.hitbox)
		) {
			tile.is_highlighted = true;
		} else {
			tile.is_highlighted = false;
		}

		// Update activity
		
		if (tile.is_highlighted && left_click ) {
			tile.is_active = false;
		}

		// Update lighting

		if (tile_above_up_right_index < tiles.size() &&
			tiles.at(tile_above_up_right_index).is_active
		) {
			tile.is_in_shadow = true;
		} else {
			tile.is_in_shadow = false;
		}

		i++;
	}
}

void Tiles::draw(const Renderer& ren) const {
	static uint8_t old_alpha {255};
	static uint8_t new_alpha {255};
	for (const auto& tile : tiles) {

		// Render base rect
		if (tile.is_highlighted) {
			new_alpha = 128;
		} else {
			new_alpha = 255;
		}
		if (new_alpha != old_alpha) {
			ren.set_alpha_mode(tex, new_alpha);
		}
		old_alpha = new_alpha;
		if (tile.is_active && tile.is_visible) {
			ren.copy(tex, tile.dstrect, tile.srcrect);
		}

		// Render shadows
		if (tile.is_in_shadow) {
			Rect srcrect = tile.srcrect;
			srcrect.x = srcrect.w * 5;
			ren.copy(tex, tile.dstrect, srcrect);
		}

	}
	// ren.set_draw_color({100, 100, 200, 100});
	// for (const auto& tile : tiles) {
	// 	if (tile.is_exposed) {
	// 		ren.fill_rect(tile.hitbox);
	// 	}
	// }
}
