export module ground;

import std;
import init;
import sdl;

using std::vector;
using std::size_t;
using std::int32_t;

export struct Block {
	FRect dstrect;
	FRect hitbox;
	Rect srcrect;
	bool active {true};
	bool visible {true};
	bool blocked_from_above {false};
	size_t tex_id;
	vector<Rect> shading;
	size_t layer;
	size_t row;
	size_t col;
};

export class Ground : game::BlocksInitData {

private:

	vector<Block> blocks;
	const size_t num_blocks_per_layer;
	const size_t num_blocks;

	Rect shading(size_t shade_index) const {
		return Rect{
			.x = static_cast<int32_t>(shade_index) *
				static_cast<int32_t>(img_size),
			.y = 0,
			.w = img_size,
			.h = img_size
		};
	}

	size_t index(size_t layer, size_t row, size_t col) const {
		if (	layer >= num_layers ||
			row >= num_rows ||
			col >= num_cols
		) {
			return (size_t)-1;
		}

		return
			layer * num_blocks_per_layer +
			row * num_cols +
			col;
	}

	bool blocked(size_t layer, size_t row, size_t col) {
		size_t i = index(layer, row, col);

		return
			i != -1lu &&
			blocks[i].active;
	}

public:

	Ground(game::BlocksInitData init_data, size_t tex_id) :
		game::BlocksInitData(init_data),
		num_blocks_per_layer(num_rows * num_cols),
		num_blocks(num_layers * num_blocks_per_layer)
	{
		for (size_t i = 0; i < num_blocks; i++) {
			const size_t layer = i / num_blocks_per_layer;
			const  size_t row =
				(i - layer * num_blocks_per_layer) / num_cols;
			const size_t col = i - layer * num_blocks_per_layer - 
				row * num_cols;

			const float flayer = static_cast<float>(layer);
			const float frow = static_cast<float>(row);
			const float fcol = static_cast<float>(col);

			const FRect dstrect {
				.x = origin_x + fcol * x_offset -
					frow * x_offset,
				.y = origin_y + frow * y_offset +
					fcol * y_offset -
					flayer * z_offset,
				.w = block_size,
				.h = block_size
			};

			const Rect srcrect {
				.x = 0,
				.y = 0,
				.w = img_size,
				.h = img_size
			};

			const FRect hitbox {
				.x = dstrect.x + (block_size - hitbox_size) / 2,
				.y = dstrect.y + 1,
				.w = hitbox_size,
				.h = hitbox_size
			};

			const Block block {
				.dstrect = dstrect,
				.hitbox = hitbox,
				.srcrect = srcrect,
				.active =
					layer >= num_visible_layers ?
					false : true,
				.tex_id = tex_id,
				.shading = {},
				.layer = layer,
				.row = row,
				.col = col
			};

			blocks.push_back(block);
		}
	}
	const vector<Block> &get_blocks() const {
		return blocks;
	}
	void update(Point mouse, bool left_click, bool right_click, bool b_key) {
		FRect mouse_rect {
			static_cast<float>(mouse.x),
			static_cast<float>(mouse.y),
			1, 1
		};

		static Block* highlighted_block {nullptr};
		static Block* selected_block {nullptr};

		for (auto& block : blocks) {
			
			block.shading.clear();

			const size_t layer = block.layer;
			const size_t row = block.row;
			const size_t col = block.col;

			const bool blocked_from_above = 
				blocked(layer + 1, row, col);
			const bool blocked_from_right =
				blocked(layer, row - 1, col + 1);
			const bool blocked_from_left =
				blocked(layer, row + 1, col - 1);
			const bool blocked_from_right_up =
				blocked(layer, row - 1, col);
			const bool blocked_from_right_down =
				blocked(layer, row, col + 1);
			// const bool blocked_from_left_up =
			// 	blocked(layer, row, col - 1);
			const bool blocked_from_left_down =
				blocked(layer, row + 1, col);
			const bool blocked_from_above_right_up =
				blocked(layer + 1, row - 1, col);
			const bool blocked_from_above_down =
				blocked(layer + 1, row + 1, col + 1);
			const bool blocked_from_above_right_down =
				blocked(layer + 1, row, col + 1);
			const bool blocked_from_above_left_down =
				blocked(layer + 1, row + 1, col);

			// Visibility

			block.visible =
				!block.active ||
				(blocked_from_above_right_down &&
				 blocked_from_above_left_down) ?
				false : true;


			// Selectability

			block.blocked_from_above = blocked_from_above;

			// if (	block.active &&
				// (!blocked_from_above ||
				 // !blocked_from_right_down ||
				 // !blocked_from_left_down ||
				 // !blocked_from_above_down ||
				 // !blocked_from_above_right_down ||
				 // !blocked_from_above_left_down)
			// ) {
				// block.visible = true;
			// } else {
				// block.visible = false;
			// }

			// Shading
			
			if (	block.visible &&
				blocked_from_right &&
				!blocked_from_right_down
			) {
				block.shading.push_back(
					shading(right_shadow_index)
				);
			}

			if (	block.visible &&
				blocked_from_left &&
				!blocked_from_left_down
			) {
				block.shading.push_back(
					shading(left_shadow_index)
				);
			}

			if (	block.visible &&
				!blocked_from_right_down &&
				!blocked_from_left_down
			) {
				block.shading.push_back(
					shading(front_corner_index)
				);
			}

			if (	block.visible &&
				!blocked_from_right &&
				!blocked_from_right_up
			) {
				block.shading.push_back(
					shading(right_light_index)
				);
			}

			if (	block.visible &&
				blocked_from_above_right_up
			) {
				block.shading.push_back(
					shading(top_shadow_index)
				);
			}

			// Highlight, destroy, and select, build
			
			if (	block.visible &&
				!blocked_from_above &&
				!blocked_from_above_down &&
				// !blocked_from_above_right_down &&
				// !blocked_from_above_left_down &&
				mouse_rect.has_intersection(block.hitbox)
			) {
				highlighted_block = &block;
			}

			if (	highlighted_block &&
				highlighted_block->blocked_from_above
			) {
				highlighted_block = nullptr;
			}

			if (	highlighted_block &&
				&block == highlighted_block
			) {
				block.shading.push_back(
					shading(highlighted_index)
				);
			}

			if (	highlighted_block &&
				&block == highlighted_block &&
				right_click
			) {
				block.active = false;
			}

			if (	highlighted_block &&
				&block == highlighted_block &&
				left_click
			) {
				selected_block = &block;
			}

			if (	selected_block &&
				&block == selected_block
			) {
				block.shading.push_back(
					shading(selected_index)
				);
			}

			if (	highlighted_block &&
				&block == highlighted_block &&
				b_key &&
				layer + 1 < num_layers
			) {
				blocks.at(index(layer + 1, row, col)).active =
					true;
			}
		}
	}
};

// }
