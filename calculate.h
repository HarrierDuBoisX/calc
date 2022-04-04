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


    std::string calculus(const operations & o);


public:
    Calculate();
    ~Calculate();

    std::string recive( enum operations o )
    {
        return calculus(o);
    }


};

#endif // CALCULATE_H
