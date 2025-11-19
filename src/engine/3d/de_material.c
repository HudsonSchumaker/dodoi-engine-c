/**
* @file de_material.c
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "../../include/de_material.h"

material_t material_init(void) {
	material_t material;
	material.ambient = vec3_new(0.0f, 0.0f, 0.0f);
	material.diffuse = vec3_new(0.0f, 0.0f, 0.0f);
	material.specular = vec3_new(0.0f, 0.0f, 0.0f);
	material.shininess = 0.0f;
	return material;
}

material_t* material_new(vec3_t ambient, vec3_t diffuse, vec3_t specular, float shininess) {
	material_t* material = (material_t*)malloc(sizeof(material_t));
	if (material == NULL) {
		fprintf(stderr, "failed to allocate memory for material.\n");
		exit(EXIT_FAILURE);
	}
	material->ambient = ambient;
	material->diffuse = diffuse;
	material->specular = specular;
	material->shininess = shininess;
	return material;
}

material_t material_emerald(void) {
    return (material_t) {
        .ambient = vec3_new(0.0215f, 0.1745f, 0.0215f),
        .diffuse = vec3_new(0.07568f, 0.61424f, 0.07568f),
        .specular = vec3_new(0.633f, 0.727811f, 0.633f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_jade(void) {
    return (material_t) {
        .ambient = vec3_new(0.135f, 0.2225f, 0.1575f),
        .diffuse = vec3_new(0.54f, 0.89f, 0.63f),
        .specular = vec3_new(0.316228f, 0.316228f, 0.316228f),
        .shininess = 0.1f * 128.0f
    };
}

material_t material_obsidian(void) {
    return (material_t) {
        .ambient = vec3_new(0.05375f, 0.05f, 0.06625f),
        .diffuse = vec3_new(0.18275f, 0.17f, 0.22525f),
        .specular = vec3_new(0.332741f, 0.328634f, 0.346435f),
        .shininess = 0.3f * 128.0f
    };
}

material_t material_pearl(void) {
    return (material_t) {
        .ambient = vec3_new(0.25f, 0.20725f, 0.20725f),
        .diffuse = vec3_new(1.0f, 0.829f, 0.829f),
        .specular = vec3_new(0.296648f, 0.296648f, 0.296648f),
        .shininess = 0.088f * 128.0f
    };
}

material_t material_ruby(void) {
    return (material_t) {
        .ambient = vec3_new(0.1745f, 0.01175f, 0.01175f),
        .diffuse = vec3_new(0.61424f, 0.04136f, 0.04136f),
        .specular = vec3_new(0.727811f, 0.626959f, 0.626959f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_turquoise(void) {
    return (material_t) {
        .ambient = vec3_new(0.1f, 0.18725f, 0.1745f),
        .diffuse = vec3_new(0.396f, 0.74151f, 0.69102f),
        .specular = vec3_new(0.297254f, 0.30829f, 0.306678f),
        .shininess = 0.1f * 128.0f
    };
}

material_t material_brass(void) {
    return (material_t) {
        .ambient = vec3_new(0.329412f, 0.223529f, 0.027451f),
        .diffuse = vec3_new(0.780392f, 0.568627f, 0.113725f),
        .specular = vec3_new(0.992157f, 0.941176f, 0.807843f),
        .shininess = 0.21794872f * 128.0f
    };
}

material_t material_bronze(void) {
    return (material_t) {
        .ambient = vec3_new(0.2125f, 0.1275f, 0.054f),
        .diffuse = vec3_new(0.714f, 0.4284f, 0.18144f),
        .specular = vec3_new(0.393548f, 0.271906f, 0.166721f),
        .shininess = 0.2f * 128.0f
    };
}

material_t material_chrome(void) {
    return (material_t) {
        .ambient = vec3_new(0.25f, 0.25f, 0.25f),
        .diffuse = vec3_new(0.4f, 0.4f, 0.4f),
        .specular = vec3_new(0.774597f, 0.774597f, 0.774597f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_copper(void) {
    return (material_t) {
        .ambient = vec3_new(0.19125f, 0.0735f, 0.0225f),
        .diffuse = vec3_new(0.7038f, 0.27048f, 0.0828f),
        .specular = vec3_new(0.256777f, 0.137622f, 0.086014f),
        .shininess = 0.1f * 128.0f
    };
}

material_t material_gold(void) {
    return (material_t) {
        .ambient = vec3_new(0.24725f, 0.1995f, 0.0745f),
        .diffuse = vec3_new(0.75164f, 0.60648f, 0.22648f),
        .specular = vec3_new(0.628281f, 0.555802f, 0.366065f),
        .shininess = 0.4f * 128.0f
    };
}

material_t material_silver(void) {
    return (material_t) {
        .ambient = vec3_new(0.19225f, 0.19225f, 0.19225f),
        .diffuse = vec3_new(0.50754f, 0.50754f, 0.50754f),
        .specular = vec3_new(0.508273f, 0.508273f, 0.508273f),
        .shininess = 0.4f * 128.0f
    };
}

material_t material_black_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.01f, 0.01f, 0.01f),
        .specular = vec3_new(0.5f, 0.5f, 0.5f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_cyan_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.1f, 0.06f),
        .diffuse = vec3_new(0.0f, 0.50980392f, 0.50980392f),
        .specular = vec3_new(0.50196078f, 0.50196078f, 0.50196078f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_green_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.1f, 0.35f, 0.1f),
        .specular = vec3_new(0.45f, 0.55f, 0.45f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_red_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.5f, 0.0f, 0.0f),
        .specular = vec3_new(0.7f, 0.6f, 0.6f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_white_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.55f, 0.55f, 0.55f),
        .specular = vec3_new(0.7f, 0.7f, 0.7f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_yellow_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.5f, 0.5f, 0.0f),
        .specular = vec3_new(0.6f, 0.6f, 0.5f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_black_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.02f, 0.02f, 0.02f),
        .diffuse = vec3_new(0.01f, 0.01f, 0.01f),
        .specular = vec3_new(0.4f, 0.4f, 0.4f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_cyan_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.05f, 0.05f),
        .diffuse = vec3_new(0.4f, 0.5f, 0.5f),
        .specular = vec3_new(0.04f, 0.7f, 0.7f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_green_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.05f, 0.0f),
        .diffuse = vec3_new(0.4f, 0.5f, 0.4f),
        .specular = vec3_new(0.04f, 0.7f, 0.04f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_red_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.05f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.5f, 0.4f, 0.4f),
        .specular = vec3_new(0.7f, 0.04f, 0.04f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_white_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.05f, 0.05f, 0.05f),
        .diffuse = vec3_new(0.5f, 0.5f, 0.5f),
        .specular = vec3_new(0.7f, 0.7f, 0.7f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_yellow_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.05f, 0.05f, 0.0f),
        .diffuse = vec3_new(0.5f, 0.5f, 0.4f),
        .specular = vec3_new(0.7f, 0.7f, 0.04f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_polished_bronze(void) {
    return (material_t) {
        .ambient = vec3_new(0.25f, 0.148f, 0.06475f),
        .diffuse = vec3_new(0.4f, 0.2368f, 0.1036f),
        .specular = vec3_new(0.774597f, 0.458561f, 0.200621f),
        .shininess = 0.4f * 128.0f
    };
}

material_t material_polished_copper(void) {
    return (material_t) {
        .ambient = vec3_new(0.2295f, 0.08825f, 0.0275f),
        .diffuse = vec3_new(0.5508f, 0.2118f, 0.066f),
        .specular = vec3_new(0.580594f, 0.223257f, 0.0695701f),
        .shininess = 0.4f * 128.0f
    };
}

material_t material_polished_gold(void) {
    return (material_t) {
        .ambient = vec3_new(0.24725f, 0.1995f, 0.0745f),
        .diffuse = vec3_new(0.75164f, 0.60648f, 0.22648f),
        .specular = vec3_new(0.628281f, 0.555802f, 0.366065f),
        .shininess = 0.4f * 128.0f
    };
}

material_t material_polished_silver(void) {
    return (material_t) {
        .ambient = vec3_new(0.23125f, 0.23125f, 0.23125f),
        .diffuse = vec3_new(0.2775f, 0.2775f, 0.2775f),
        .specular = vec3_new(0.773911f, 0.773911f, 0.773911f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_pewter(void) {
    return (material_t) {
        .ambient = vec3_new(0.105882f, 0.058824f, 0.113725f),
        .diffuse = vec3_new(0.427451f, 0.470588f, 0.541176f),
        .specular = vec3_new(0.333333f, 0.333333f, 0.521569f),
        .shininess = 0.21794872f * 128.0f
    };
}

material_t material_rubber(void) {
    return (material_t) {
        .ambient = vec3_new(0.02f, 0.02f, 0.02f),
        .diffuse = vec3_new(0.01f, 0.01f, 0.01f),
        .specular = vec3_new(0.4f, 0.4f, 0.4f),
        .shininess = 0.078125f * 128.0f
    };
}

material_t material_plastic(void) {
    return (material_t) {
        .ambient = vec3_new(0.0f, 0.0f, 0.0f),
        .diffuse = vec3_new(0.01f, 0.01f, 0.01f),
        .specular = vec3_new(0.5f, 0.5f, 0.5f),
        .shininess = 0.25f * 128.0f
    };
}

material_t material_polished_emerald(void) {
    return (material_t) {
        .ambient = vec3_new(0.0215f, 0.1745f, 0.0215f),
        .diffuse = vec3_new(0.07568f, 0.61424f, 0.07568f),
        .specular = vec3_new(0.633f, 0.727811f, 0.633f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_polished_jade(void) {
    return (material_t) {
        .ambient = vec3_new(0.135f, 0.2225f, 0.1575f),
        .diffuse = vec3_new(0.54f, 0.89f, 0.63f),
        .specular = vec3_new(0.316228f, 0.316228f, 0.316228f),
        .shininess = 0.1f * 128.0f
    };
}

material_t material_polished_obsidian(void) {
    return (material_t) {
        .ambient = vec3_new(0.05375f, 0.05f, 0.06625f),
        .diffuse = vec3_new(0.18275f, 0.17f, 0.22525f),
        .specular = vec3_new(0.332741f, 0.328634f, 0.346435f),
        .shininess = 0.3f * 128.0f
    };
}

material_t material_polished_pearl(void) {
    return (material_t) {
        .ambient = vec3_new(0.25f, 0.20725f, 0.20725f),
        .diffuse = vec3_new(1.0f, 0.829f, 0.829f),
        .specular = vec3_new(0.296648f, 0.296648f, 0.296648f),
        .shininess = 0.088f * 128.0f
    };
}

material_t material_polished_ruby(void) {
    return (material_t) {
        .ambient = vec3_new(0.1745f, 0.01175f, 0.01175f),
        .diffuse = vec3_new(0.61424f, 0.04136f, 0.04136f),
        .specular = vec3_new(0.727811f, 0.626959f, 0.626959f),
        .shininess = 0.6f * 128.0f
    };
}

material_t material_polished_turquoise(void) {
    return (material_t) {
        .ambient = vec3_new(0.1f, 0.18725f, 0.1745f),
        .diffuse = vec3_new(0.396f, 0.74151f, 0.69102f),
        .specular = vec3_new(0.297254f, 0.30829f, 0.306678f),
        .shininess = 0.1f * 128.0f
    };
}
