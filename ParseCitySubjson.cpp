// ������� ��� �������� ������
vector<Language> ParseLanguages(const Json& json)
{
    vector<Language> languages;
    for (const auto& lang_obj : json.AsList())
    {
        languages.push_back(FromString<Language>(lang_obj.AsString()));
    }
    return languages;
}

// ������� ��� �������� �������
void ParseCities(vector<City>& cities, const Json& json, const Country& country)
{
    for (const auto& city_json : json.AsList())
    {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({ city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),country.phone_code + city_obj["phone_code"s].AsString(), country.name, country.iso_code,country.time_zone, country.languages });
    }
}

// ������� ��� �������� �����
void ParseCountries(vector<Country>& countries, const Json& json)
{
    for (const auto& country_json : json.AsList())
    {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
            });
        Country& country = countries.back();
        country.languages = ParseLanguages(country_obj["languages"s]);
    }
}

// ������� ��� �������� JSON
void ParseJson(vector<Country>& countries, vector<City>& cities, const Json& json)
{
    ParseCountries(countries, json);
    for (Country& country : countries)
    {
        ParseCities(cities, country_obj["cities"s], country);
    }
}