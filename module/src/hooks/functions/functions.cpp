#include "functions.hpp"


#include "sdk/track.hpp"

std::uint64_t hooked_functions::create_track(std::uint64_t a1, std::uint64_t player_meta,
	spotify_track_meta_t* track_meta, double speed, unsigned int normalization, int urgency,
	unsigned int track_select_flag, std::uint64_t a8, unsigned int a9, std::uint64_t start_position_ms,
	std::uint64_t seek_to_creator_timestamp, std::uint64_t a12, std::uint64_t a13)
{
	bool is_ad = track_meta->m_wrapped->is_ad_track();
#ifdef _DEBUG
	std::printf("[create_track] track: %s (uri: %s) is_ad: %s\n", track_meta->m_wrapped->get_track_title().data(), track_meta->track_uri(), is_ad ? "yes" : "no");
#endif

	// @note: speed up the track when ad is present
	if(is_ad)
	{
		speed = 30.f;
	}

	return o_create_track(a1, player_meta, track_meta, speed, normalization, urgency, track_select_flag, a8, a9, start_position_ms, seek_to_creator_timestamp, a12, a13);
}
