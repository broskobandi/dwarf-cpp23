export module tasks;

import sdl;
import std;
import init;
import ground;

using std::vector;
using std::size_t;
using std::uint32_t;

export struct Task {
	enum Type {
		NONE,
		STAND
	};
	Location location;
	FRect dstrect;
	Rect srcrect;
	size_t tex_id;
	uint32_t ticks_to_complete {0};
	Type type {NONE};
	uint32_t start_time {0};
	bool done {true};
};

export class Tasks : private game::TasksInitData {
private:
	vector<Task> tasks;
public:
	Tasks(
		TasksInitData init_data,
		size_t tex_id,
		const vector<Block>& blocks
	) :
		TasksInitData(init_data)
	{
		for (const auto& block : blocks) {
			tasks.push_back({
				.location = block.location,
				.dstrect = block.dstrect,
				.srcrect = {0, 0, img_size, img_size},
				.tex_id = tex_id
			});
		}
	}
	const vector<Task>& get_tasks() const {
		return tasks;
	}
	vector<Task>& get_tasks_mut() {
		return tasks;
	}
};
