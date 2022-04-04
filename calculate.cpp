#include "calculate.h"

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

Calculate::Calculate()
    :cur_num(0)
    ,prev_num(0)
{

}

Calculate::~Calculate()
{

}
