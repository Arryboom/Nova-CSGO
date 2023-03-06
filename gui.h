#pragma once
#include "imgui/imgui.h"
#include <d3d9.h>

namespace gui {
	namespace config {
		namespace aimbot {
			inline bool master_switch = false;
		}

		namespace triggerbot {
			inline bool master_switch = false;
		}

		namespace esp {
			inline bool master_switch = false;
			inline int current_category = 0;

            // enemies
			inline bool enemy_name = false;
			inline float enemy_name_color[3] = { 1.f, 1.f, 1.f };
			inline bool enemy_box = false;
			inline float enemy_box_color[3] = { 1.f, 1.f, 1.f };
			inline bool enemy_health_bar = false;
			inline bool enemy_ammo_bar = false;
			inline float enemy_ammo_bar_color[3] = { 0.4f, 0.6f, 1.f };
			inline bool enemy_weapon_name = false;
			inline bool enemy_dormant = false;

			// teammates
			inline bool teammate_name = false;
			inline float teammate_name_color[3] = { 1.f, 1.f, 1.f };
			inline bool teammate_box = false;
			inline float teammate_box_color[3] = { 1.f, 1.f, 1.f };
			inline bool teammate_health_bar = false;
			inline bool teammate_ammo_bar = false;
			inline float teammate_ammo_bar_color[3] = { 0.4f, 0.6f, 1.f };
			inline bool teammate_weapon_name = false;
		}

		namespace visuals {
			inline int smoke_type = 0;
		}

		namespace misc {
			inline bool auto_jump = false;
			inline bool auto_fire = false;
			inline bool quick_stop = false;
			inline bool infinite_stamina = false;
		}
		
		namespace config {

		}
	};

	inline bool open = true;
	inline bool setup = false;
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};
	inline WNDPROC originalWindowProcess = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const char* windowClassName) noexcept;
	void DestroyWindowClass() noexcept;
	bool SetupWindow(const char* windowName) noexcept;
	void DestroyWindow() noexcept;
	bool SetupDirectX() noexcept;
	void DestroyDirectX() noexcept;

	void Setup();
	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;
	void Render() noexcept;
	void SetupStyle();
}