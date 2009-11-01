#include "PersistantData.h"
using namespace Common;

#include <fstream>
using namespace std;

#include <QDir>
#include <QtDebug>

#include <google/protobuf/text_format.h>
#if DEBUG
#  include <google/protobuf/io/zero_copy_stream_impl.h>
#endif

void PersistantData::setValue(const QString& name, const google::protobuf::Message& data)
{
   if (PersistantData::createApplicationFolder())
   {
      QString tempName(name + TEMP_POSTFIX_TERM);

      ofstream file((APPLICATION_FOLDER_PATH + QDir::separator() + tempName).toStdString().data(), ios_base::binary | ios_base::out);
      // if (file.fail()) // TODO : check if failure

#if DEBUG
      google::protobuf::io::OstreamOutputStream zeroCopyStream(&file);
      google::protobuf::TextFormat::Print(data, &zeroCopyStream);
#else
      data.SerializeToOstream(&file);
#endif

      file.close(); // We have to close before renaming.

      // TODO : Some data loss can occure here, we must remove the file first
      // because 'rename' cannot overwrite an existing file.
      QFile::remove(APPLICATION_FOLDER_PATH + QDir::separator() + name);
      QFile::rename(APPLICATION_FOLDER_PATH + QDir::separator() + tempName, APPLICATION_FOLDER_PATH + QDir::separator() + name);
   }
}

void PersistantData::getValue(const QString& name, google::protobuf::Message& data)
{
   ifstream file((APPLICATION_FOLDER_PATH + QDir::separator() + name).toStdString().data(), ios_base::binary | ios_base::in);
   if (file.fail())
      throw UnknownValueException();

#if DEBUG
      google::protobuf::io::IstreamInputStream zeroCopyStream(&file);
      google::protobuf::TextFormat::Parse(&zeroCopyStream, &data);
#else
      data.ParseFromIstream(&file);
#endif
}

bool PersistantData::rmValue(const QString& name)
{
   return QFile::remove(APPLICATION_FOLDER_PATH + QDir::separator() + name);
}

bool PersistantData::createApplicationFolder()
{
   if (!QDir::home().exists(APPLICATION_FOLDER_NAME))
      return QDir::home().mkdir(APPLICATION_FOLDER_NAME);

   return true;
}

const QString PersistantData::APPLICATION_FOLDER_NAME(".aybabtu");
const QString PersistantData::APPLICATION_FOLDER_PATH(QDir::homePath() + QDir::separator() + APPLICATION_FOLDER_NAME);
const QString PersistantData::TEMP_POSTFIX_TERM(".temp");

