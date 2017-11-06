#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

class p2String;
// ----------------------------------------------------

enum LayerTypes
{
	BACKGROUND = 0,
	BACKGROUND_SPIKES_1,
	BACKGROUND_SPIKES_2,
	LAVA,
	GROUND_1,
	GROUND_2,
	LOGIC,
	COLLISIONS,

	LAYER_NOT_DEF
};

enum TileSetTypes
{
	PLATFORM = 0,
	FLAG,
	

	TILESET_NOT_DEF
};

struct MapLayer {

	p2SString name = nullptr;
	uint width = 0; //number of tiles in the x axis
	uint height = 0; //number of tiles in the y axis

	uint* data = nullptr;
	uint size_data = 0;

	LayerTypes layer_type = LAYER_NOT_DEF;

	~MapLayer() {
		RELEASE(data);
	}

	inline uint Get(int x, int y) const;
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;

	TileSetTypes		tileset_type = TILESET_NOT_DEF;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*> layers;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;

	iPoint WorldToMap(int x, int y) const;

	void setAllLogicForMap();
	void LayersSetUp();


private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:

	MapData data;
	p2SString sceneName;
	iPoint spawn;

	//for comodity c:
	MapLayer* collisionLayer;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__