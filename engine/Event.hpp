#pragma once
#include <Keys.hpp>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <any>
#include <renderer/Window.hpp>
#include <typeindex>
#include <Log.hpp>
#include <typeinfo>
#include <renderer/Renderer.hpp>
namespace H4_engine {

	struct BaseEvent
	{};


	class MessageBus
	{
		public:
			template<typename EventType>
			static void Subscribe(std::function<void(EventType&)> callback) {
				auto baseCallback = [func = std::move(callback)](BaseEvent& e)
				{
					func(static_cast<EventType&>(e));
				};
				callbacks[std::type_index(typeid(EventType))].push_back(baseCallback);
			}

			template <typename EventType, typename = std::enable_if_t<!std::is_pointer_v<EventType>>>
			static void Publish(EventType&& event) {
				auto type_id = std::type_index(typeid(event));
				if (callbacks.find(type_id) != callbacks.end()) {
					for (const auto& callback : callbacks[type_id]) {
						callback(event);
					}
				}
			}

		private:
			inline static std::unordered_map<std::type_index, std::vector<std::function<void(BaseEvent&)>>> callbacks;
	};


	struct EventMouseMoved : public BaseEvent
	{
		EventMouseMoved(const double new_x, const double new_y)
			: x(new_x)
			, y(new_y)
		{ }

		

		double x;
		double y;

	};

	class Renderer;
	struct EventRender : public BaseEvent
	{
		EventRender(Renderer *r)
			: renderer(r)
		{ }

		

		Renderer *renderer;
	};

	struct EventWindowResize : public BaseEvent
	{
		EventWindowResize(const unsigned int new_width, const unsigned int new_height)
			: width(new_width)
			, height(new_height)
		{}

		

		unsigned int width;
		unsigned int height;
	};
	struct EventMouseScroll : public BaseEvent
	{
		EventMouseScroll(const unsigned int new_y)
			: y(new_y)
		{}

		

		unsigned int y;
	};
	struct EventWindowClose : public BaseEvent
	{

	};
    struct EventKeyPressed : public BaseEvent
    {
        EventKeyPressed(const KeyCode key_code, const bool repeated)
            : key_code(key_code)
            , repeated(repeated)
        {
        }

        KeyCode key_code;
        bool repeated;

    };

    struct EventKeyReleased : public BaseEvent
    {
        EventKeyReleased(const KeyCode key_code)
            : key_code(key_code)
        {
        }

        KeyCode key_code;
    };
    struct EventMouseButtonPressed : public BaseEvent
    {
        EventMouseButtonPressed(const MouseButton mouse_button, const double x_pos, const double y_pos)
            : mouse_button(mouse_button)
            , x_pos(x_pos)
            , y_pos(y_pos)
        {
        }

        MouseButton mouse_button;
        double x_pos;
        double y_pos;
    };

    struct EventMouseButtonReleased : public BaseEvent
    {
        EventMouseButtonReleased(const MouseButton mouse_button, const double x_pos, const double y_pos)
            : mouse_button(mouse_button)
            , x_pos(x_pos)
            , y_pos(y_pos)
        {
        }

        MouseButton mouse_button;
        double x_pos;
        double y_pos;
    };
}
