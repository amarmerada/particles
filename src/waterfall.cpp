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
        renderer.blendMode(agl::BLEND);
        type.push_back("snow3");
        type.push_back("snow2");
        type.push_back("snow1");
        renderer.loadTexture("snow3", "../textures/snow3.png", 0);
        renderer.loadTexture("snow2", "../textures/water1.png", 0);
        renderer.loadTexture("snow1", "../textures/snow1.png", 0);
    }


    void createConfetti(int size, float zpos, vec3 color)
    {

        for (int i = 0; i < size; i++)
        {
            Particle particle;
            vec3 c = normalize(color + agl::randomUnitCube());
            vec3 random = agl::randomUnitCube();
            //particle.color = vec4(clamp(c.x, 0.3f, .5f), clamp(c.y, 0.7f, 1.0f), 1, 1);
            particle.color.x = color.x;
            particle.color.y = color.y;
            particle.color.z = color.z;
            particle.color.a = 1.0;
            particle.size = 0.15;
            particle.rot = 0.0;
            particle.pos = vec3(0, .75, zpos);
            particle.vel = agl::randomUnitCube();
            particle.vel.x = 0.0;
            particle.vel.z = particle.vel.z / 4;
            particle.vel.y -= 0.3;
            particle.tp = floor(clamp(random.x * 3, 0.0f, 2.0f));
            mParticles.push_back(particle);
        }
    }

    void updateConfetti(float dt)
    {
        for (int i = 0; i < mParticles.size(); i++)
        {
            mParticles[i].pos.y += mParticles[i].vel.y * dt;
            if (mParticles[i].pos.x < 1.0 && mParticles[i].pos.x > 0.0) {
                mParticles[i].pos.x += mParticles[i].vel.x * dt;
            }
            if (mParticles[i].pos.z < 5.0 && mParticles[i].pos.z > -5.0) {
                mParticles[i].pos.z += mParticles[i].vel.z * dt;
            }
            if (mParticles[i].vel.y > -1.0) {
                mParticles[i].vel.y -= 0.1;
            }
            if (mParticles[i].pos.y < -3.5) {
                mParticles.erase(mParticles.begin() + i);
            }
            
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
        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
        renderer.beginShader("sprite");
        if (mParticles.size() < 100000) {
            createConfetti(100, 0.5, vec3(0.8, 0.8, 1.0));
            createConfetti(100, 0.375, vec3(1.0, 1.0, 1.0));
            createConfetti(100, 0.25, vec3(0.8, 0.8, 1.0));
            createConfetti(100, 0.0, vec3(0.8, 0.8, 1.0));
            createConfetti(100, -0.25, vec3(0.8, 0.8, 1.0));
            createConfetti(100, -0.375, vec3(0.9, 0.9, 0.9));
            createConfetti(100, -0.5, vec3(0.8, 0.8, 1.0));
            vec3 rand = agl::randomUnitCube();
            posit.x += rand.x;
        }


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
