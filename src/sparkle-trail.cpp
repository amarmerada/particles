// Bryn Mawr College, alinen, 2020
//

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
    float rot;
    float size;
    float time;
};

class Viewer : public Window {
public:
    Viewer() : Window() {
    }

    void setup() {
        setWindowSize(1000, 1000);
        //createConfetti(500); 
        renderer.setDepthTest(false);
        renderer.blendMode(agl::ADD);
        srand(time(0));
    }

    void createConfetti(int size)
    {
        renderer.loadTexture("particle", "../textures/star4.png", 0);
        for (int i = 0; i < size; i++) {
            Particle particle;
            particle.color = vec4(agl::randomUnitCube(), 0.7);
            particle.size = 0.25;
            particle.rot = 0 ;//0.0;
            particle.pos = position;
            particle.vel = vec3(position.y, -position.x, 0) + agl::randomUnitCube();
            particle.time = glfwGetTime();
            mParticles.push_back(particle);
        }
    }

    void updateConfetti()
    {
        std::vector<Particle> altParticles;
        for (Particle p : mParticles) {
            float deltaTime = glfwGetTime() - p.time;
            p.pos += (deltaTime * p.vel * (float)0.1);
            p.rot += clamp((float)rand(), 0.0f, 1.0f);;
            p.color.a = p.color.a * 0.99;
            p.size += 0.005;
            if ((glfwGetTime() - p.time) > 3) { 
                p.color.a = 0.70;
                p.pos = position;
                p.time = glfwGetTime();
                p.rot = 0;
                p.size = (0.25);
                p.vel = vec3(position.y, -position.x, 0) +  agl::randomUnitCube();
            }
 
            altParticles.push_back(p);

        }
        mParticles.clear();
        mParticles = altParticles;
    }

    void drawConfetti()
    {
        renderer.texture("image", "particle");
        for (int i = 0; i < mParticles.size(); i++) {
            Particle particle = mParticles[i];
            renderer.sprite(particle.pos, particle.color, particle.size, particle.rot);
        }
    }

    void mouseMotion(int x, int y, int dx, int dy) {

        //position.x += dx * 0.001;
        //position.y -= dy * 0.001;
    }

    void mouseDown(int button, int mods) {
        click = true;
    }

    void mouseUp(int button, int mods) {
        click = false;
    }

    void scroll(float dx, float dy) {
        eyePos.z += dy;
    }

    void keyUp(int key, int mods) {
    }

    void draw() {
        if (mParticles.size() < 500) {
            createConfetti(1);
        }
        renderer.beginShader("sprite");
        i += 0.023;
        if (i > 6.28) {
            i = i - 6.28;
        }
        position.x = cos(i);
        position.y = sin(i);

        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);

        renderer.lookAt(eyePos, lookPos, up);
        renderer.sprite(position, vec4(1.0f), 0.2f); //1.0
        updateConfetti();
        drawConfetti();
        renderer.endShader();


        // remove for obj pool
        /**if (mParticles.size() == 500) {
            mParticles.erase(mParticles.begin(), mParticles.begin() + 1);
        }*/
    }

protected:

    vec3 eyePos = vec3(0, 0, 3);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    bool click = false;
    vec3 position = vec3(1, 0, 0);
    double lastTime = 0;
    float i = 0;

    std::vector<Particle> mParticles;
};

int main(int argc, char** argv)
{
    Viewer viewer;
    printf("beginning\n");
    viewer.run();
    return 0;
}