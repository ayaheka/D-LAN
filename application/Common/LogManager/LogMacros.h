/**
  * Aybabtu - A decentralized LAN file sharing software.
  * Copyright (C) 2010-2011 Greg Burri <greg.burri@gmail.com>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  
// See examples of using in the components as FileManager.
struct Log { static QSharedPointer<LM::ILogger> logger; };
#define L_USER(mess) LOG_USER(Log::logger, mess)
#define L_DEBU(mess) LOG_DEBU(Log::logger, mess)
#define L_WARN(mess) LOG_WARN(Log::logger, mess)
#define L_ERRO(mess) LOG_ERRO(Log::logger, mess)
#define L_FATA(mess) LOG_FATA(Log::logger, mess)