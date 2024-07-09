#pragma once
#include <Common.hpp>
#include <components/Component.hpp>
#include <renderer/VertexArray.hpp>
#include <renderer/VertexBuffer.hpp>
#include <vector>
#include <Event.hpp>
#include <renderer/MeshVAO.hpp>
#include <components/Transform.hpp>
#include <components/Camera.hpp>

namespace H4_engine
{
	class CameraController : public Component
	{
		public:
			DECLARE_COMPONENT(CameraController);
			CameraController(Entity *entity);
			void start();
			void tick();
		private:
			Camera *m_camera;
			double m_initial_mouse_pos_x = 0.0;
			double m_initial_mouse_pos_y = 0.0;
			bool m_cameraRotating = false;
	};
	REGISTER_COMPONENT(CameraController);
}
