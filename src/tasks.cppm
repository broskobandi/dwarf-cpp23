export module tasks;

import sdl;
import std;
import config;
import products;

using std::vector;
using std::size_t;
using std::uint32_t;

export class Tasks : private game::TasksConfig {
private:
	TasksProduct product;
public:
	Tasks(
		TasksConfig config,
		size_t tex_id,
		const GroundProduct& ground_product
	) :
		TasksConfig(config)
	{
		for (const auto& block : ground_product.blocks) {
			product.tasks.push_back({
				.location = block.location,
				.dstrect = block.dstrect,
				.hitbox {
					.x = block.dstrect.x +
						(block.dstrect.w -
						 hitbox_size) / 2,
					.y = block.dstrect.y + 1 + 
						block.dstrect.h / 2,
					.w = hitbox_size,
					.h = hitbox_size
				},
				.srcrect = {0, 0, img_size, img_size},
				.tex_id = tex_id
			});
		}
	}
	void update(
		const EntitiesProduct& entities_product,
		const GroundProduct& ground_product,
		Point mouse_pos,
		bool is_left_click, bool is_right_click, bool is_b_key
	) {
		size_t i = 0;
		for (auto& task : product.tasks) {
			task.is_visible = false;

			FPoint fmouse = {
				static_cast<float>(mouse_pos.x),
				static_cast<float>(mouse_pos.y)
			};
			const auto& block = ground_product.blocks.at(i);
			if (	block.is_selectable &&
				mouse_pos.x >= task.hitbox.x &&
				mouse_pos.x <= task.hitbox.x + task.hitbox.w &&
				mouse_pos.y >= task.hitbox.y &&
				mouse_pos.y <= task.hitbox.y + task.hitbox.h
			) {
				task.is_visible = true;
				task.srcrect.x = 1;
				std::println("{} {} {}",
					task.location.layer,
					task.location.row,
					task.location.col
				);
			}

			i++;
		}
	}
	const TasksProduct& get_product() const {
		return product;
	}
};
