//
// This file is part of the WoW++ project.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
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

#pragma once

#include "common/typedefs.h"
#include "templates/basic_template.h"
#include <array>
#include <map>

namespace wowpp
{
	struct LevelEntry : BasicTemplate<UInt32>
	{
		typedef BasicTemplate<UInt32> Super;

		typedef std::array<UInt32, 5> StatArray;
		typedef std::map<UInt32, StatArray> ClassStatMap;
		typedef std::map<UInt32, ClassStatMap> RaceClassMap;

		typedef std::array<float, 2> RegenArray;
		typedef std::map<UInt32, RegenArray> ClassRegenMap;

		// Note: id is the level value (1 - 70) here for compatiblity reasons
		UInt32 nextLevelXP;
		UInt32 explorationBaseXP;
		RaceClassMap stats;
		ClassRegenMap regen;

		LevelEntry();
		bool load(BasicTemplateLoadContext &context, const ReadTableWrapper &wrapper);
		void save(BasicTemplateSaveContext &context) const;
	};
}
