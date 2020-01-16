#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto len = 10;
	for (int radius = 0; radius < 100; radius += len) {

		auto noise_location = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int deg = 0; deg < 360; deg += 1) {

			int index = this->face.getNumVertices();

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0)));
			vertices.push_back(glm::vec3(glm::vec3((radius + len) * cos(deg * DEG_TO_RAD), (radius + len) * sin(deg * DEG_TO_RAD), 0)));
			vertices.push_back(glm::vec3(glm::vec3((radius + len) * cos((deg + 1) * DEG_TO_RAD), (radius + len) * sin((deg + 1) * DEG_TO_RAD), 0)));
			vertices.push_back(glm::vec3(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0)));

			auto angle_x = ofMap(ofNoise(noise_location.x, cos(deg * DEG_TO_RAD) * 0.3, ofGetFrameNum() * 0.001), 0, 1, 0, PI * 2);
			auto angle_y = ofMap(ofNoise(noise_location.y, sin(deg * DEG_TO_RAD) * 0.3, ofGetFrameNum() * 0.001), 0, 1, 0, PI * 2);
			auto angle_z = ofMap(ofNoise(noise_location.z, ofGetFrameNum() * 0.0035), 0, 1, 0, PI);

			auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

			vertices[0] = glm::vec4(vertices[0], 0) * rotation_z * rotation_y * rotation_x;
			vertices[1] = glm::vec4(vertices[1], 0) * rotation_z * rotation_y * rotation_x;

			angle_x = ofMap(ofNoise(noise_location.x, cos((deg + 1) * DEG_TO_RAD) * 0.3, ofGetFrameNum() * 0.001), 0, 1, 0, PI * 2);
			angle_y = ofMap(ofNoise(noise_location.y, sin((deg + 1) * DEG_TO_RAD) * 0.3, ofGetFrameNum() * 0.001), 0, 1, 0, PI * 2);

			rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			
			vertices[2] = glm::vec4(vertices[2], 0) * rotation_z * rotation_y * rotation_x;
			vertices[3] = glm::vec4(vertices[3], 0) * rotation_z * rotation_y * rotation_x;

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.25);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}