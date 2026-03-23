#pragma once

#define OFFSET(offset, name, ...) __VA_ARGS__& name() { return *(__VA_ARGS__*)(std::uintptr_t(this) + offset); }

struct spotify_track_meta_t
{
	struct wrapper_spotify_track_t
	{
		virtual void function0() = 0;
		virtual void function1() = 0;
		virtual void function2() = 0;
		virtual void function3() = 0;
		virtual void function4() = 0;
		virtual void function5() = 0;
		virtual void function6() = 0;
		virtual bool is_ad_track() = 0;

		OFFSET(0x50, track_title_array, std::array<char, 16>);
		OFFSET(0x50, track_title_ptr, const char*);
		OFFSET(0x60, track_title_length, std::int16_t)

		std::string get_track_title()
		{
			if(track_title_length() >= 16)
			{
				return track_title_array().data();
			}

			return track_title_ptr();
		}
	};
	wrapper_spotify_track_t* m_wrapped;

	// @note: contains string "spotify:ad:ffffffffffffffffffffffffffffffff"
	OFFSET(0xE0, track_uri, const char*);
};