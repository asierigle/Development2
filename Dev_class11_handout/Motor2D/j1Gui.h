#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes
class UI_Element
{
public:
	UI_Element(SDL_Rect position, SDL_Rect collider) : position(position), collider(collider), parent(NULL){}
	bool Update(float dt);
	virtual bool PersonalUpdate(float dt);
	virtual void Draw() {}
	SDL_Rect position;
private:
	SDL_Rect collider;
	UI_Element* parent;
	p2DynArray<UI_Element*> childs;
	p2List<j1Module*> listeners;
	bool active;
	int layer;

};

class UI_Rect : public UI_Element
{
public:
	

private:
	int r, g, b, a;
};


class UI_Label : public UI_Element
{
public:
	void SetText(char* text, int r, int g, int b);
	void SetColor(int r, int g, int b);
private:
	p2SString text;
	SDL_Texture* texture;
	int r, g, b;
};

class UI_Image : public UI_Element
{
public:
	UI_Image(SDL_Texture* texture, SDL_Rect rect, SDL_Rect position, SDL_Rect collider) : UI_Element(position, collider), texture(texture), rect(rect){}
	void Draw();
private:
	SDL_Texture* texture;
	SDL_Rect rect;
};

class UI_InputText : public UI_Element
{
public:
	void GetNewInput(char* text);
	p2SString GetString();


private:
	UI_Label text;
	p2List<char> textList;
	int MaxCharacters;
};

class UI_Button : public UI_Element
{
public:
	void GetCurrentRect(int index);

private:
	SDL_Texture* texture;
	SDL_Rect rect[3];
};

class UI_Collapse : public UI_Button
{
public:

private:
	UI_Element* linkedElement;
	bool changed;
};

class UI_Bar : public UI_Element
{
public:

private:
	SDL_Rect rect;
	int* maxData, currentData;
	SDL_Texture* texture;
};




// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UI_Image* CreateUI_Image(SDL_Texture* texture, SDL_Rect rect, SDL_Rect position, SDL_Rect collider = { 0, 0, 0, 0 });

	UI_Label* CreateUI_Label(SDL_Rect position, SDL_Texture* texture, char* text, int r, int g, int b, SDL_Rect collider = { 0,0,0,0 });

	UI_Rect* CreateUI_Rect(SDL_Rect position, int r, int g, int b, SDL_Rect collider);

	UI_Button* CreateUI_Button(SDL_Rect position, char* path, p2DynArray<SDL_Rect> rect, SDL_Rect collider);


	SDL_Texture* GetAtlas() const;
private:

	void SendNewInput(char* text);
	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<UI_Element*> UI_Elements;
	UI_Element* focus;
	
};

#endif // __j1GUI_H__