module game;

import sdl2;
import canvas;
import tiles;

import std;

using sdl2::Sdl;
using sdl2::Dimensions;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Event;
using sdl2::KeyCode;
using sdl2::Texture;
using std::vector;

void Game::run() {

	auto sdl = Sdl::init(Sdl::Flags::EVERYTHING);
	auto win =sdl->window(
		"Dwarf", Dimensions{800, 600}, Window::Flags::SHOWN
	);
	auto event = sdl->event();
	bool is_running = true;

	Canvas canvas(win);

	Tiles tiles(
		canvas.create_texture("../assets/ground3.bmp"),
		canvas.create_texture("../assets/ground3-shadow.bmp"),
		128,
		128 / 2,
		600 / (128 / 4),
		800 / 128,
		128 / 4,
		2,
		128 / 4
	);

	while (is_running) {
		bool left_click = false;
		while (event.poll()) {
			if (
				event.type() == Event::Type::QUIT ||
				(
					event.type() == Event::Type::KEYDOWN &&
					event.keycode() == KeyCode::q
				)
			) {
				is_running = false;
			}
			if (
				event.type() == Event::Type::MOUSEBUTTONDOWN &&
				event.mouse().left
			) {
				left_click = true;
			}
		}

		tiles.update({event.mouse().x, event.mouse().y}, left_click);

		canvas.clear({30, 70, 70, 255});

		canvas.draw(tiles.render_data());
		// canvas.draw(tiles.hitboxes_render_data());

		canvas.present();
	}

}
