#include <priv/UploadManager.h>
using namespace UM;

#include <Protos/core_protocol.pb.h>

#include <Common/ZeroCopyStreamQIODevice.h>
#include <Common/Settings.h>
#include <Core/FileManager/IChunk.h>
#include <Core/FileManager/Exceptions.h>
#include <Core/PeerManager/ISocket.h>

#include <priv/Log.h>
#include <priv/Uploader.h>

UploadManager::UploadManager(QSharedPointer<FM::IFileManager> fileManager, QSharedPointer<PM::IPeerManager> peerManager) :
   fileManager(fileManager), peerManager(peerManager)
{
   connect(this->peerManager.data(), SIGNAL(getChunk(Common::Hash, int, PM::ISocket*)), this, SLOT(getChunk(Common::Hash, int, PM::ISocket*)));
}

QList< QSharedPointer<IUpload> > UploadManager::getUploads()
{
   QList< QSharedPointer<IUpload> > uploads;

   for (QListIterator< QSharedPointer<Uploader> > i(this->uploaders); i.hasNext();)
      uploads << i.next();

   return uploads;
}

int UploadManager::getUploadRate() const
{
   int uploadRate = 0;
   for (QListIterator< QSharedPointer<Uploader> > i(this->uploaders); i.hasNext();)
      uploadRate += i.next()->getUploadRate();

   return uploadRate;
}

void UploadManager::getChunk(Common::Hash hash, int offset, PM::ISocket* socket)
{
   try
   {
      QSharedPointer<FM::IChunk> chunk = this->fileManager->getChunk(hash);

      Protos::Core::GetChunkResult result;
      result.set_status(Protos::Core::GetChunkResult_Status_OK);
      result.set_chunk_size(chunk->getKnownBytes());
      socket->send(0x52, result);

      QSharedPointer<Uploader> uploader = QSharedPointer<Uploader>(new Uploader(chunk, offset, socket));
      connect(uploader.data(), SIGNAL(uploadFinished(bool)), this, SLOT(uploadFinished(bool)), Qt::QueuedConnection);
      this->uploaders << uploader;
      uploader->start();
   }
   catch(FM::UnknownChunkException)
   {
      Protos::Core::GetChunkResult result;
      result.set_status(Protos::Core::GetChunkResult_Status_DONT_HAVE);
      socket->send(0x52, result);
      socket->finished();

      L_ERRO(QString("UploadManager::getChunk(..) : Chunk unknown : %1").arg(hash.toStr()));
   }
}

void UploadManager::uploadFinished(bool networkError)
{
   Uploader* uploader = dynamic_cast<Uploader*>(this->sender());

   L_DEBU(QString("Upload finished, chunk : %1").arg(uploader->getChunk()->toStr()));

   uploader->getSocket()->finished(networkError);
   for (QMutableListIterator< QSharedPointer<Uploader> > i(this->uploaders); i.hasNext();)
   {
      if (i.next().data() == uploader)
      {
         i.remove();
         break;
      }
   }
}
