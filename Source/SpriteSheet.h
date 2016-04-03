#pragma once
#include <vector>
#include <SDL.h>
#include "Texture.h"
#include "metafilereader.h"

class SpriteSheet {
public:
	std::vector<SDL_Rect*> sheetRectangles;
	Texture textureSheet;
	
	bool loadSpriteSheet(std::string imagepath, std::string metapath, SDL_Renderer* renderer) {
		bool success = true;

		
		if (textureSheet.loadFromFile(renderer, imagepath)) {
			sheetRectangles = MetaFileReader::readSpriteMetaPositions(metapath);
			if (sheetRectangles.size() == 0) {
				success = false;
			}
		}
		else {
			success = false;
		}

		return success;
	}

	void renderSpriteAtKey(SDL_Renderer* renderer, int x, int y ,int key, SDL_Rect* target, double angle, SDL_RendererFlip flip ) {
		
		SDL_Rect* clip = sheetRectangles[key];

		textureSheet.renderALTER(
			renderer,
			x,
			y,
			clip,
			target,
			angle,
			NULL,
			flip
			);
	}

};