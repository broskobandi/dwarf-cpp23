export module game;

import std;
import sdl;
import ground;
import entities;
import tasks;
import products;
export import config;

namespace game {

using std::vector;
using std::uint32_t;
using std::int32_t;
using std::size_t;

void render_content(
	const Sdl& sdl,
	const GroundProduct& ground,
	const TasksProduct& tasks,
	const EntitiesProduct& entites
) {

	size_t i = 0;
	for (const auto& block : ground.blocks) {
		const Task& task = tasks.tasks.at(i);
		// for (const auto& entity : entities.get_entities()) {
		// 	if (entity.location == block.location) {
		// 		sdl.copy_ex_f(
		// 			entity.tex_id,
		// 			entity.srcrect,
		// 			entity.dstrect,
		// 			entity.is_flipped
		// 		);
		// 	}
		// }
		if (block.is_visible) {
			sdl.copy_f(
				block.tex_id,
				block.srcrect,
				block.dstrect
			);
			for (const auto& srcrect : block.shading) {
				sdl.copy_f(
					block.tex_id,
					srcrect,
					block.dstrect
				);
			}
		}
		if (task.is_visible) {
			sdl.copy_f(
				task.tex_id,
				task.srcrect,
				task.dstrect
			);
		}
		i++;
	}
}

export void run(
	GameConfig&& game_config,
	GroundConfig&& ground_config,
	TasksConfig&& tasks_config,
	EntitiesConfig&& entities_config
) {
	static bool has_game_run {false};

	if (has_game_run)
		throw std::runtime_error("Game cannot be run twice.");

	Sdl sdl(game_config);

	Ground ground(
		ground_config,
		sdl.texture(ground_config.path_to_bmp)
	);

	Tasks tasks(
		tasks_config,
		sdl.texture(tasks_config.path_to_bmp),
		ground.get_product()
	);

	Entities entities(
		entities_config,
		sdl.texture(entities_config.path_to_bmp),
		ground.get_product()
	);

	bool is_running {true};

	dbg("Entering main loop...");

	while (is_running) {
		bool is_left_click {false};
		bool is_right_click {false};
		bool is_b_key {false};

		while (sdl.poll_events()) {
			if (	sdl.has_type(EventType::QUIT) ||
				(sdl.has_type(EventType::KEYDOWN) &&
				 sdl.has_key(Key::q))
			) {
				is_running = false;
			}

			if (sdl.has_type(EventType::KEYDOWN)) {
				if (sdl.has_key(Key::b)) {
					is_b_key = true;
				}
			}
			if (sdl.has_left_button()) {
				is_left_click = true;
			}
			if (sdl.has_right_button()) {
				is_right_click = true;
			}
		}

		entities.update(
			tasks.get_product()
		);

		tasks.update(
			entities.get_product(),
			ground.get_product(),
			sdl.get_mouse_pos(),
			is_left_click, is_right_click, is_b_key
		);

		ground.update(
			tasks.get_product()
		);

		sdl.clear();
		
		render_content(
			sdl,
			ground.get_product(),
			tasks.get_product(),
			entities.get_product()
		);

		sdl.present();
	}

	dbg("Loop finished.");

	has_game_run = true;
}

}
