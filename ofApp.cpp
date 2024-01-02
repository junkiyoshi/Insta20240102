#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 1.44);

	string word = "HAPPY NEW YEAR 2024 !";
	int sample_count = 180;
	auto noise_param = ofRandom(1000);

	for (int i = 0; i < word.size(); i++) {

		ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
				auto rotation_y = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				auto noise_value = ofNoise(location.x * 0.005, ofGetFrameNum() * 0.01);
				auto param_y = 0;
				if (noise_value < 0.5) {

					param_y = -100;
					if (noise_value > 0.4) {

						param_y = ofMap(noise_value, 0.4, 0.5, -100, 0);
					}
				}
				else
				{
					param_y = 100;
					if (noise_value < 0.6) {

						param_y = ofMap(noise_value, 0.5, 0.6, 0, 100);
					}
				}

				location = location + glm::vec3(0, param_y, 0);
				ofVertex(location);
			}
		}
		ofEndShape();

		ofNoFill();
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
			for (auto& vertex : vertices) {

				auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
				auto rotation_y = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				location = glm::vec4(location, 0) * rotation_y;

				auto noise_value = ofNoise(location.x * 0.005, ofGetFrameNum() * 0.01);
				auto param_y = 0;
				if (noise_value < 0.5) {

					param_y = 100;
					if (noise_value > 0.4) {

						param_y = ofMap(noise_value, 0.4, 0.5, 100, 0);
					}
				}
				else
				{
					param_y = -100;
					if (noise_value < 0.6) {

						param_y = ofMap(noise_value, 0.5, 0.6, 0, -100);
					}
				}

				location = location + glm::vec3(0, param_y, 0);
				ofVertex(location);
			}
		}
		ofEndShape();
	}

	this->cam.end();

	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}