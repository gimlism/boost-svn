//  (C) Copyright Gennadiy Rozental 2001-2003.
//  (C) Copyright Beman Dawes 2001.
//  Use, modification, and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : test failures reported by throwing the exception.
//  Should fail during run.
// ***************************************************************************

// Boost.Test
#include <boost/test/test_tools.hpp>

int test_main( int argc, char* [] )  // note the name
{
    BOOST_ERROR( "Msg" );

    if( argc > 0 ) // to prevent the unreachable return warning
        throw "Test error by throwing C-style string exception";

    return 0;
}

//____________________________________________________________________________//

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.11  2003/11/06 07:31:42  rogeeff
//  Licence update
//
//  Revision 1.10  2003/10/27 07:13:32  rogeeff
//  licence update
//
//  Revision 1.9  2003/09/14 12:42:22  beman_dawes
//  Change to new license (with Gennadiy's permission)
//
//  Revision 1.8  2003/06/09 09:25:24  rogeeff
//  1.30.beta1
//
//  Revision 1.7  2003/02/15 21:49:58  rogeeff
//  borland warning fix
//
//  Revision 1.6  2002/11/02 20:04:43  rogeeff
//  release 1.29.0 merged into the main trank
//

// ***************************************************************************

// EOF
