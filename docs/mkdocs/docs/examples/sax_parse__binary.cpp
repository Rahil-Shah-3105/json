#include <iostream>
#include <iomanip>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// a simple event consumer that collects string representations of the passed
// values; note inheriting from json::json_sax_t is not required, but can
// help not to forget a required function
class sax_event_consumer : public json::json_sax_t
{
  public:
    std::vector<std::string> events;

    bool null() override
    {
		std::cerr << ">>> Entering null()" << std::endl;
        events.push_back("null()");
		std::cerr << "<<< Exiting null()" << std::endl;
        return true;
    }

    bool boolean(bool val) override
    {
		std::cerr << ">>> Entering boolean(val=" << val << ")" << std::endl;
        events.push_back("boolean(val=" + std::string(val ? "true" : "false") + ")");
		std::cerr << "<<< Exiting boolean(val=" << val << ")" << std::endl;
        return true;
    }

    bool number_integer(number_integer_t val) override
    {
		std::cerr << ">>> Entering number_integer(val=" << val << ")" << std::endl;
        events.push_back("number_integer(val=" + std::to_string(val) + ")");
		std::cerr << "<<< Exiting number_integer(val=" << val << ")" << std::endl;
        return true;
    }

    bool number_unsigned(number_unsigned_t val) override
    {
		std::cerr << ">>> Entering number_unsigned(val=" << val << ")" << std::endl;
        events.push_back("number_unsigned(val=" + std::to_string(val) + ")");
		std::cerr << "<<< Exiting number_unsigned(val=" << val << ")" << std::endl;
        return true;
    }

    bool number_float(number_float_t val, const string_t& s) override
    {
		std::cerr << ">>> Entering number_float(val=" << val << ",s=" << s << ")" << std::endl;
        events.push_back("number_float(val=" + std::to_string(val) + ", s=" + s + ")");
		std::cerr << "<<< Exiting number_float(val=" << val << ",s=" << s << ")" << std::endl;
        return true;
    }

    bool string(string_t& val) override
    {
		std::cerr << ">>> Entering string(val=" << val << ")" << std::endl;
        events.push_back("string(val=" + val + ")");
		std::cerr << "<<< Exiting string(val=" << val << ")" << std::endl;
        return true;
    }

    bool start_object(std::size_t elements) override
    {
		std::cerr << ">>> Entering start_object(elements=" << elements << ")" << std::endl;
        events.push_back("start_object(elements=" + std::to_string(elements) + ")");
		std::cerr << "<<< Exiting start_object(elements=" << elements << ")" << std::endl;
        return true;
    }

    bool end_object() override
    {
		std::cerr << ">>> Entering end_object()" << std::endl;
        events.push_back("end_object()");
		std::cerr << "<<< Exiting end_object()" << std::endl;
        return true;
    }

    bool start_array(std::size_t elements) override
    {
		std::cerr << ">>> Entering start_array(elements=" << elements << ")" << std::endl;
        events.push_back("start_array(elements=" + std::to_string(elements) + ")");
		std::cerr << "<<< Exiting start_array(elements=" << elements << ")" << std::endl;
        return true;
    }

    bool end_array() override
    {
		std::cerr << ">>> Entering end_array()" << std::endl;
        events.push_back("end_array()");
		std::cerr << "<<< Exiting end_array()" << std::endl;
        return true;
    }

    bool key(string_t& val) override
    {
		std::cerr << ">>> Entering key(val=" << val << ")" << std::endl;
        events.push_back("key(val=" + val + ")");
		std::cerr << "<<< Exiting key(val=" << val << ")" << std::endl;
        return true;
    }

    bool binary(json::binary_t& val) override
    {
		std::cerr << ">>> Entering binary(val=" << val << ")" << std::endl;
        events.push_back("binary(val=[...])");
		std::cerr << "<<< Exiting binary(val=" << val << ")" << std::endl;
        return true;
    }

    bool parse_error(std::size_t position, const std::string& last_token, const json::exception& ex) override
    {
		std::cerr << ">>> Entering parse_error(position=" << position << ",last_token=" << last_token << ",ex=" << ex << ")" << std::endl;
        events.push_back("parse_error(position=" + std::to_string(position) + ", last_token=" + last_token + ",\n            ex=" + std::string(ex.what()) + ")");
		std::cerr << "parse_error(position=" << position << ",last_token=" << last_token << ",ex=" << ex << "): ex → " << ex << std::endl;
		std::cerr << "<<< Exiting parse_error(position=" << position << ",last_token=" << last_token << ",ex=" << ex << ")" << std::endl;
        return false;
    }
};

int main()
{
	std::cerr << ">>> Entering main()" << std::endl;
    // CBOR byte string
    std::vector<std::uint8_t> vec = {{0x44, 0xcA, 0xfe, 0xba, 0xbe}};

    // create a SAX event consumer object
    sax_event_consumer sec;

    // parse CBOR
    bool result = json::sax_parse(vec, &sec, json::input_format_t::cbor);
	std::cerr << "main(): result → " << result << std::endl;

    // output the recorded events
    for (auto& event : sec.events)
    {
        std::cout << event << "\n";
    }

    // output the result of sax_parse
    std::cout << "\nresult: " << std::boolalpha << result << std::endl;
	std::cerr << "<<< Exiting main()" << std::endl;
}
