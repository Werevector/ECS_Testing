#pragma once
#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <iostream>
#include <fstream>

using namespace std;

class MetaFileReader {
public:
	static vector<SDL_Rect*> readSpriteMetaPositions(string filepath) {
		fstream metaFile(filepath);
		vector<SDL_Rect*> result;

		if (metaFile.is_open()) {

			int x, y, w, h;
			

			while (metaFile >> x >> y >> w >> h) {
				SDL_Rect* spriteRect = new SDL_Rect();
				spriteRect->x = x;
				spriteRect->y = y;
				spriteRect->w = w;
				spriteRect->h = h;

				result.push_back(spriteRect);

			}

		}
		else {
			cout << "Could not open metafile " << filepath << endl;
		}
		return result;
	}
};