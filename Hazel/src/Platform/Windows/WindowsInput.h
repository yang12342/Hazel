#pragma once
#include "Hazel/Input.h"

//��ѯ���ƴ����¼���ȡ

namespace Hazel
{
	class WindowsInput :public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int key) override;

		virtual bool IsMouseButtonPressedImpl(int button)override;
		virtual std::pair<float, float> GetMousePositionImpl()override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl()override;
		
	};
}

