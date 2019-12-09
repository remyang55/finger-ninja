#include "ofApp.h"
#include "ofMain.h"

constexpr int kMaxX = 1024;
constexpr int kMaxY = 768;

int main() {
  ofSetupOpenGL(kMaxX, kMaxY, OF_WINDOW);
  ofRunApp(new ofApp());
}
