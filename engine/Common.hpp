#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
namespace H4_engine
{
    static double get_time()
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() / (double)1000;
    }
    struct Vertex
    {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 normal;
        Vertex(glm::vec3 pos, glm::vec2 uv, glm::vec3 normal)
            : pos(pos), uv(uv), normal(normal) {}
        Vertex(glm::vec3 pos, glm::vec2 uv)
            : pos(pos), uv(uv) {}
        Vertex(glm::vec3 pos)
            : pos(pos) {}
    };
    struct Triangle
    {
        Triangle(Vertex p1, Vertex p2, Vertex p3)
            : p1(p1), p2(p2), p3(p3) {}
        Vertex p1, p2, p3;
    };
    static glm::mat4 GenerateModelMatrix(glm::vec3 position, glm::vec3 scale)
    {
        glm::mat4 scale_matrix(scale.x, 0, 0, 0,
                               0, scale.y, 0, 0,
                               0, 0, scale.z, 0,
                               0, 0, 0, 1);
        float rotate_in_radians = glm::radians(0.0f);
        glm::mat4 rotate_matrix(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
        glm::mat4 translate_matrix(1, 0, 0, 0,
                                   0, 1, 0, 0,
                                   0, 0, 1, 0,
                                   position.x, position.y, position.z, 1);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, position);
        return trans;
    }

    static bool FileExists(const std::string &abs_filename)
	{
		bool ret;
		FILE *fp = fopen(abs_filename.c_str(), "rb");
		if (fp)
		{
			ret = true;
			fclose(fp);
		}
		else
		{
			ret = false;
		}

		return ret;
	}

	static std::string GetBaseDir(const std::string &filepath)
	{
		if (filepath.find_last_of("/\\") != std::string::npos)
			return filepath.substr(0, filepath.find_last_of("/\\"));
		return "";
	}

    static glm::vec3 vec3_zero = glm::vec3(0);
}