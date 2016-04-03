#pragma once
#include <vector>
#include <string>

class vec2 {
public:
	vec2() : x(0), y(0) {};
	vec2(float x, float y) : x(x), y(y) {};

	float x;
	float y;
};

class rgba {
public:
	rgba() : r(0), g(0), b(0), a(0) {};
	rgba(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};

	int r;
	int g;
	int b;
	int a;
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class KeySequence {
public:
	int GetNextKey() {

		int returnkey;
		returnkey = sequence[index];

		if (index == sequence.size() - 1) {
			if (isPlayOnce) {
				index = sequence.size() - 1;
			}
			else {
				index = 0;
			}

		}
		else
			index++;

		return returnkey;
	}

	void setSequence(std::vector<int> seq) {
		sequence = seq;
	}
	void setName(std::string name) {
		seq_name = name;
	}

	void restartSequence() {
		index = 0;
	}

	std::string getSequenceName() { return seq_name; }

	KeySequence() {

	}

	KeySequence(std::vector<int> seq, std::string name) {
		sequence = seq;
		seq_name = name;
	}
	bool isPlayOnce = false;

private:
	std::string seq_name = "";
	std::vector<int> sequence;
	int index;
};

//The animation of a character in it's sprite should be read as extra meta data
//but is hard-coded for now
class Animation {
public:
	
	int GetAnimationKey() {
		return current_key;
	}

	void Tick() {
		if (frame >= framerate) {
			current_key = key_sequences[current_sequence].GetNextKey();
			frame = 0;
		}
		else {
			frame++;
		}
	}

	void setTickPerUpdate(int rate) {
		framerate = rate;
	}

	bool readAnimationFile(std::string filepath) {
		return false;
	}

	bool changeSequence(std::string name) {
		bool found = false;
		for (int i = 0; i < key_sequences.size(); i++) {
			if (key_sequences[i].getSequenceName().compare(name) == 0) {
				current_sequence = i;
				resetSequence();
				current_key = key_sequences[current_sequence].GetNextKey();
				found = true;
				break;
			}
		}
		return found;
	}

	bool createTestAnimation() {
		std::vector<int> vec =	{ 0,1,2,3,2,1,0 };
		std::vector<int> vec2 = { 4,5,6,7,8,9,10,11 };
		std::vector<int> vec3 = { 24,26,27,28,29,30,31 };
		std::vector<int> vec4 = { 16,17,18,19,20,21,22,23,24 };
		std::vector<int> jump = { 32,33,34,35,36,37,38,39 };
		std::vector<int> air =	{ 39 };

		KeySequence seq(vec, "Idle");
		key_sequences.push_back(seq);
		KeySequence seq2(vec2, "Running");
		key_sequences.push_back(seq2);
		KeySequence seq3(vec3, "Walking");
		key_sequences.push_back(seq3);
		KeySequence seq4(vec4, "Dying");
		key_sequences.push_back(seq4);
		KeySequence seq5(jump, "Jump");
		seq5.isPlayOnce = true;
		key_sequences.push_back(seq5);
		KeySequence seq6(air, "Air");
		
		key_sequences.push_back(seq6);

		return true;
	}
	SDL_RendererFlip flip = SDL_FLIP_NONE;

private:
	int current_key = 0;
	int current_sequence = 0;

	std::vector<KeySequence> key_sequences;
	int framerate = 10;
	int frame = 0;

	void resetSequence() {
		key_sequences[current_sequence].restartSequence();
	}
};

namespace EntityState {
	enum Movement{
		IDLE,
		WALKING,
		RUNNING,
		JUMP
	};
}