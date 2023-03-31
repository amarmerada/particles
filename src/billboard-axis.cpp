// Bryn Mawr College, alinen, 2020
//

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"

using namespace std;
using namespace glm;
using namespace agl;

class Viewer : public Window {
public:
  Viewer() : Window() {
  }

  void setup() {
    setWindowSize(1000, 1000);
    renderer.loadShader("simple-texture",
      "../shaders/simple-texture.vs",
      "../shaders/simple-texture.fs");

    Image img;
    img.load("../textures/tree.png", true);
    renderer.loadTexture("tree", img, 0);
    // TODO: Use the width and the height of the image to scale the billboard
    int h = img.height();
    int w = img.width();
    ratio = (float)h / (float)w;
    renderer.loadTexture("grass", "../textures/grass.png", 0);
    renderer.blendMode(agl::BLEND);
  }


  void mouseMotion(int x, int y, int dx, int dy) {
      if (click) {
          ele = ele - (dy * 0.05);
          if (ele > 6.283) {
              ele = 0;
          }
          if (ele < 0) {
              ele = 6.283;
          }
          az = az - (dx * 0.05);
          if (az < -3.1415) {
              az = 3.1415;
          }
          if (az > 3.1415) {
              az = -3.1415;
          }

          float x = radius * cos(az) * sin(ele);
          float y = radius * cos(ele);
          float z = radius * sin(az) * sin(ele);
          eyePos = vec3(x, y, z);
      }
  }

  void mouseDown(int button, int mods) {
      click = true;
  }

  void mouseUp(int button, int mods) {
      click = false;
  }

  void scroll(float dx, float dy) {
      radius = radius + dx - dy;
      float x = radius * cos(az) * sin(ele);
      float y = radius * cos(ele);
      float z = radius * sin(az) * sin(ele);
      eyePos = vec3(x, y, z);
  }

  void draw() {
    renderer.beginShader("simple-texture");

    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
    renderer.lookAt(eyePos, lookPos, up);
    renderer.setUniform("ratio", ratio);

    // draw plane
    renderer.texture("Image", "grass");
    renderer.push();
    renderer.translate(vec3(0.0, -0.5, 0));
    renderer.scale(vec3(2.0));
    renderer.plane();
    renderer.pop();

    // draw tree
    renderer.texture("Image", "tree");
    renderer.push();
    vec3 dir = normalize(eyePos - lookPos);
    renderer.rotate(atan2(dir.x, dir.z), vec3(0.0, 1.0, 0.0));
    renderer.translate(vec3(-0.5, -0.5, 0));
    renderer.scale(vec3(1, ratio, 1));
    renderer.quad(); // vertices span from (0,0,0) to (1,1,0)
    renderer.pop();

    renderer.endShader();
  }

protected:

  vec3 eyePos = vec3(0, 0, 2);
  vec3 lookPos = vec3(0, 0, 0);
  bool click = false;
  vec3 up = vec3(0, 1, 0);
  float ele = 0;
  float az = 0;
  float radius = 10;
  float ratio;
};

int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
