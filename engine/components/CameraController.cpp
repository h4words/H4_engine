#include <components/CameraController.hpp>
#include <Common.hpp>
#include <Log.hpp>
#include <Input.hpp>
#include <stb_image.h>
#include <unordered_map>
#include <algorithm>
#include <vector>
namespace H4_engine
{
	CameraController::CameraController(Entity *entity)
		: Component(entity) { }

	void CameraController::start()
	{
		m_camera = m_entity->get_component<Camera>();
	}

	void CameraController::tick()
	{
		glm::vec3 movement_delta{0};
		glm::vec3 rotation_delta{0};
		if (Input::IsKeyPressed(KeyCode::KEY_W))
		{
			movement_delta.z += 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_S))
		{
			movement_delta.z -= 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_A))
		{
			movement_delta.x -= 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_D))
		{
			movement_delta.x += 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_E))
		{
			movement_delta.y += 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_Q))
		{
			movement_delta.y -= 0.05f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_UP))
		{
			rotation_delta.x -= 0.5f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_DOWN))
		{
			rotation_delta.x += 0.5f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_RIGHT))
		{
			rotation_delta.y -= 0.5f;
		}
		if (Input::IsKeyPressed(KeyCode::KEY_LEFT))
		{
			rotation_delta.y += 0.5f;
		}
		if (Input::IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT))
		{
			int mouseX;
			int mouseY;
			SDL_GetGlobalMouseState(&mouseX, &mouseY);

			if (!m_cameraRotating)
			{
				m_initial_mouse_pos_x = mouseX;
				m_initial_mouse_pos_y = mouseY;
				m_cameraRotating = true;
			}
			if (Input::IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
			{
				m_camera->move_right(static_cast<float>(mouseX - m_initial_mouse_pos_x) / 100.f);
				m_camera->move_up(static_cast<float>(m_initial_mouse_pos_y - mouseY) / 100.f);
			}
			else
			{
				rotation_delta.y += static_cast<float>(mouseX - m_initial_mouse_pos_x) / 5.f;
				rotation_delta.x += static_cast<float>(m_initial_mouse_pos_y - mouseY) / 5.f;
			}
			m_initial_mouse_pos_x = mouseX;
			m_initial_mouse_pos_y = mouseY;
		}
		else
		{
			m_cameraRotating = false;
		}
		m_camera->add_movement_and_rotation(movement_delta, rotation_delta);
	}
}
