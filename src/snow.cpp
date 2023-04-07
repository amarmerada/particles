#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

struct Particle {
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec4 color;
    float size;
    float rot;
    float startTime;
    int tp;
    float rs;
};

class Viewer : public Window {
public:
    Viewer() : Window() {
    }

    void setup() {
        setWindowSize(1000, 1000);
        renderer.setDepthTest(false);
        renderer.blendMode(agl::ADD);
        type.push_back("snow3");
        type.push_back("snow2");
        type.push_back("snow1");

        renderer.loadTexture("snow3", "../textures/snow3.png", 0);
        renderer.loadTexture("snow2", "../textures/snow2.png", 0);
        renderer.loadTexture("snow1", "../textures/snow1.png", 0);
    }


    void createConfetti(int size)
    {

        for (int i = 0; i < size; i++)
        {
            Particle particle;
            vec3 c = normalize(vec3(0.8, 0.8, 1) + agl::randomUnitCube());
            particle.color = vec4(clamp(c.x, 0.7f, 1.0f), clamp(c.y, 0.7f, 1.0f), 1, 1);
            particle.size = 0.25;
            particle.rot = 0.0;
            vec3 random = agl::randomUnitCube();
            posit.z += random.z;
            particle.rs = random.y;
            particle.pos = posit;
            particle.pos.y = 10;
            particle.pos.x = clamp((random.z + 0.12f) * 10, -10.0f, 10.0f);
            particle.vel = agl::randomUnitCube();
            particle.vel.y = -1.0;
            particle.tp = rand() % 3;
            mParticles.push_back(particle);
        }
    }

    void updateConfetti(float dt)
    {
        for (int i = 0; i < mParticles.size(); i++)
        {
            Particle particle = mParticles[i];
            if (particle.pos.y > -10)
            {
                particle.pos += particle.vel * dt;
                vec3 rand = agl::randomUnitCube();
                posit.z += rand.z;
                if (posit.z > 10 || posit.z < -10) posit.z = 0;
                particle.rot += particle.rs;
            }
            else {
            }
            mParticles[i] = particle;
        }
    }

    void drawConfetti()
    {
        vec3 cameraPos = renderer.cameraPosition();

        // sort
        for (int i = 1; i < mParticles.size(); i++)
        {
            Particle particle1 = mParticles[i];
            Particle particle2 = mParticles[i - 1];
            float dSqr1 = length2(particle1.pos - cameraPos);
            float dSqr2 = length2(particle2.pos - cameraPos);
            if (dSqr2 < dSqr1)
            {
                mParticles[i] = particle2;
                mParticles[i - 1] = particle1;
            }
        }

        // draw



        for (int i = 0; i < mParticles.size(); i++)
        {
            Particle particle = mParticles[i];
            renderer.texture("image", type[particle.tp]);
            renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
        }
    }

    void mouseMotion(int x, int y, int dx, int dy) {
    }

    void mouseDown(int button, int mods) {
    }

    void mouseUp(int button, int mods) {
    }

    void scroll(float dx, float dy) {
        eyePos.x += dy;
    }

    void keyUp(int key, int mods) {
    }

    void draw() {
        renderer.lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
        renderer.beginShader("sprite");
        if (posit.x > 2 || posit.x < -2) posit.x = 0;
        if (posit.y > 2 || posit.y < -2) posit.y = 0;
        if (posit.z > 3 || posit.z < -3) posit.z = 0;
        if (mParticles.size() < 100000) {
            createConfetti(100);
            vec3 rand = agl::randomUnitCube();
            posit.x += rand.x;
        }

        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

        renderer.lookAt(eyePos, lookPos, up);
        updateConfetti(dt());
        drawConfetti();
        renderer.endShader();
    }

protected:

    vec3 eyePos = vec3(10, 0, 0);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    vec3 posit = vec3(1, 3, 2);
    std::vector<string> type;
    int thing = 0;
    std::vector<Particle> mParticles;
    float thresh;
};

int main(int argc, char** argv)
{
    Viewer viewer;
    viewer.run();
    return 0;
}
