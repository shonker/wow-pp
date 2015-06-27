//
// This file is part of the WoW++ project.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Genral Public License as published by
// the Free Software Foudnation; either version 2 of the Licanse, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// World of Warcraft, and all World of Warcraft or Warcraft art, images,
// and lore are copyrighted by Blizzard Entertainment, Inc.
// 

#include "player_social.h"
#include "player.h"


namespace wowpp
{
	PlayerSocial::PlayerSocial(PlayerManager &manager, Player &player)
		: m_manager(manager)
		, m_player(player)
	{
	}

	PlayerSocial::~PlayerSocial()
	{
	}

	game::FriendResult PlayerSocial::addToSocialList(UInt64 guid, bool ignore)
	{
		// Build flags
		UInt32 flag = (ignore ? game::social_flag::Ignored : game::social_flag::Friend);

		// Check if this contact is already in the social list
		auto it = m_contacts.find(guid);
		if (it != m_contacts.end())
		{
			if (it->second.flags == flag)
			{
				return (ignore ? game::friend_result::IgnoreAlreadyAdded : game::friend_result::AlreadyAdded);
			}
			else
			{
				// Change the flags (remove from friend list, add to ignore list and vice versa)
				it->second.flags = flag;
			}
		}
		else
		{
			ILOG("Adding new friend!");

			// Couldn't find the specified contact - add him
			game::SocialInfo info;
			info.flags = flag;
			m_contacts[guid] = std::move(info);
			
			// Just a little check to be absolutely sure....
			DLOG("Check if the new friend IS a friend: " << isFriend(guid));
		}

		// Successfully added / switched mode
		return (ignore ? game::friend_result::IgnoreAdded : game::friend_result::AddedOffline);
	}

	void PlayerSocial::removeFromSocialList(UInt64 guid, bool ignore)
	{
		//TODO
	}

	void PlayerSocial::setFriendNote(UInt64 guid, String note)
	{
		//TODO
	}

	void PlayerSocial::sendSocialList() const
	{
		//TODO
	}

	bool PlayerSocial::isFriend(UInt64 guid) const
	{
		// Find the friend info
		auto it = m_contacts.find(guid);
		if (it == m_contacts.end())
		{
			return false;
		}

		// Check the flags
		return (it->second.flags == game::social_flag::Friend);
	}

	bool PlayerSocial::isIgnored(UInt64 guid) const
	{
		// Find the friend info
		auto it = m_contacts.find(guid);
		if (it == m_contacts.end())
		{
			return false;
		}

		// Check the flags
		return (it->second.flags != game::social_flag::Friend);
	}
}
