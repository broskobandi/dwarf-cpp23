import std;
import sdl2;

using std::runtime_error;
using std::println;
using std::cerr;
using sdl2::Sdl;
using sdl2::Dimensions;
using sdl2::Window;
using sdl2::Renderer;
using sdl2::Event;
using sdl2::KeyCode;

int main(void) {
	try {
		auto sdl = Sdl::init(Sdl::Flags::EVERYTHING);
		auto win = sdl->window("Dwarf", Dimensions{800, 600}, Window::Flags::SHOWN);
		auto ren = win->renderer(Renderer::Flags::PRESENTVSYNC);
		auto event = sdl->event();
		bool is_running = true;

		while (is_running) {
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
			}
			ren.clear({30, 70, 70, 255});
			ren.present();
		}

	} catch (const runtime_error& e) {
		println(cerr, "{}", e.what());
	}

	return 0;
}
