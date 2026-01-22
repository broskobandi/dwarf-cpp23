export module entities;

import config;
import sdl;
import std;
import products;

using std::vector;
using std::size_t;
using std::uint32_t;
using std::rand;

export class Entities : private game::EntitiesConfig {
private:
	EntitiesProduct product;
public:
	Entities(
		game::EntitiesConfig config,
		size_t tex_id,
		const GroundProduct& ground_product
	) :
		EntitiesConfig(config)
	{
		std::srand(static_cast<uint32_t>(std::time(nullptr)));

		vector<Location> locations;

		for (size_t i = 0; i < num_entities; i++) {
			Location location {};
			do {
				location.layer = spawn_layer;
				location.row = spawn_row +
					static_cast<size_t>(std::rand()) %
					spawn_area;
				location.col = spawn_col +
					static_cast<size_t>(std::rand()) %
					spawn_area;
			} while (location.has_equal_in(locations));
			locations.push_back(location);
		}

		for (const auto& block : ground_product.blocks) {
			for (const auto& location : locations) {
				if (location != block.location) continue;
				float x =
					block.dstrect.x +
					static_cast<float>((block.dstrect.w -
					 entity_size) / 2);
				float y =
					block.dstrect.y +
					static_cast<float>((block.dstrect.h -
					 entity_size) / 2);
				float w = entity_size;
				float h = entity_size;
				FRect dstrect {
					x, y, w, h
				};
				Rect srcrect {
					0, 0, img_size, img_size
				};
				product.entities.push_back(
					Entity(
						dstrect,
						srcrect,
						tex_id,
						location
					)
				);
			}
			
		}
	}

	void update(const TasksProduct& tasks_product) {
		for (auto& entity : product.entities) {

			bool has_task = false;
			Location task_location {};
			float target_x {};
			float target_y {};

			for (const auto& task : tasks_product.tasks) {
				if (task.type != Task::NONE) {
					has_task = true;
					task_location = task.location;
					target_x =
						task.dstrect.x +
						(task.dstrect.w -
						 entity_size) / 2;
					target_y =
						task.dstrect.y +
						(task.dstrect.h -
						 entity_size) / 2;
					if (	entity.dstrect.x ==
						target_x &&
						entity.dstrect.y ==
						target_y
					) {
						entity.location = task.location;
						// entity.location.layer++;
					}
					break;
				}
			}

			if (has_task) {

				enum Direction {
					RIGHT	= 1 << 0,
					LEFT	= 1 << 1,
					DOWN	= 1 << 2,
					UP	= 1 << 3
				};

				Direction direction {RIGHT};

				float x_speed = 0;
				float y_speed = 0;

				if (	entity.dstrect.x >
					target_x + pixels_per_frame
				) {
					// entity.dstrect.x -= pixels_per_frame;
					x_speed -= pixels_per_frame;
					direction = static_cast<Direction>(
						static_cast<int>(direction) |
						LEFT);
				}
					
				if (	entity.dstrect.x <
					target_x - pixels_per_frame
				) {
					// entity.dstrect.x += pixels_per_frame;
					x_speed += pixels_per_frame;
					direction = static_cast<Direction>(
						static_cast<int>(direction) |
						RIGHT);
				}		
					
				if (	entity.dstrect.y >
					target_y + pixels_per_frame
				) {
					// entity.dstrect.y -= pixels_per_frame;
					y_speed -= pixels_per_frame;
					direction = static_cast<Direction>(
						static_cast<int>(direction) |
						UP);
				}

				if (	entity.dstrect.y <
					target_y - pixels_per_frame
				) {
					// entity.dstrect.y += pixels_per_frame;
					y_speed += pixels_per_frame;
					direction = static_cast<Direction>(
						static_cast<int>(direction) |
						DOWN);
				}

				if (	(direction & UP &&
					 direction & RIGHT) ||
					(direction & UP &&
					 direction & LEFT) ||
					(direction & DOWN &&
					 direction & RIGHT) ||
					(direction & DOWN &&
					 direction & LEFT)
				) {
					x_speed *= 0.7f;
					y_speed *= 0.7f;
				}
				
				entity.dstrect.x += x_speed;
				entity.dstrect.y += y_speed;

				if (	std::fabs(entity.dstrect.x - target_x) <
					pixels_per_frame
				) {
					entity.dstrect.x = target_x;
				}

				if (	std::fabs(entity.dstrect.y - target_y) <
					pixels_per_frame
				) {
					entity.dstrect.y = target_y;
				}

			}
		}

	}

	const EntitiesProduct& get_product() const {
		return product;
	}
};
