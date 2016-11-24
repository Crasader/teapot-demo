#pragma once

// C++ Headers
#include <Windows.h>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <chrono>
#include <memory>
#include <utility>

// OpenGL Headers
#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#define GLM_FORCE_RADIANS
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/quaternion.hpp"

#include "SOIL.h"

// Program Headers
#include "Debug.h"
#include "Event.h"
#include "EventManager.h"
#include "GLWindow.h"
#include "GLContext.h"
#include "Timer.h"
#include "InputHandler.h"
#include "Clamp.h"
#include "BoundingBox.h"
#include "Color4F.h"
#include "Position.h"
#include "Transform.h"
#include "Camera.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Light.h"
#include "Renderer.h"
#include "Shader.h"
#include "FileManager.h"
#include "State.h"
#include "TeapotDemo.h"
