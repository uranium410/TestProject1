#pragma once

namespace GameObjects {
	class GameObject {
	public:
		virtual void Update()=0;
		virtual void DrawUpdate()=0;
	};
}