#pragma once

class PreparedStatementQuery
{
	mysql_session::prepared_statement_ptr stmt{ nullptr };

public:
	PreparedStatementQuery()
	{}

	PreparedStatementQuery(const std::string& _query_text)
		: stmt{ session->prepareStatement(_query_text) }
	{}

	void setBigInt(unsigned int parameterIndex, const sql::SQLString& value)
	{
		stmt->setBigInt(parameterIndex, value);
	}

	void setBlob(unsigned int parameterIndex, std::istream* blob)
	{
		stmt->setBlob(parameterIndex, blob);
	}

	void setBoolean(unsigned int parameterIndex, bool value)
	{
		stmt->setBoolean(parameterIndex, value);
	}

	void setDateTime(unsigned int parameterIndex, const sql::SQLString& value)
	{
		stmt->setDateTime(parameterIndex, value);
	}

	void setDouble(unsigned int parameterIndex, double value)
	{
		stmt->setDouble(parameterIndex, value);
	}

	void setInt(unsigned int parameterIndex, int32_t value)
	{
		stmt->setInt(parameterIndex, value);
	}

	void setUInt(unsigned int parameterIndex, uint32_t value)
	{
		stmt->setUInt(parameterIndex, value);
	}

	void setInt64(unsigned int parameterIndex, int64_t value)
	{
		stmt->setInt64(parameterIndex, value);
	}

	void setUInt64(unsigned int parameterIndex, uint64_t value)
	{
		stmt->setUInt64(parameterIndex, value);
	}

	void setNull(unsigned int parameterIndex, int sqlType)
	{
		stmt->setNull(parameterIndex, sqlType);
	}

	void setString(unsigned int parameterIndex, const sql::SQLString& value)
	{
		stmt->setString(parameterIndex, value);
	}

	auto execute(const std::string& _query_text = "")
	{
		return _query_text.empty() ? stmt->execute() : stmt->execute(_query_text);
	}

	auto executeQuery(const std::string& _query_text = "")
	{
		return _query_text.empty() ? stmt->executeQuery() : stmt->executeQuery(_query_text);
	}

	auto executeUpdate(const std::string& _query_text = "")
	{
		return _query_text.empty() ? stmt->executeUpdate() : stmt->executeUpdate(_query_text);
	}

	void close()
	{
		stmt->close();
	}

	~PreparedStatementQuery()
	{
	}
};

using prepared_statement_query_ptr = std::shared_ptr<PreparedStatementQuery>;

class LFRTraits
{
protected:
	using xml_node = const pugi::xml_node&;
	using __GUID = std::pair<std::string, std::string>;
	using __GUID_cref = const __GUID&;

	bool checkCatalog(const std::string& table, const std::string& code)
	{
		std::stringstream query;
		query << "SELECT 1 FROM catalogues." << table << " WHERE code = '" << code << "'";

		if (session->executeQuery(query.str())->rowsCount())
			return true;

		return false;
	}

	auto createInsertPtr(const std::string& query_text)
	{
		std::string pfx{ "INSERT INTO resp_db." };
		pfx.append(query_text);

		return std::make_shared<PreparedStatementQuery>(pfx);
	}

	auto createSelectPtr(const std::string& query_text)
	{
		std::string pfx{ "SELECT * FROM resp_db." };
		pfx.append(query_text);

		return std::make_shared<PreparedStatementQuery>(pfx);
	}

	auto createUpdatePtr(const std::string& query_text)
	{
		std::string pfx{ "UPDATE resp_db." };
		pfx.append(query_text);

		return std::make_shared<PreparedStatementQuery>(pfx);
	}

	size_t getAttributesCount(xml_node node)
	{
		return std::distance(node.attributes().begin(), node.attributes().end());
	}

	size_t getNodesCount(xml_node node)
	{
		return std::distance(node.begin(), node.end());
	}

public:
	virtual ~LFRTraits();

	virtual void parse(std::shared_ptr<pugi::xml_document>) = 0;
	virtual void insert(const std::string&) = 0;
	
	static std::string getGUID()
	{
		return xg::newGuid().str();
	}
};
