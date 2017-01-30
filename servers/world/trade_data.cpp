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

#include "pch.h"
#include "trade_data.h"
#include "game/game_creature.h"
#include "game_protocol/game_protocol.h"
#include "player.h"
#include "game/game_world_object.h"


namespace wowpp
{	
	TradeData::TradeData(Player &player, Player &trader)
		: m_initiator(player)
		, m_other(trader)
	{
	}

	void TradeData::openWindows()
	{
		m_initiator.sendTradeStatus(game::trade_status::OpenWindow);
		m_other.sendTradeStatus(game::trade_status::OpenWindow);
	}

	void TradeData::cancel()
	{
		m_initiator.sendTradeStatus(game::trade_status::TradeCanceled);
		m_other.sendTradeStatus(game::trade_status::TradeCanceled);

		// Resetting the trade session field for both player instances will destroy this
		// instance
		m_initiator.setTradeSession(nullptr);
		m_other.setTradeSession(nullptr);
	}

	void TradeData::setGold(Trader index, UInt32 gold)
	{
		assert(index > Trader::Count_);

		// Update gold value and acceptance state
		m_data[index].gold = gold;

		// Send data
		sendTradeData(index);

		// Refresh trade state
		setAcceptedState(Owner, false);
		setAcceptedState(Target, false);
	}

	void TradeData::setAcceptedState(Trader index, bool accept)
	{
		assert(index > Trader::Count_);

		bool wasAccepted = m_data[index].accepted;
		if (accept == wasAccepted)
			return;

		m_data[index].accepted = accept;

		// If no more accepted, send back to trade
		if (wasAccepted)
		{
			// Notify both players about the cancellation
			m_initiator.sendTradeStatus(game::trade_status::BackToTrade);
			m_other.sendTradeStatus(game::trade_status::BackToTrade);
			return;
		}
		else
		{
			Player *target = (index == Owner ? &m_other : &m_initiator);
			assert(target);

			// Did both accept?
			if (m_data[Owner].accepted && m_data[Target].accepted)
			{
				// TODO: Do the trade

				// Get both characters
				auto ownerChar = m_initiator.getCharacter();
				assert(ownerChar);
				auto otherChar = m_other.getCharacter();
				assert(otherChar);

				const UInt32 ownerMoney = ownerChar->getUInt32Value(character_fields::Coinage);
				const UInt32 otherMoney = otherChar->getUInt32Value(character_fields::Coinage);

				// Perform some checks, some of them again
				{
					// Check owner gold
					if (ownerMoney < m_data[Owner].gold)
						return;

					// Check other gold
					if (otherMoney < m_data[Target].gold)
						return;
				}
				
				// Perform gold trade
				{
					// Increment gold values
					ownerChar->setUInt32Value(character_fields::Coinage, ownerMoney - m_data[Owner].gold + m_data[Target].gold);
					otherChar->setUInt32Value(character_fields::Coinage, otherMoney - m_data[Target].gold + m_data[Owner].gold);
				}
				
				// Finalize trade, which will close the trade window on both clients
				m_initiator.sendTradeStatus(game::trade_status::TradeComplete);
				m_other.sendTradeStatus(game::trade_status::TradeComplete);

				// Destroy this trade session
				m_initiator.setTradeSession(nullptr);
				m_other.setTradeSession(nullptr);
			}
			else
			{
				// Notify the other client about the acceptance
				target->sendTradeStatus(game::trade_status::TradeAccept);
			}
		}
	}

	void TradeData::setItem(Trader index, UInt8 tradeSlot, ItemPtr item)
	{
		assert(index > Trader::Count_);
		assert(tradeSlot < MaxTradeSlots);

		// First remove that item from any other trade slot where it eventually is
		if (item != nullptr)
		{
			for (auto &oldItem : m_data[index].items)
			{
				if (oldItem && oldItem->getGuid() == item->getGuid())
				{
					oldItem = nullptr;
				}
			}
		}
		
		// Now set the new one
		m_data[index].items[tradeSlot] = item;

		// Send new items to other client
		sendTradeData(index);

		// Reset trade state
		setAcceptedState(Owner, false);
		setAcceptedState(Target, false);
	}
	void TradeData::sendTradeData(Trader index)
	{
		// Send data
		auto formatter = std::bind(game::server_write::sendUpdateTrade, std::placeholders::_1,
			1,
			0,
			MaxTradeSlots,
			MaxTradeSlots,
			m_data[index].gold,
			0,
			std::cref(m_data[index].items));
		if (index == Owner)
		{
			m_other.sendProxyPacket(formatter);
		}
		else
		{
			m_initiator.sendProxyPacket(formatter);
		}
	}
}
