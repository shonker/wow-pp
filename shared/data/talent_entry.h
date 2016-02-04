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

#include "templates/basic_template.h"

namespace wowpp
{
	struct DataLoadContext;
	struct SpellEntry;

	struct TalentEntry : BasicTemplate<UInt32>
	{
		typedef BasicTemplate<UInt32> Super;

		UInt32 tab;
		UInt32 row;
		UInt32 column;
		std::vector<const SpellEntry*> ranks;
		const TalentEntry *dependsOn;
		UInt32 dependsOnRank;
		const SpellEntry *dependsOnSpell;

		TalentEntry();
		bool load(DataLoadContext &context, const ReadTableWrapper &wrapper);
		void save(BasicTemplateSaveContext &context) const;
	};
}
