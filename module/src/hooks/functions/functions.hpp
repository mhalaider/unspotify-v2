#pragma once

struct spotify_track_meta_t;

#define DECLARE_OG(func) inline decltype(&func) o_##func = nullptr;

namespace hooked_functions
{
	std::uint64_t __fastcall create_track(
		std::uint64_t a1, std::uint64_t player_meta, spotify_track_meta_t* track_meta, double speed, unsigned int normalization,
		int urgency, unsigned int track_select_flag, std::uint64_t a8, unsigned int a9, std::uint64_t start_position_ms,
		std::uint64_t seek_to_creator_timestamp, std::uint64_t a12, std::uint64_t a13);
	DECLARE_OG(create_track);

}
