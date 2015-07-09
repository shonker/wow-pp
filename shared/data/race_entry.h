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

#pragma once

#include "templates/basic_template.h"
#include "game/action_button.h"
#include "data_load_context.h"

namespace wowpp
{
	struct ItemEntry;

	struct RaceEntry : BasicTemplate<UInt32>
	{
		typedef BasicTemplate<UInt32> Super;

		typedef std::vector<const ItemEntry*> InitialItemVector;
		typedef std::map<UInt32, InitialItemVector> GenderItemMap;
		typedef std::map<UInt32, GenderItemMap> ClassGenderItemMap;

		typedef std::vector<UInt16> InitialSpellIds;
		typedef std::map<UInt32, InitialSpellIds> InitialClassSpellMap;
		typedef std::map<UInt32, ActionButtons> InitialActionButtonsMap;

		String name;
		UInt32 factionID;
		UInt32 maleModel;
		UInt32 femaleModel;
		UInt32 baseLanguage;		//7 = Alliance	1 = Horde
		UInt32 startingTaxiMask;
		UInt32 cinematic;
		InitialClassSpellMap initialSpells;
		InitialActionButtonsMap initialActionButtons;
		ClassGenderItemMap initialItems;		// initialItems[class][gender][item_index]
		UInt32 startMap;
		UInt32 startZone;
		std::array<float, 3> startPosition;
		float startRotation;

		RaceEntry();
		bool load(DataLoadContext &context, const ReadTableWrapper &wrapper);
		void save(BasicTemplateSaveContext &context) const;
	};
}
