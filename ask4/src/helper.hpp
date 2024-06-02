#ifndef HELPER_H
#define HELPER_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SCALE_M(S) glm::vec3(S, S, S)

struct Allocator {
	std::vector<char *> allocations;

	~Allocator();
	char *allocate(size_t size);
	void freeAll();
};

enum Unum {
	ID0 = 0,
	ID1 = 1,
	ID2 = 2,
	ID3 = 3,
	ID4 = 4,
};

enum LightType {
	POSITIONAL,
	DIRECTIONAL
};

struct LightSources {
	LightType type;
	glm::vec3 position;
	glm::vec3 direction;
};

std::vector<int> getLightSrcIds(Unum num);
const char *f(Allocator& arena, const char *str, int id);


static const LightSources lightSrcsTable[] = {
	{ // ID = 0
		.type=POSITIONAL,
		.position=glm::vec3(2.3f, -3.3f, -4.0f),
		.direction=glm::vec3(0.0f, 0.0f, 0.0f)
	},
	{ // ID = 1
		.type=POSITIONAL,
		.position=glm::vec3(-3.0f, 1.0f, -10.0f),
		.direction=glm::vec3(0.0f, 0.0f, 0.0f)
	},
	{ // ID = 2
		.type=POSITIONAL,
		.position=glm::vec3(0.0f, 0.0f, -3.0f),
		.direction=glm::vec3(0.0f, 0.0f, 0.0f)
	},
	{ // ID = 3
		.type=POSITIONAL,
		.position=glm::vec3(3.4f, 4.0f, -14.0f),
		.direction=glm::vec3(0.0f, 0.0f, 0.0f)
	},
	{ // ID = 4
		.type=DIRECTIONAL,
		.position=glm::vec3(0.0f, 10.0f, -10.0f),
		.direction=glm::vec3(0.0f, -1.0f, 0.0f)
	},
	{ // ID = 5
		.type=DIRECTIONAL,
		.position=glm::vec3(0.0f, -10.0f, -10.0f),
		.direction=glm::vec3(0.0f, 1.0f, 0.0f)
	},
	{ // ID = 6
		.type=DIRECTIONAL,
		.position=glm::vec3(-10.0f, 10.0f, 10.0f),
		.direction=glm::vec3(1.0f, -1.0f, 0.0f)
	},
	{ // ID = 7
		.type=DIRECTIONAL,
		.position=glm::vec3(10.0f, 10.0f, -10.0f),
		.direction=glm::vec3(-1.0f, -1.0f, 0.0f)
	},
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

static const Material materials[] {
        // Emerald
        {
            glm::vec3(0.0215f, 0.1745f, 0.0215f),
            glm::vec3(0.07568f, 0.61424f, 0.07568f),
            glm::vec3(0.633f, 0.727811f, 0.633f),
            0.6f
        },
        // Jade
        {
            glm::vec3(0.135f, 0.2225f, 0.1575f),
            glm::vec3(0.54f, 0.89f, 0.63f),
            glm::vec3(0.316228f, 0.316228f, 0.316228f),
            0.1f
        },
        // Obsidian
        {
            glm::vec3(0.05375f, 0.05f, 0.06625f),
            glm::vec3(0.18275f, 0.17f, 0.22525f),
            glm::vec3(0.332741f, 0.328634f, 0.346435f),
            0.3f
        },
        // Pearl
        {
            glm::vec3(0.25f, 0.20725f, 0.20725f),
            glm::vec3(1.0f, 0.829f, 0.829f),
            glm::vec3(0.296648f, 0.296648f, 0.296648f),
            0.088f
        },
        // Ruby
        {
            glm::vec3(0.1745f, 0.01175f, 0.01175f),
            glm::vec3(0.61424f, 0.04136f, 0.04136f),
            glm::vec3(0.727811f, 0.626959f, 0.626959f),
            0.6f
        },
        // Turquoise
        {
            glm::vec3(0.1f, 0.18725f, 0.1745f),
            glm::vec3(0.396f, 0.74151f, 0.69102f),
            glm::vec3(0.297254f, 0.30829f, 0.306678f),
            0.1f
        },
        // Brass
        {
            glm::vec3(0.329412f, 0.223529f, 0.027451f),
            glm::vec3(0.780392f, 0.568627f, 0.113725f),
            glm::vec3(0.992157f, 0.941176f, 0.807843f),
            0.21794872f
        },
        // Bronze
        {
            glm::vec3(0.2125f, 0.1275f, 0.054f),
            glm::vec3(0.714f, 0.4284f, 0.18144f),
            glm::vec3(0.393548f, 0.271906f, 0.166721f),
            0.2f
        },
        // Chrome
        {
            glm::vec3(0.25f, 0.25f, 0.25f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.774597f, 0.774597f, 0.774597f),
            0.6f
        },
        // Copper
        {
            glm::vec3(0.19125f, 0.0735f, 0.0225f),
            glm::vec3(0.7038f, 0.27048f, 0.0828f),
            glm::vec3(0.256777f, 0.137622f, 0.086014f),
            0.1f
        },
        // Gold
        {
            glm::vec3(0.24725f, 0.1995f, 0.0745f),
            glm::vec3(0.75164f, 0.60648f, 0.22648f),
            glm::vec3(0.628281f, 0.555802f, 0.366065f),
            0.4f
        },
        // Silver
        {
            glm::vec3(0.19225f, 0.19225f, 0.19225f),
            glm::vec3(0.50754f, 0.50754f, 0.50754f),
            glm::vec3(0.508273f, 0.508273f, 0.508273f),
            0.4f
        },
        // Black Plastic
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.01f, 0.01f, 0.01f),
            glm::vec3(0.50f, 0.50f, 0.50f),
            0.25f
        },
        // Cyan Plastic
        {
            glm::vec3(0.0f, 0.1f, 0.06f),
            glm::vec3(0.0f, 0.50980392f, 0.50980392f),
            glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
            0.25f
        },
        // Green Plastic
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f, 0.35f, 0.1f),
            glm::vec3(0.45f, 0.55f, 0.45f),
            0.25f
        },
        // Red Plastic
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.5f, 0.0f, 0.0f),
            glm::vec3(0.7f, 0.6f, 0.6f),
            0.25f
        }
};

struct Attenuations {
	int distance;
	float linear;
};

static const Attenuations linearAttenMap[] = {
	{20, 0.22f},
	{32, 0.14f},
	{50, 0.09f},
	{65, 0.07f},
	{100, 0.045f}
};

struct CubeRotationAttribs {
	float RotationSpeed;
	float SpinSpeed;
	bool RotationToggle;
	bool SpinToggle;
	float RotationRadius;
	glm::vec3 scaleVec;
};
glm::mat4 updateModelTrans(CubeRotationAttribs attrb, glm::mat4 &rotationTrans, glm::mat4 &spinTrans, float deltaTime);

#endif // HELPER_H
