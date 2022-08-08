#pragma once
#include <memory>
#include <mysql/jdbc.h>

class mysql_session
{
public:
  using connection_ptr         = std::unique_ptr<sql::Connection>;
  using statement_ptr          = std::unique_ptr<sql::Statement>;
  using prepared_statement_ptr = std::shared_ptr<sql::PreparedStatement>;

  explicit mysql_session(sql::ConnectOptionsMap& connection_properties)
    : connection(get_driver_instance()->connect(connection_properties))
  {}

  ~mysql_session()
  {
    if (not connection->isClosed())
      close();
  }

  mysql_session(connection_ptr&) = delete;
  void operator=(const connection_ptr&) = delete;

  connection_ptr::pointer get() const
  {
    return connection.get();
  }

  auto createStatement()
  {
    return statement_ptr(connection->createStatement());
  }

  auto prepareStatement(const sql::SQLString& sql)
  {
    return prepared_statement_ptr(connection->prepareStatement(sql));
  }

  auto executeQuery(const sql::SQLString& sql)
  {
    return createStatement()->executeQuery(sql);
  }

  auto executeUpdate(const sql::SQLString& sql)
  {
    return createStatement()->executeUpdate(sql);
  }

  auto execute(const sql::SQLString& sql)
  {
    return createStatement()->execute(sql);
  }

  void rollback()
  {
    connection->rollback();
  }

  void commit()
  {
    connection->commit();
  }

  void close()
  {
    connection->close();
  }

private:
  connection_ptr connection;
};

using mysql_session_ptr = std::unique_ptr<mysql_session>;

extern mysql_session_ptr session;
