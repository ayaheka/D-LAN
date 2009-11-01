#ifndef COMMON_PERSISTANTDATA_H
#define COMMON_PERSISTANTDATA_H

#include <exception>
using namespace std;

#include <google/protobuf/message.h>

#include <QString>
#include <QByteArray>

namespace Common
{
   class UnknownValueException : public exception {};

   /**
     * Some little functions to persist data and retrieve it.
     * The data are persisted in the user directory.
     * The data are described by a Protocol Buffer message.
     * Theses functions can be used for the application settings.
     */
   class PersistantData
   {
   public:

      /**
        * Define a value associated to a name.
        * You may refer to the name policy of the platform. Try to avoir special characters or space.
        * You can use an extension in the name like "settings.conf".
        * @param name The name of the data
        * @param data The data to persist
        */
      static void setValue(const QString& name, const google::protobuf::Message& data);

      /**
        * Retrieve the data associated to a given name.
        * @param name The name of the data
        * @return the associated value
        * @exception UnknownValueException Throwed if the value doesn't exist
        */
      static void getValue(const QString& name, google::protobuf::Message& data);

      /**
        * Remove a data.
        * @return Return false if the data didn't exist.
        */
      static bool rmValue(const QString& name);

   private:
      static bool createApplicationFolder();

      static const QString APPLICATION_FOLDER_NAME;
      static const QString APPLICATION_FOLDER_PATH;
      static const QString TEMP_POSTFIX_TERM;
   };
}
#endif