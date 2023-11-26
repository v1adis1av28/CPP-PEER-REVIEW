DBHandler ConnectWithDataBase(string_view db_name, int db_connection_timeout, bool db_allow_exceptions, DBLogLevel db_log_level)
{
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s))
    {
        db = connector.ConnectTmp(db_name, db_connection_timeout);
    }
    else
    {
        db = connector.Connect(db_name, db_connection_timeout);
    }
    if (!db_allow_exceptions && !db.IsOK())
    {
        throw runtime_error("Failed to connect to the database");
    }
    return db;
}

DBQuery CreatePerformQuery(DBHandler& db, int min_age, int max_age, string_view name_filter)
{
    ostringstream query_str;
    query_str << "from Persons "s<< "select Name, Age "s<< "where Age between "s << min_age << " and "s << max_age << " "s<< "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());
    return query;
}

vector<Person> LoadPersons(DBHandler& db, DBQuery& query)
{
    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query))
    {
        persons.push_back({ move(name), age });
    }
    return persons;
}

vector<Person> LoadPersons(string_view db_name, int db_connection_timeout, bool db_allow_exceptions, DBLogLevel db_log_level, int min_age, int max_age, string_view name_filter)
{
    DBHandler db = ConnectWithDataBase(db_name, db_connection_timeout, db_allow_exceptions, db_log_level);
    DBQuery query = CreatePerformQuery(db, min_age, max_age, name_filter);
    return LoadPersons(db, query);
}