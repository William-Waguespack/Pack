#pragma once

#include "Pack/Layer.h"
#include "Pack/Events/MouseEvents.h"
#include "Pack/Events/KeyEvent.h"
#include "Pack/Events/ApplicationEvent.h"

namespace Pack
{
	class PACK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}


