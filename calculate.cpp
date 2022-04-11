#include "calculate.h"
#include "parse.h"


std::string Calculate::calculus(const operations &o)
{
    using FType = void(*)(safe_int&, safe_int&);
    FType fclean = [](safe_int& x, safe_int& y){x = 0; y = 0;};
    FType fnone = [](safe_int& x, safe_int& y){x = y;};
    static FType flambda = fnone;
    try{
        if(on_display.length()>0)
            cur_num = std::stoi(on_display);
        std::stringstream helper_stream;
        switch(o){
        case operations::zero:
        case operations::one:
        case operations::two:
        case operations::three:
        case operations::four:
        case operations::five:
        case operations::six:
        case operations::seven:
        case operations::eight:
        case operations::nine:
            on_display += std::to_string(static_cast<int>(o));
            return on_display;
        case operations::backspace:
            if (on_display.empty() && prev_num != 0 )
            {
                (helper_stream << prev_num);
                on_display = helper_stream.str();
            }
            on_display = on_display.substr(0, on_display.length()-1);
            return on_display;
        case operations::clear_all:
            fclean(prev_num, cur_num);
            flambda = fnone;
            helper_stream << "";
            break;
        case operations::plus:
            flambda(prev_num, cur_num);
            flambda = [](safe_int& x, safe_int& y){x += y;};
            helper_stream << prev_num;
            break;
        case operations::minus:
            flambda(prev_num, cur_num);
            flambda = [](safe_int& x, safe_int& y){x -= y;};
            helper_stream << prev_num;
            break;
        case operations::multiplication:
            flambda(prev_num, cur_num);
            flambda = [](safe_int& x, safe_int& y){x *= y;};
            helper_stream << prev_num;
            break;
        case operations::division:
            flambda(prev_num, cur_num);
            flambda = [](safe_int& x, safe_int& y){x /= y;};
            helper_stream << prev_num;
            break;
        case operations::res:
            flambda(prev_num, cur_num);
            cur_num = prev_num;
            flambda = fnone;
            helper_stream << prev_num;
            break;
        }
        on_display.clear();
        return helper_stream.str();
    }
    catch(std::exception & e){
        flambda = fclean;
        on_display = e.what();
    }
    return on_display;
}

std::string Calculate::evalus(const operations &o)
{
    switch(o)
    {
    case operations::zero:
    case operations::one:
    case operations::two:
    case operations::three:
    case operations::four:
    case operations::five:
    case operations::six:
    case operations::seven:
    case operations::eight:
    case operations::nine:
        on_display += std::to_string(static_cast<int>(o));
        break;
    case operations::eval:
        on_display = std::to_string(parse());
        break;
    case operations::backspace:
    {
        size_t len = on_display.length();
        on_display = on_display.substr(0, (len>0)?len-1:0);
    }
        return on_display;
    case operations::clear_all:
        on_display.clear();
        break;
    case operations::plus:
        on_display += "+";
        break;
    case operations::minus:
        on_display += "-";
        break;
    case operations::multiplication:
        on_display += "*";
        break;
    case operations::division:
        on_display += "/";
        break;
    case operations::left_bracket:
        on_display += "(";
        break;
    case operations::right_bracket:
        on_display += ")";
        break;
    case operations::res:

        break;
    }
    return on_display;
}

int Calculate::parse()
{
    /*
    auto& calc = grammar::def_parse;    // Our grammar
    typedef std::string::const_iterator iterator_type;

    iterator_type iter = on_display.begin();
    iterator_type end = on_display.end();
    boost::spirit::x3::ascii::space_type space;

    int valu;
    bool r = phrase_parse(iter, end, calc, space, valu);

    if (r && iter == end)
    {
        //all ok parse
    }
*/
    namespace x3 = boost::spirit::x3;

    int32_t value{};
    if (!phrase_parse(on_display.begin(), on_display.end(), grammar::expr >> x3::eoi,
                    x3::space, value))
        throw std::runtime_error("error in expression");
    return value;
}

Calculate::Calculate()
    :prev_num(0)
    ,cur_num(0)
{

}

Calculate::~Calculate()
{

}
