/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    Autogenerated by MultiStageTable.py (Unicode multi-stage
    table builder) (c) Peter Kankowski, 2008
==============================================================================*/
#if !defined(BOOST_SPIRIT_UNICODE_CATEGORY_TABLES)
#include <boost/cstdint.hpp>

namespace boost { namespace spirit { namespace unicode
{
    enum category
    {
        /*[Cc]*/    other_control,
        /*[Cf]*/    other_format,
        /*[Cn]*/    other_not_assigned,         // (no characters in the file have this property)
        /*[Co]*/    other_private_use,
        /*[Cs]*/    other_surrogate,
        /*[Ll]*/    letter_lowercase,
        /*[Lm]*/    letter_modifier,
        /*[Lo]*/    letter_other,
        /*[Lt]*/    letter_titlecase,
        /*[Lu]*/    letter_uppercase,
        /*[Mc]*/    mark_spacing_combining,
        /*[Me]*/    mark_enclosing,
        /*[Mn]*/    mark_nonspacing,
        /*[Nd]*/    number_decimal_digit,
        /*[Nl]*/    number_letter,
        /*[No]*/    number_other,
        /*[Pc]*/    punctuation_connector,
        /*[Pd]*/    punctuation_dash,
        /*[Pe]*/    punctuation_close,
        /*[Pf]*/    punctuation_final_quote,    // (may behave like Ps or Pe depending on usage)
        /*[Pi]*/    punctuation_initial_quote,  // (may behave like Ps or Pe depending on usage)
        /*[Po]*/    punctuation_other,
        /*[Ps]*/    punctuation_open,
        /*[Sc]*/    symbol_currency,
        /*[Sk]*/    symbol_modifier,
        /*[Sm]*/    symbol_math,
        /*[So]*/    symbol_other,
        /*[Zl]*/    separator_line,
        /*[Zp]*/    separator_paragraph,
        /*[Zs]*/    separator_space        
    };
    
    category get_category(::boost::uint32_t ch);
}}}

#include "tables.hpp"
#endif