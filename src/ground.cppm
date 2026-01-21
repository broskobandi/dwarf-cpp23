export module ground;

import std;
import config;
import sdl;
import products;

using std::vector;
using std::size_t;
using std::int32_t;

export class Ground : game::GroundConfig {

private:

	GroundProduct product;
	const size_t num_blocks_per_layer;
	const size_t num_blocks;

	Rect get_shading(size_t shade_index) const {
		return Rect{
			.x = static_cast<int32_t>(shade_index) *
				static_cast<int32_t>(img_size),
			.y = 0,
			.w = img_size,
			.h = img_size
		};
	}

	size_t get_index(size_t layer, size_t row, size_t col) const {
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

	const Block* get_block(size_t layer, size_t row, size_t col) const {
		size_t index = get_index(layer, row, col);
		if (index == (size_t)-1) return nullptr;
		return &product.blocks.at(index);
	}

	bool is_blocked(size_t layer, size_t row, size_t col) {
		size_t i = get_index(layer, row, col);

		return
			i != (size_t)-1 &&
			product.blocks[i].is_active;
	}

public:

	Ground(game::GroundConfig config, size_t tex_id) :
		game::GroundConfig(config),
		num_blocks_per_layer(num_rows * num_cols),
		num_blocks(num_blocks_per_layer * num_layers)
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

			const Block block {
				.dstrect = dstrect,
				.srcrect = srcrect,
				.is_active =
					layer >= num_visible_layers ?
					false : true,
				.tex_id = tex_id,
				.shading = {},
				.location {
					.layer = layer,
					.row = row,
					.col = col
				}
			};

			product.blocks.push_back(block);
		}
	}
	const GroundProduct& get_product() const {
		return product;
	}
	void update(const TasksProduct& tasks_product) {
		for (auto& block : product.blocks) {
			
			block.shading.clear();

			const size_t layer = block.location.layer;
			const size_t row = block.location.row;
			const size_t col = block.location.col;

			const bool is_blocked_from_above = 
				is_blocked(layer + 1, row, col);
			const bool is_blocked_from_right =
				is_blocked(layer, row - 1, col + 1);
			const bool is_blocked_from_left =
				is_blocked(layer, row + 1, col - 1);
			const bool is_blocked_from_right_up =
				is_blocked(layer, row - 1, col);
			const bool is_blocked_from_right_down =
				is_blocked(layer, row, col + 1);
			// const bool is_blocked_from_left_up =
			// 	is_blocked(layer, row, col - 1);
			const bool is_blocked_from_left_down =
				is_blocked(layer, row + 1, col);
			const bool is_blocked_from_above_right_up =
				is_blocked(layer + 1, row - 1, col);
			const bool is_blocked_from_above_down =
				is_blocked(layer + 1, row + 1, col + 1);
			const bool is_blocked_from_above_right_down =
				is_blocked(layer + 1, row, col + 1);
			const bool is_blocked_from_above_left_down =
				is_blocked(layer + 1, row + 1, col);

			// Visibility, selectability

			block.is_visible =
				!block.is_active ||
				(is_blocked_from_above_right_down &&
				 is_blocked_from_above_left_down) ?
				false : true;

			const Block* block_below =
				get_block(layer - 1, row, col);

			block.is_selectable =
				block_below &&
				block_below->is_visible &&
				!block.is_visible ?
				true : false;

			// Shading
			
			if (	block.is_visible &&
				is_blocked_from_right &&
				!is_blocked_from_right_down
			) {
				block.shading.push_back(
					get_shading(right_shadow_index)
				);
			}

			if (	block.is_visible &&
				is_blocked_from_left &&
				!is_blocked_from_left_down
			) {
				block.shading.push_back(
					get_shading(left_shadow_index)
				);
			}

			if (	block.is_visible &&
				!is_blocked_from_right_down &&
				!is_blocked_from_left_down
			) {
				block.shading.push_back(
					get_shading(front_corner_index)
				);
			}

			if (	block.is_visible &&
				!is_blocked_from_right &&
				!is_blocked_from_right_up
			) {
				block.shading.push_back(
					get_shading(right_light_index)
				);
			}

			if (	block.is_visible &&
				is_blocked_from_above_right_up
			) {
				block.shading.push_back(
					get_shading(top_shadow_index)
				);
			}
		}
	}
};
