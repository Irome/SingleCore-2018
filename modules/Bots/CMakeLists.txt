#
# Copyright (C) 2005-2012 MaNGOS project <http://getmangos.com/>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

#Add PCH Files
file(GLOB_RECURSE sources_playerbot playerbot/*.cpp playerbot/*.h)
file(GLOB_RECURSE sources_pch *.cpp *.h)
    
#Define base source library
set(bot_STAT_SRCS
  ${bot_STAT_SRCS}  
  ${sources_playerbot}
  ${sources_pch}
)

include_directories(
  ${game_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/playerbot
  ${CMAKE_SOURCE_DIR}/modules/worldengine/deps/recastnavigation/Detour
  ${CMAKE_SOURCE_DIR}/modules/worldengine/deps/recastnavigation/Recast
  ${CMAKE_SOURCE_DIR}/modules/worldengine/deps/g3dlite/include
  ${CMAKE_SOURCE_DIR}/modules/worldengine/deps/SFMT
  ${CMAKE_SOURCE_DIR}/modules/worldengine/deps/zlib
  ${CMAKE_SOURCE_DIR}/modules/worldengine/lib-collision/src/
  ${CMAKE_SOURCE_DIR}/modules/worldengine/lib-collision/src/Management
  ${CMAKE_SOURCE_DIR}/modules/worldengine/lib-collision/src/Models
  ${CMAKE_SOURCE_DIR}/modules/worldengine/lib-collision/src/Maps
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Configuration
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Cryptography
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Cryptography/Authentication
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Database
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/DataStores
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Debugging
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Dynamic/LinkedReference
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Dynamic
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Logging
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Packets
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Threading
  ${CMAKE_SOURCE_DIR}/modules/worldengine/nucleus/src/Utilities
  ${CMAKE_SOURCE_DIR}/modules/acore/game-framework/src/Addons
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src/game/Accounts
  ${CMAKE_SOURCE_DIR}/src/game/Achievements
  ${CMAKE_SOURCE_DIR}/src/game/AI
  ${CMAKE_SOURCE_DIR}/src/game/AI/CoreAI
  ${CMAKE_SOURCE_DIR}/src/game/AI/ScriptedAI
  ${CMAKE_SOURCE_DIR}/src/game/AI/SmartScripts
  ${CMAKE_SOURCE_DIR}/src/game/AuctionHouse
  ${CMAKE_SOURCE_DIR}/src/game/Battlefield
  ${CMAKE_SOURCE_DIR}/src/game/Battlefield/Zones
  ${CMAKE_SOURCE_DIR}/src/game/Battlegrounds
  ${CMAKE_SOURCE_DIR}/src/game/Battlegrounds/Zones
  ${CMAKE_SOURCE_DIR}/src/game/Calendar
  ${CMAKE_SOURCE_DIR}/src/game/Chat
  ${CMAKE_SOURCE_DIR}/src/game/Chat/Channels
  ${CMAKE_SOURCE_DIR}/src/game/Combat
  ${CMAKE_SOURCE_DIR}/src/game/Conditions
  ${CMAKE_SOURCE_DIR}/src/game/DataStores
  ${CMAKE_SOURCE_DIR}/src/game/DungeonFinding
  ${CMAKE_SOURCE_DIR}/src/game/Entities
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Creature
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Corpse
  ${CMAKE_SOURCE_DIR}/src/game/Entities/DynamicObject
  ${CMAKE_SOURCE_DIR}/src/game/Entities/GameObject
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Item
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Item/Container
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Object
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Object/Updates
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Pet
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Player
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Totem
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Unit
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Vehicle
  ${CMAKE_SOURCE_DIR}/src/game/Entities/Transport
  ${CMAKE_SOURCE_DIR}/src/game/Events
  ${CMAKE_SOURCE_DIR}/src/game/Globals
  ${CMAKE_SOURCE_DIR}/src/game/Grids/Cells
  ${CMAKE_SOURCE_DIR}/src/game/Grids/Notifiers
  ${CMAKE_SOURCE_DIR}/src/game/Grids
  ${CMAKE_SOURCE_DIR}/src/game/Groups
  ${CMAKE_SOURCE_DIR}/src/game/Guilds
  ${CMAKE_SOURCE_DIR}/src/game/Handlers
  ${CMAKE_SOURCE_DIR}/src/game/Instances
  ${CMAKE_SOURCE_DIR}/src/game/Loot
  ${CMAKE_SOURCE_DIR}/src/game/Mails
  ${CMAKE_SOURCE_DIR}/src/game/Maps
  ${CMAKE_SOURCE_DIR}/src/game/Miscellaneous
  ${CMAKE_SOURCE_DIR}/src/game/Movement
  ${CMAKE_SOURCE_DIR}/src/game/Movement/Spline
  ${CMAKE_SOURCE_DIR}/src/game/Movement/MovementGenerators
  ${CMAKE_SOURCE_DIR}/src/game/Movement/Waypoints
  ${CMAKE_SOURCE_DIR}/src/game/OutdoorPvP
  ${CMAKE_SOURCE_DIR}/src/game/Petitions
  ${CMAKE_SOURCE_DIR}/src/game/Pools
  ${CMAKE_SOURCE_DIR}/src/game/PrecompiledHeaders
  ${CMAKE_SOURCE_DIR}/src/game/Quests
  ${CMAKE_SOURCE_DIR}/src/game/Reputation
  ${CMAKE_SOURCE_DIR}/src/game/Scripting
  ${CMAKE_SOURCE_DIR}/src/game/Server/Protocol
  ${CMAKE_SOURCE_DIR}/src/game/Server
  ${CMAKE_SOURCE_DIR}/src/game/Skills
  ${CMAKE_SOURCE_DIR}/src/game/Spells
  ${CMAKE_SOURCE_DIR}/src/game/Spells/Auras
  ${CMAKE_SOURCE_DIR}/src/game/Texts
  ${CMAKE_SOURCE_DIR}/src/game/Tools
  ${CMAKE_SOURCE_DIR}/src/game/Tickets
  ${CMAKE_SOURCE_DIR}/src/game/Warden
  ${CMAKE_SOURCE_DIR}/src/game/Warden/Modules
  ${CMAKE_SOURCE_DIR}/src/game/Weather
  ${CMAKE_SOURCE_DIR}/src/game/World
  ${CMAKE_SOURCE_DIR}/src/game/ArenaSpectator
  ${CMAKE_SOURCE_DIR}/src/game/Misc
  ${CMAKE_SOURCE_DIR}/src/scripts/
  ${CMAKE_SOURCE_DIR}/src/scripts/PrecompiledHeaders
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

add_library(Bots STATIC
  ${bot_STAT_SRCS}
  ${bot_STAT_PCH_SRC}
)

target_link_libraries(Bots
  ${MYSQL_LIBRARY})

if(UNIX)
  # Both systems don't have libdl and don't need them
  if (NOT (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "NetBSD"))
    target_link_libraries(${LIBRARY_NAME} dl)
  endif()
endif()

# Install config files
if( WIN32 )
  if ( MSVC )
    add_custom_command(TARGET Bots
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/aiplayerbot.conf.dist ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
    )
  elseif ( MINGW )
    add_custom_command(TARGET Bots
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/aiplayerbot.conf.dist ${CMAKE_BINARY_DIR}/bin/
    )
  endif()
endif()

# Generate PCH
if(PCH)
    ADD_CXX_PCH(Bots ${bots_PCH})
endif()
