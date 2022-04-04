#ifndef CALCULATE_H
#define CALCULATE_H

#include <vector>
#include <utility>
#include <string>
#include <functional>
#include <sstream>

#include <iostream>

#include <boost/safe_numerics/safe_integer.hpp>

using namespace boost::safe_numerics;

class Calculate
{
public:
    enum class operations{
        zero,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,

        clear_all,
        plus,
        minus,
        multiplication,
        division,
        res,

        left_bracket,
        right_bracket,
        eval,
        backspace,
    };

private:



    using safe_int = safe<std::int32_t>;
    safe_int prev_num;
    safe_int cur_num;
    std::string on_display;


    std::string calculus(const operations & o)
    {
//        static operations x = operations::clear_all;

        using FType = void(*)(safe_int&, safe_int&);
        FType fclean = [](safe_int& x, safe_int& y){x = 0; y = 0;};
        FType fnone = [](safe_int& x, safe_int& y){x = y;};
        static FType flambda = fnone;
        try{
            if(on_display.length()>0)
                cur_num = std::stoi(on_display);
            std::stringstream sss;
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
                    (sss << prev_num);
                    on_display = sss.str();
                }
                on_display = on_display.substr(0, on_display.length()-1);
                return on_display;
            case operations::clear_all:
                fclean(prev_num, cur_num);
                flambda = fnone;
                sss << "";
                break;
            case operations::plus:
                flambda(prev_num, cur_num);
                flambda = [](safe_int& x, safe_int& y){x += y;};
                sss << prev_num;
                break;
            case operations::minus:
                flambda(prev_num, cur_num);
                flambda = [](safe_int& x, safe_int& y){x -= y;};
                sss << prev_num;
                break;
            case operations::multiplication:
                flambda(prev_num, cur_num);
                flambda = [](safe_int& x, safe_int& y){x *= y;};
                sss << prev_num;
                break;
            case operations::division:
                flambda(prev_num, cur_num);
                flambda = [](safe_int& x, safe_int& y){x /= y;};
                sss << prev_num;
                break;
            case operations::res:
                flambda(prev_num, cur_num);
                cur_num = prev_num;
                flambda = fnone;
                sss << prev_num;
                break;
            }
            on_display.clear();
            return sss.str();
        }
        catch(std::exception & e){
            flambda = fclean;
            on_display = e.what();
        }
        return on_display;
    }

public:
    Calculate();
    ~Calculate();

    std::string recive( enum operations o )
    {
        return calculus(o);
    }


};

#endif // CALCULATE_H
