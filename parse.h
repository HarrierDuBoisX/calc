#pragma once

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <iostream>
#include <string>
#include <list>
//#include <numeric>


namespace grammar
{

namespace x3 = boost::spirit::x3;

using i32 = int32_t;


x3::rule<struct expr, i32> const   expr{"expr"};
x3::rule<struct simple, i32> const simple{"simple"};
x3::rule<struct factor, i32> const factor{"factor"};

auto assign = [](auto& ctx) { _val(ctx) = _attr(ctx); };

#define BINOP(op, rhs) (x3::lit(#op) >> x3::as_parser(rhs) \
    [([](auto& ctx) { _val(ctx) = _val(ctx) op _attr(ctx); })])

auto simple_def = x3::double_ | '(' >> expr >> ')';

auto factor_def = simple[assign] >>
    *(BINOP(*, factor)
    | BINOP(/, factor)
    | BINOP(%, factor));

auto expr_def = factor[assign] >>
    *(BINOP(+, expr)
    | BINOP(-, expr));

BOOST_SPIRIT_DEFINE(expr, factor, simple)

}

