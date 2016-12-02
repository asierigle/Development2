#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

//Update of UI_Elements
bool UI_Element::Update(float dt)
{
	if (active == true)
		PersonalUpdate(dt);
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (int i = 0; i < UI_Elements.count(); i++)
		delete UI_Elements[i];
	return true;
}

UI_Image * j1Gui::CreateUI_Image( SDL_Texture * texture, SDL_Rect rect, SDL_Rect position, SDL_Rect collider)
{
	UI_Image* image = new UI_Image( texture, rect, position, collider);
	UI_Elements.add(image);
	return image;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void UI_Image::Draw()
{
	App->render->Blit(texture,position.x, position.y, )
}
