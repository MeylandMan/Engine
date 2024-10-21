#pragma once

#include <renderer/renderer.h>
#include <iostream>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender(Renderer& renderer) {}
		virtual void onImGUI() {}
	};
}