#include <glbinding/gl45core/gl.h>
#include <glbinding/Binding.h>

#pragma warning(suppress: 4251)

int main()
{
	glbinding::Binding::initialize(false);
	return 0;
}