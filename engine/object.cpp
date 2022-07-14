#include "object.h"

namespace engine
{
    base_object_t::base_object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color
	)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->color = color;
		if (texture_path != "")
			this->set_texture_path(texture_path);
	}

	base_object_t::base_object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color,
		const char *texture_path
	) : base_object_t(hitbox, position, color)
	{
		this->texture_path = texture_path;
	}

	base_object_t::~base_object_t ()
	{
		if (this->texture != nullptr)
			SDL_DestroyTexture(this->texture);
	}

	bool base_object_t::load_texture(SDL_Renderer *renderer)
	{
		return false;
	}

	object_t::object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color,
		float mass
	) : base_object_t(hitbox, position, color)
	{
		this->velocity = vector_t(0, 0);
		this->mass = mass;
	}

	object_t::object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
		float mass,
		const char *texture_path
	) : base_object_t(hitbox, position, color, texture_path)
	{
		this->velocity = vector_t(0, 0);
		this->mass = mass;
	}

	bool object_t::load_texture (SDL_Renderer *renderer)
	{
		if (this->texture_path != "" && renderer != nullptr) {
			SDL_Surface *surface = SDL_LoadBMP(this->texture_path.c_str());
			if (surface == nullptr)
				return false;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr)
				return false;
			
			if (this->texture != nullptr)
				SDL_DestroyTexture(this->texture);
			SDL_FreeSurface(surface);
			this->texture = texture;
			return true;
		}

		return false;
	}

	ui_text_t::ui_text_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
		const char *texture_path,
		const char *message
	) : base_object_t(hitbox, position, color, texture_path)
	{
		this->message = message;
	}

	bool ui_text_t::load_texture (SDL_Renderer *renderer)
	{
		 if (this->texture_path != "" && renderer != nullptr) {
            TTF_Font *font = TTF_OpenFont(this->texture_path.c_str(), 24);

            if (!font) {
                return false;
            }

            SDL_Surface *surface = TTF_RenderText_Solid(font, this->message.c_str(), {255,255,255});

            if (surface == nullptr)
                return false;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (texture == nullptr)
                return false;

            if (this->texture != nullptr)
                SDL_DestroyTexture(this->texture);
            SDL_FreeSurface(surface);
            this->texture = texture;
            return true;
        }

		return false;
	}
}
