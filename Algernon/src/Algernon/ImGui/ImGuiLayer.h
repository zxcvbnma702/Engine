#pragma once

#include "Algernon/Core/Layer.h"
#include <Algernon/Event/MouseEvent.h>
#include <Algernon/Event/KeyEvent.h>
#include <Algernon/Event/ApplicationEvent.h>

namespace Algernon {

	class ALGERNON_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		//virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}

