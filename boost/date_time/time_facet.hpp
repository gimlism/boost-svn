
#ifndef _DATE_TIME_FACET__HPP__
#define _DATE_TIME_FACET__HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author:  Martin Andrian, Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/date_facet.hpp"
#include <sstream>
#include <iomanip>
#include <exception>

namespace boost {
namespace date_time {

  template <class CharT>
  struct time_formats {
    public:
      typedef CharT char_type;
      static const char_type fractional_seconds_format[3];               // f
      static const char_type fractional_seconds_or_none_format[3];       // F
      static const char_type seconds_with_fractional_seconds_format[3];  // s
      static const char_type seconds_format[3];                          // S
      static const char_type standard_format[9];                         // x X
      static const char_type zone_abbrev_format[3];                      // z
      static const char_type zone_name_format[3];                        // Z
      static const char_type zone_iso_format[3];                         // q
      static const char_type zone_iso_extended_format[3];                // Q
      static const char_type duration_seperator[2];
      static const char_type iso_time_format_specifier[18];
      static const char_type iso_time_format_extended_specifier[22];
      //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
      static const char_type default_time_format[23]; 
      //default time_duration format is HH:MM:SS[.fff...]
      static const char_type default_time_duration_format[11];
  };

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::fractional_seconds_format[3] = {'%','f'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::fractional_seconds_or_none_format[3] = {'%','F'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::seconds_with_fractional_seconds_format[3] = 
    {'%','s'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::seconds_format[3] =  {'%','S'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  //time_formats<CharT>::standard_format[5] =  {'%','c',' ','%','z'};
  time_formats<CharT>::standard_format[9] =  {'%','x',' ','%','X',' ','%','z'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::zone_abbrev_format[3] =  {'%','z'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::zone_name_format[3] =  {'%','Z'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::zone_iso_format[3] =  {'%','q'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::zone_iso_extended_format[3] ={'%','Q'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::duration_seperator[2] =  {':'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::iso_time_format_specifier[18] =  
    {'%', 'Y', '%', 'm', '%', 'd', 'T', 
     '%', 'H', '%', 'M', '%', 'S', '%', 'F', '%','q' };

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::iso_time_format_extended_specifier[22] =  
    {'%', 'Y', '-', '%', 'm', '-', '%', 'd', ' ', 
     '%', 'H', ':', '%', 'M', ':', '%', 'S', '%', 'F','%','Q'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::default_time_format[23] = 
    {'%','Y','-','%','b','-','%','d',' ',
      '%','H',':','%','M',':','%','S','%','F',' ','%','z'};

  template <class CharT>  
  const typename time_formats<CharT>::char_type 
  time_formats<CharT>::default_time_duration_format[11] = 
    {'%','H',':','%','M',':','%','S','%','F'};



  /*! Facet used for format-based output of time types 
   * This class provides for the use of format strings to output times.  In addition
   * to the flags for formatting date elements, the following are the allowed format flags:
   *  - %x %X => default format - enables addition of more flags to default (ie. "%x %X %z")
   *  - %f => fractional seconds ".123456"
   *  - %F => fractional seconds or none: like frac sec but empty if frac sec == 0
   *  - %s => seconds w/ fractional sec "02.123" (this is the same as "%S%f) 
   *  - %S => seconds "02"
   *  - %z => abbreviated time zone "EDT"
   *  - %Z => full time zone name "Eastern Daylight Time"
   */
  template <class time_type,
            class CharT, 
            class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class time_facet : 
    public boost::date_time::date_facet<typename time_type::date_type , CharT, OutItrT> {
   public:
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;
    typedef boost::date_time::period<time_type,time_duration_type> period_type;
    typedef boost::date_time::date_facet<typename time_type::date_type, CharT, OutItrT> base_type;
    typedef typename base_type::string_type string_type;
    typedef typename base_type::char_type   char_type;
    typedef typename base_type::period_formatter_type period_formatter_type;
    typedef typename base_type::special_values_formatter_type special_values_formatter_type;
    typedef typename base_type::date_gen_formatter_type date_gen_formatter_type;
    static const char_type* fractional_seconds_format;                // f
    static const char_type* fractional_seconds_or_none_format;        // F
    static const char_type* seconds_with_fractional_seconds_format;   // s
    static const char_type* seconds_format;                           // S
    static const char_type* standard_format;                          // x X
    static const char_type* zone_abbrev_format;                       // z
    static const char_type* zone_name_format;                         // Z
    static const char_type* zone_iso_format;                          // q
    static const char_type* zone_iso_extended_format;                 // Q
    static const char_type* duration_seperator;
    static const char_type* iso_time_format_specifier;
    static const char_type* iso_time_format_extended_specifier;

    //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
    static const char_type* default_time_format; 
    //default time_duration format is HH:MM:SS[.fff...]
    static const char_type* default_time_duration_format;
    static std::locale::id id;

    //! sets default formats for ptime, local_date_time, and time_duration
    explicit time_facet(::size_t a_ref = 0) 
      //: base_type(standard_format),
      : base_type(default_time_format), 
        m_time_duration_format(default_time_duration_format),
        m_time_duration_seperator(duration_seperator)

    {
      set_duration_seperator_from_facet(); //todo fix this
    }

    //TODO sets time_dur to default - change to a custom?
    explicit time_facet(const char_type* a_format,
                        period_formatter_type period_formatter = period_formatter_type(), 
                        const special_values_formatter_type& special_value_formatter = special_values_formatter_type(), 
                        date_gen_formatter_type dg_formatter = date_gen_formatter_type(),
                         ::size_t a_ref = 0) 
      : base_type(a_format, 
                  period_formatter,
                  special_value_formatter, 
                  dg_formatter, 
                  a_ref),
        m_time_duration_format(default_time_duration_format),
        m_time_duration_seperator(duration_seperator)
    {}

    //! Changes format for time_duration
    void time_duration_format(const char_type* const format) {
      m_time_duration_format = format;
    }
    virtual void set_iso_format()
    {
      this->m_format = iso_time_format_specifier;
      //TODO: set time_dur format to iso spec too?
    }
    virtual void set_iso_extended_format()
    {
      this->m_format = iso_time_format_extended_specifier;
      //TODO: set time_dur format to iso_ext spec too?
    }

    OutItrT put(OutItrT a_next, 
                std::ios_base& a_ios, 
                char_type a_fill, 
                const time_type& a_time) const 
    {
      if (a_time.is_special()) { 
        return do_put_special(a_next, a_ios, a_fill, 
                              a_time.date().as_special());
      }
      string_type format(this->m_format);
      string_type frac_str;
      if (format.find(seconds_with_fractional_seconds_format)) {
        // replace %s with %S.nnn 
        frac_str = 
          fractional_seconds_as_string(a_time.time_of_day(), false);
        char_type sep = std::use_facet<std::numpunct<char_type> >(a_ios.getloc()).decimal_point();
        
        string_type replace_string(seconds_format);
        replace_string += sep;
        replace_string += frac_str;
        boost::algorithm::replace_all(format, 
                                      seconds_with_fractional_seconds_format, 
                                      replace_string);
      }
      if (format.find(zone_name_format)) {
        if(a_time.zone_name().empty()) {
          /* TODO: this'll probably create problems if a user places 
           * the zone_*_format flag in the format with a ptime. This 
           * code removes the flag from the default formats */

          // if zone_name() returns an empty string, we want to
          // erase zone_name_format & one preceeding space
          std::basic_stringstream<char_type> ss;
          ss << ' ' << zone_name_format;
          boost::algorithm::replace_all(format,
                                        ss.str(),
                                        "");
        }
        else{
          boost::algorithm::replace_all(format,
                                        zone_name_format,
                                        a_time.zone_name());
        }
      }
      if (format.find(zone_abbrev_format)) {
        if(a_time.zone_abbrev(false).empty()) {
          /* TODO: this'll probably create problems if a user places 
           * the zone_*_format flag in the format with a ptime. This 
           * code removes the flag from the default formats */

          // if zone_abbrev() returns an empty string, we want to
          // erase zone_abbrev_format & one preceeding space
          std::basic_stringstream<char_type> ss;
          ss << ' ' << zone_abbrev_format;
          boost::algorithm::replace_all(format,
                                        ss.str(),
                                        "");
        }
        else{
          boost::algorithm::replace_all(format,
                                        zone_abbrev_format,
                                        a_time.zone_abbrev(false));
        }
      }
      if (format.find(zone_iso_extended_format)) {
        if(a_time.zone_name(true).empty()) {
          /* TODO: this'll probably create problems if a user places 
           * the zone_*_format flag in the format with a ptime. This 
           * code removes the flag from the default formats */

          // if zone_name() returns an empty string, we want to
          // erase zone_iso_extended_format from format
          boost::algorithm::replace_all(format,
                                        zone_iso_extended_format,
                                        "");
        }
        else{
          boost::algorithm::replace_all(format,
                                        zone_iso_extended_format,
                                        a_time.zone_name(true));
        }
      }
      if (format.find(zone_iso_format)) {
        if(a_time.zone_abbrev(true).empty()) {
          /* TODO: this'll probably create problems if a user places 
           * the zone_*_format flag in the format with a ptime. This 
           * code removes the flag from the default formats */

          // if zone_abbrev() returns an empty string, we want to
          // erase zone_iso_format from format
          boost::algorithm::replace_all(format,
                                        zone_iso_format,
                                        "");
        }
        else{
          boost::algorithm::replace_all(format,
                                        zone_iso_format,
                                        a_time.zone_abbrev(true));
        }
      }
      if (format.find(fractional_seconds_format)) {
        // replace %f with nnnnnnn
        if (!frac_str.size()) {
          frac_str = fractional_seconds_as_string(a_time.time_of_day(), false);
        }
        boost::algorithm::replace_all(format,
                                      fractional_seconds_format, 
                                      frac_str);
      }

      if (format.find(fractional_seconds_or_none_format)) {
        // replace %F with nnnnnnn or nothing if fs == 0
        frac_str = 
          fractional_seconds_as_string(a_time.time_of_day(), true);
        if (frac_str.size()) {
          char_type sep = std::use_facet<std::numpunct<char_type> >(a_ios.getloc()).decimal_point();
          string_type replace_string;
          replace_string += sep;
          replace_string += frac_str;
          boost::algorithm::replace_all(format,
                                        fractional_seconds_or_none_format, 
                                        replace_string);
        }
        else {
          boost::algorithm::erase_all(format,
                                      fractional_seconds_or_none_format);
        }
      }

      return do_put_tm(a_next, a_ios, a_fill, 
                       to_tm(a_time), format);
    }

    //! put function for time_duration
    OutItrT put(OutItrT a_next, 
                std::ios_base& a_ios, 
                char_type a_fill, 
                const time_duration_type& a_time_dur) const 
    {
      if (a_time_dur.is_special()) { 
        return do_put_special(a_next, a_ios, a_fill, 
                              a_time_dur.get_rep().as_special());
      }

      string_type format(m_time_duration_format);
      string_type frac_str;
      if (format.find(seconds_with_fractional_seconds_format)) {
        // replace %s with %S.nnn 
        frac_str = 
          fractional_seconds_as_string(a_time_dur, false);
        char_type sep = std::use_facet<std::numpunct<char_type> >(a_ios.getloc()).decimal_point();
        
        string_type replace_string(seconds_format);
        replace_string += sep;
        replace_string += frac_str;
        boost::algorithm::replace_all(format, 
                                      seconds_with_fractional_seconds_format, 
                                      replace_string);
      }
      if (format.find(fractional_seconds_format)) {
        // replace %f with nnnnnnn
        if (!frac_str.size()) {
          frac_str = fractional_seconds_as_string(a_time_dur, false);
        }
        boost::algorithm::replace_all(format,
                                      fractional_seconds_format, 
                                      frac_str);
      }

      if (format.find(fractional_seconds_or_none_format)) {
        // replace %F with nnnnnnn or nothing if fs == 0
        frac_str = 
          fractional_seconds_as_string(a_time_dur, true);
        if (frac_str.size()) {
          char_type sep = std::use_facet<std::numpunct<char_type> >(a_ios.getloc()).decimal_point();
          string_type replace_string;
          replace_string += sep;
          replace_string += frac_str;
          boost::algorithm::replace_all(format,
                                        fractional_seconds_or_none_format, 
                                        replace_string);
        }
        else {
          boost::algorithm::erase_all(format,
                                      fractional_seconds_or_none_format);
        }
      }

      return do_put_tm(a_next, a_ios, a_fill, 
                       to_tm(a_time_dur), format);
    }
    
    OutItrT put(OutItrT next, std::ios_base& a_ios, 
                char_type fill, const period_type& p) const 
    {
      return this->m_period_formatter.put_period(next, a_ios, fill,p,*this);
    }


  protected:

    static 
    string_type 
    fractional_seconds_as_string(const time_duration_type& a_time,
                                 bool null_when_zero) 
    {
      typename time_duration_type::fractional_seconds_type frac_sec = 
        a_time.fractional_seconds();

      if (null_when_zero && (frac_sec == 0)) {
        return string_type();
      }

      std::basic_ostringstream<char_type> ss;
      ss.imbue(std::locale::classic()); // don't want any formatting
      ss << std::setw(time_duration_type::num_fractional_digits())
         << std::setfill(static_cast<char_type>('0'));
#if (defined(BOOST_MSVC) && (_MSC_VER <= 1200))  // 1200 == VC++ 6.0
      // JDG [7/6/02 VC++ compatibility]
      char_type buff[34];
      ss << _i64toa(static_cast<boost::int64_t>(frac_sec), buff, 10);
#else
      ss << frac_sec;
#endif
      return ss.str();
    }

  private:
    //! Use the std facet to figure out the seperator
    /*! Simple algorithm here -- print as %X time and search for 
     *  non-numeric character.  This is assumed to be seperator. 
     *  Would be better if the standard facet was enhanced.
     */
    void set_duration_seperator_from_facet() 
    {
      //TODO write this function
    }
    string_type m_time_duration_format;
    string_type m_time_duration_seperator;

  };
  
  template <class time_type, class CharT, class OutItrT>  
  std::locale::id time_facet<time_type, CharT, OutItrT>::id;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type* 
  time_facet<time_type, CharT, OutItrT>::fractional_seconds_format = time_formats<CharT>::fractional_seconds_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type* 
  time_facet<time_type, CharT, OutItrT>::fractional_seconds_or_none_format = time_formats<CharT>::fractional_seconds_or_none_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type* 
  time_facet<time_type, CharT, OutItrT>::seconds_with_fractional_seconds_format = 
    time_formats<CharT>::seconds_with_fractional_seconds_format;


  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_name_format =  time_formats<CharT>::zone_name_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_abbrev_format =  time_formats<CharT>::zone_abbrev_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_iso_extended_format =time_formats<CharT>::zone_iso_extended_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::zone_iso_format =  time_formats<CharT>::zone_iso_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::seconds_format =  time_formats<CharT>::seconds_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::standard_format =  time_formats<CharT>::standard_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::duration_seperator =  time_formats<CharT>::duration_seperator;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type,CharT, OutItrT>::char_type*
  time_facet<time_type,CharT, OutItrT>::iso_time_format_specifier = time_formats<CharT>::iso_time_format_specifier;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::iso_time_format_extended_specifier = time_formats<CharT>::iso_time_format_extended_specifier;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type*
  time_facet<time_type, CharT, OutItrT>::default_time_format = 
    time_formats<CharT>::default_time_format;

  template <class time_type, class CharT, class OutItrT>  
  const typename time_facet<time_type, CharT, OutItrT>::char_type* 
  time_facet<time_type, CharT, OutItrT>::default_time_duration_format = 
    time_formats<CharT>::default_time_duration_format;


  //! Facet for format-based input.  
  /*!
   */
  template <class time_type,
            class CharT, 
            class InItrT = std::istreambuf_iterator<CharT, std::char_traits<CharT> > >
  class time_input_facet : 
    public boost::date_time::date_input_facet<typename time_type::date_type , CharT, InItrT> {
    public:
      typedef typename time_type::date_type date_type;
      typedef typename time_type::time_duration_type time_duration_type;
      typedef typename time_duration_type::fractional_seconds_type fracional_seconds_type;
      typedef boost::date_time::period<time_type,time_duration_type> period_type;
      typedef boost::date_time::date_input_facet<typename time_type::date_type, CharT, InItrT> base_type;
      typedef typename base_type::duration_type date_duration_type;
      typedef typename base_type::year_type year_type;
      typedef typename base_type::month_type month_type;
      typedef typename base_type::day_type day_type;
      typedef typename base_type::string_type string_type;
      typedef typename string_type::const_iterator const_itr;
      typedef typename base_type::char_type   char_type;
      typedef typename base_type::format_date_parser_type format_date_parser_type;
      typedef typename base_type::period_parser_type period_parser_type;
      typedef typename base_type::special_values_parser_type special_values_parser_type;
      typedef typename base_type::date_gen_parser_type date_gen_parser_type;
      typedef typename base_type::special_values_parser_type::match_results match_results;

      static const char_type* fractional_seconds_format;                // f
      static const char_type* fractional_seconds_or_none_format;        // F
      static const char_type* seconds_with_fractional_seconds_format;   // s
      static const char_type* seconds_format;                           // S
      static const char_type* standard_format;                          // x X
      static const char_type* zone_abbrev_format;                       // z
      static const char_type* zone_name_format;                         // Z
      static const char_type* zone_iso_format;                          // q
      static const char_type* zone_iso_extended_format;                 // Q
      static const char_type* duration_seperator;
      static const char_type* iso_time_format_specifier;
      static const char_type* iso_time_format_extended_specifier;
      static const char_type* default_time_format; 
      static const char_type* default_time_duration_format;
      static std::locale::id id;

      //! Constructor that takes a format string for a ptime
      explicit time_input_facet(const string_type& format, ::size_t a_ref = 0) 
        : base_type(format, a_ref), 
          m_time_duration_format(default_time_duration_format),
          m_time_duration_seperator(duration_seperator)
      { }

      explicit time_input_facet(const string_type& format,
                                const format_date_parser_type& date_parser,
                                const special_values_parser_type& sv_parser,
                                const period_parser_type& per_parser,
                                const date_gen_parser_type& date_gen_parser,
                                ::size_t a_ref = 0)
        : base_type(format,
                    date_parser,
                    sv_parser,
                    per_parser,
                    date_gen_parser,
                    a_ref), 
          m_time_duration_format(default_time_duration_format),
          m_time_duration_seperator(duration_seperator)
      {}

      //! sets default formats for ptime, local_date_time, and time_duration
      explicit time_input_facet(::size_t a_ref = 0) 
        : base_type(default_time_format, a_ref), 
          m_time_duration_format(default_time_duration_format),
          m_time_duration_seperator(duration_seperator)
      { }
      
      //! Set the format for time_duration
      void time_duration_format(const char_type* const format) {
        m_time_duration_format = format;
      }
      
      InItrT get(InItrT& sitr,
                 InItrT& stream_end,
                 std::ios_base& a_ios,
                 period_type& p) const
      {
        p = this->m_period_parser.get_period(sitr, 
                                             stream_end, 
                                             a_ios, 
                                             p, 
                                             time_duration_type::unit(), 
                                             *this);
        return sitr;
      }
      
      //default ptime format is YYYY-Mon-DD HH:MM:SS[.fff...][ zzz]
      //default time_duration format is %H:%M:%S%F HH:MM:SS[.fff...]

      InItrT get(InItrT& sitr, 
                 InItrT& stream_end, 
                 std::ios_base& a_ios, 
                 time_duration_type& td) const
      {
        // skip leading whitespace
        while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
        
        bool use_current_char = false;
        
        // num_get will consume the +/-, we may need a copy if special_value
        char_type c = '\0';
        if(*sitr == '-' || *sitr == '+') {
          c = *sitr;
        }
        
        long hour = 0; 
        long min = 0; 
        long sec = 0; 
        typename time_duration_type::fractional_seconds_type frac(0);
        
        typedef std::num_get<CharT, InItrT> num_get;
        if(!std::has_facet<num_get>(a_ios.getloc())) {
          num_get* ng = new num_get();
          std::locale loc = std::locale(a_ios.getloc(), ng);
          a_ios.imbue(loc);
        }
       
        const_itr itr(m_time_duration_format.begin());
        while (itr != m_time_duration_format.end() && (sitr != stream_end)) {
          if (*itr == '%') {
            itr++;
            if (*itr != '%') { //ignore '%%'
              std::ios_base::iostate err = std::ios_base::goodbit;
              switch(*itr) {
              case 'H': 
                {
                  sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, hour);
                  if(err & std::ios_base::failbit){
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'M': 
                {
                  sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, min);
                  if(err & std::ios_base::failbit){
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'S': 
                {
                  sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, sec);
                  if(err & std::ios_base::failbit){
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 's':
                {
                  sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, sec);
                  if(err & std::ios_base::failbit){
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  // %s is the same as %S%f so we drop through into %f
                  //break;
                }
              case 'f':
                {
                  // check for decimal, check special_values if missing
                  if(*sitr == '.') {
                    ++sitr;
                    parse_frac_type(sitr, stream_end, frac);
                    // sitr will point to next expected char after this parsing 
                    // is complete so no need to advance it
                    use_current_char = true;
                  }
                  else {
                    return check_special_value(sitr, stream_end, td, c);
                  }
                  break;
                }
              case 'F': 
                {
                  // check for decimal, skip if missing
                  if(*sitr == '.') {
                    ++sitr;
                    parse_frac_type(sitr, stream_end, frac);
                    // sitr will point to next expected char after this parsing 
                    // is complete so no need to advance it
                    use_current_char = true;
                  }
                  else {
                    // nothing was parsed so we don't want to advance sitr
                    use_current_char = true;
                  }
                  break;
                }
              default:
                {} // ignore what we don't understand?
              }// switch
            }
        
            itr++; //advance past format specifier
          }
          else {  //skip past chars in format and in buffer
            itr++;
            // set use_current_char when sitr is already 
            // pointing at the next character to process
            if (use_current_char) {
              use_current_char = false;
            }
            else {
              sitr++;
            }
          }
        }

        td = time_duration_type(hour, min, sec, frac);
        return sitr;
      }
    

      InItrT get(InItrT& sitr, 
                 InItrT& stream_end, 
                 std::ios_base& a_ios, 
                 time_type& t) const
      {
        // skip leading whitespace
        while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
        
        // num_get should consume the sign & HH, then stop.
        // use technique for iterating format in format_date_parser(while loop)

        bool use_current_char = false;
        
        // num_get will consume the +/-, we may need a copy if special_value
        char_type c = '\0';
        if(*sitr == '-' || *sitr == '+') {
          c = *sitr;
        }
       
        // time elements
        long hour = 0; 
        long min = 0; 
        long sec = 0; 
        typename time_duration_type::fractional_seconds_type frac(0);
        // date elements
        short /*year(0), month(0), day(0),*/ day_of_year(0);
        /* Initialized the following to their minimum values. These intermediate 
         * objects are used so we get specific exceptions when part of the input 
         * is unparsable. 
         * Ex: "205-Jan-15" will throw a bad_year, "2005-Jsn-15"- bad_month, etc.*/
        year_type t_year(1400);
        month_type t_month(1);
        day_type t_day(1);
        
        typedef std::num_get<CharT, InItrT> num_get;
        if(!std::has_facet<num_get>(a_ios.getloc())) {
          num_get* ng = new num_get();
          std::locale loc = std::locale(a_ios.getloc(), ng);
          a_ios.imbue(loc);
        }
       
        const_itr itr(this->m_format.begin());
        while (itr != this->m_format.end() && (sitr != stream_end)) {
          if (*itr == '%') {
            itr++;
            if (*itr != '%') { //ignore '%%'
              std::ios_base::iostate err = std::ios_base::goodbit;
              // the cases are grouped by date & time flags - not alphabetical order
              switch(*itr) {
                // date flags
                case 'Y':
                case 'y':
                  {
                    char_type cs[3] = { '%', *itr };
                    string_type s(cs);
                    match_results mr;
                    try {
                      t_year = this->m_parser.parse_year(sitr, stream_end, s, mr);
                    }
                    catch(std::out_of_range bad_year) { // base class for bad_year exception
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_year
                      }
                    }
                    break;
                  }
                case 'B':
                case 'b':
                case 'm':
                  {
                    char_type cs[3] = { '%', *itr };
                    string_type s(cs);
                    match_results mr;
                    try {
                      t_month = this->m_parser.parse_month(sitr, stream_end, s, mr);
                    }
                    catch(std::out_of_range bad_month) { // base class for bad_month exception
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_year
                      }
                    }
                    // did m_parser already advance sitr to next char?
                    if(mr.has_remaining()) {
                      use_current_char = true;
                    }
                    break;
                  }
                case 'j':
                  {
                    // code that gets julian day (from format_date_parser)
                    match_results mr;
                    day_of_year = fixed_string_to_int<unsigned short, CharT>(sitr, stream_end, mr, 3);
                    if(day_of_year == -1) {
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                    }
                    // these next two lines are so we get an exception with bad input
                    typedef typename time_type::date_type::day_of_year_type day_of_year_type;
                    day_of_year_type t_day_of_year(day_of_year);
                    break;
                  }
                case 'd':
                  {
                    try {
                      t_day = this->m_parser.parse_day_of_month(sitr, stream_end);
                    }
                    catch(std::out_of_range bad_day_of_month) { // base class for exception
                      match_results mr;
                      if(this->m_sv_parser.match(sitr, stream_end, mr)) {
                        t = time_type(static_cast<special_values>(mr.current_match));
                        return sitr;
                      }
                      else {
                        throw; // rethrow bad_year
                      }
                    }
                    break;
                  }
                // time flags
                case 'H': 
                  {
                    sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, hour);
                    if(err & std::ios_base::failbit){
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 'M': 
                  {
                    sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, min);
                    if(err & std::ios_base::failbit){
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 'S': 
                  {
                    sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, sec);
                    if(err & std::ios_base::failbit){
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 's':
                  {
                    sitr = std::use_facet<num_get>(a_ios.getloc()).get(sitr, stream_end, a_ios, err, sec);
                    if(err & std::ios_base::failbit){
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    // %s is the same as %S%f so we drop through into %f
                    //break;
                  }
                case 'f':
                  {
                    // check for decimal, check SV if missing
                    if(*sitr == '.') {
                      ++sitr;
                      parse_frac_type(sitr, stream_end, frac);
                      // sitr will point to next expected char after this parsing 
                      // is complete so no need to advance it
                      use_current_char = true;
                    }
                    else {
                      return check_special_value(sitr, stream_end, t, c);
                    }
                    break;
                  }
                case 'F': 
                  {
                    // check for decimal, skip if missing
                    if(*sitr == '.') {
                      ++sitr;
                      parse_frac_type(sitr, stream_end, frac);
                      // sitr will point to next expected char after this parsing 
                      // is complete so no need to advance it
                      use_current_char = true;
                    }
                    else {
                      // nothing was parsed so we don't want to advance sitr
                      use_current_char = true;
                    }
                    break;
                  }
                default:
                {} // ignore what we don't understand?
              }// switch
            }
        
            itr++; //advance past format specifier
          }
          else {  //skip past chars in format and in buffer
            itr++;
            // set use_current_char when sitr is already 
            // pointing at the next character to process
            if (use_current_char) {
              use_current_char = false;
            }
            else {
              sitr++;
            }
          }
        }
        
        date_type d(not_a_date_time);
        if (day_of_year > 0) {
          d = date_type(t_year-1,12,31) + date_duration_type(day_of_year);
        }
        else {
          d = date_type(t_year, t_month, t_day);
        }

        time_duration_type td(hour, min, sec, frac);
        t = time_type(d, td);
        return sitr;
      }

    protected:

      //! Helper function to check for special_value
      /*! First character may have been consumed during original parse 
       * attempt. Parameter 'c' should be a copy of that character. 
       * Throws ios_base::failure if parse fails. */
      template<class temporal_type>
      inline
      InItrT check_special_value(InItrT& sitr,InItrT& stream_end, temporal_type& tt, char_type c='\0') const
      {
        match_results mr;
        if((c == '-' || c == '+') && (*sitr != c)) { // was the first character consumed?
          mr.cache += c;
        }
        this->m_sv_parser.match(sitr, stream_end, mr);
        if(mr.current_match == match_results::PARSE_ERROR) {
          throw std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'");
        }
        tt = temporal_type(static_cast<special_values>(mr.current_match)); 
        return sitr;
      }

      //! Helper function for parsing a fractional second type from the stream
      void parse_frac_type(InItrT& sitr, 
                           InItrT& stream_end, 
                           fracional_seconds_type& frac) const
      {
        string_type cache;
        while(std::isdigit(*sitr) && sitr != stream_end) {
          cache += *sitr;
          ++sitr;
        }
        if(cache.size() > 0) {
          unsigned short precision = time_duration_type::num_fractional_digits();
          // input may be only the first few decimal places
          if(cache.size() < precision) {
            frac = lexical_cast<fracional_seconds_type>(cache);
            frac = decimal_adjust(frac, precision - cache.size());
          }
          else {
            // if input has too many decimal places, drop excess digits
            frac = lexical_cast<fracional_seconds_type>(cache.substr(0, precision));
          }
        }
      }
      
    private:
      string_type m_time_duration_format;
      string_type m_time_duration_seperator; // TODO is this necessary? Doesn't it just get skipped while parsing the input?

      //! Helper function to adjust trailing zeros when parsing fractional digits
      template<class int_type>
      inline
      int_type decimal_adjust(int_type val, const unsigned short places) const
      {
        unsigned long factor = 1;
        for(int i = 0; i < places; ++i){
          factor *= 10; // shift decimal to the right
        }
        return val * factor;
      }

  };

template <class time_type, class CharT, class InItrT>
  std::locale::id time_input_facet<time_type, CharT, InItrT>::id;

template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::fractional_seconds_format = time_formats<CharT>::fractional_seconds_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::fractional_seconds_or_none_format = time_formats<CharT>::fractional_seconds_or_none_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::seconds_with_fractional_seconds_format = time_formats<CharT>::seconds_with_fractional_seconds_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::seconds_format = time_formats<CharT>::seconds_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::standard_format = time_formats<CharT>::standard_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::zone_abbrev_format = time_formats<CharT>::zone_abbrev_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::zone_name_format = time_formats<CharT>::zone_name_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::zone_iso_format = time_formats<CharT>::zone_iso_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::zone_iso_extended_format = time_formats<CharT>::zone_iso_extended_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::duration_seperator = time_formats<CharT>::duration_seperator;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::iso_time_format_specifier = time_formats<CharT>::iso_time_format_specifier;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::iso_time_format_extended_specifier = time_formats<CharT>::iso_time_format_extended_specifier;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::default_time_format = time_formats<CharT>::default_time_format;

  template <class time_type, class CharT, class InItrT>  
  const typename time_input_facet<time_type, CharT, InItrT>::char_type* 
  time_input_facet<time_type, CharT, InItrT>::default_time_duration_format = time_formats<CharT>::default_time_duration_format;


} } // namespaces


#endif
