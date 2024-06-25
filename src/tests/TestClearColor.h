#include "../src/tests/Test.h"

namespace test {
	class TestClearColor : public Test {

	public:
		TestClearColor();
		~TestClearColor();

		virtual void onUpdate(float deltaTime) override;
		virtual void onRender(GLFWwindow* window, mat4 _view, mat4 _proj) override;
		virtual void onImGUIRender() override;
	private:
		float m_ClearColor[4];
	};
}