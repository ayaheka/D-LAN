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
  
#ifndef TESTS_FILEMANAGER_HASHESRECEIVER_H
#define TESTS_FILEMANAGER_HASHESRECEIVER_H

#include <QObject>
#include <QList>

#include <Common/Hash.h>

class HashesReceiver : public QObject
{
   Q_OBJECT
public:
   HashesReceiver();
   bool waitToReceive(QList<Common::Hash>& hashes, int timeout);

public slots:
   void nextHash(Common::Hash hash);

private:
   QList<Common::Hash> receivedHashes;
   int num;
};

#endif