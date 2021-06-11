/*! \file    main.cpp
 *  \brief   Entry point for the Pixie program.
 *  \author  Peter Chapin <chapinp@acm.org>
 *
 * LICENSE
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 * 
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Tasks.hpp"

using namespace std;

namespace {

    //! Splits the command line into separate words.
    /*!
     * This function does basic command line splitting based on the given delimiters.
     */
    static vector<string> split_string(
        const string  &buffer,         // String to be split.
        const char    *delimiters      // String of delimiter characters.
    )
    {
        enum State { START, IN_WORD };

        State             current_state = START;
        string::size_type buffer_offset;
        vector<string>    strings;

        buffer_offset = 0;
        while( buffer_offset != buffer.size( ) ) {
            char ch = buffer[buffer_offset];

            switch( current_state ) {
            case START:
                if( strchr( delimiters, ch ) != 0 ) {
                    current_state = START;
                }
                else {
                    current_state = IN_WORD;
                    strings.push_back( string( 1, ch ) );
                }
                break;

            case IN_WORD:
                if( strchr( delimiters, ch ) != 0 ) {
                    current_state = START;
                }
                else {
                    strings.back( ).append( 1, ch );
                }
                break;
            }

            buffer_offset++;
        }
        
        return strings;
     }


    bool process_command( const string &command_line )
    {
        vector<string> command_parts;
        vector<string>::size_type argument_count;

        command_parts = split_string( command_line, " " );
        argument_count = command_parts.size( );

        if( argument_count == 0 ) return true;

        if( command_parts[0] == "help" ) {
            cout << "quit                    : Terminate Pixie, saving automatically\n"
                 << "add task_no minutes     : Adds 'minutes' to task 'task_no'\n"
                 << "create task_name        : Creates a task 'task_name'. The name can contain spaces\n"
                 << "daily task_no minutes   : Sets task 'task_no' to have 'minutes' daily minutes\n"
                 << "delete task_no          : Deletes task 'task_no'\n"
                 << "priority task_no, pri   : Sets task 'task_no' to priority 'pri'\n"
                 << "rename task_no new_name : Changes task 'task_no' to the name 'new_name'\n"
                 << "save                    : Saves current state\n"
                 << "start task_no           : Starts task 'task_no'\n"
                 << "stop                    : Stops the currently running task\n"
                 << "undo_daily              : Removes one day's worth of daily accumulation from all tasks \n"
                 << "zero                    : Sets all times to zero \n";
            return true;
        }

        if( command_parts[0] == "quit" ) {
            return false;
        }
        else if( command_parts[0] == "add" ) {
            if( argument_count == 3 ) {
                add_minutes( atoi( command_parts[1].c_str( ) ), atoi( command_parts[2].c_str( ) ) );
            }
        }
        else if( command_parts[0] == "create" ) {
            // This is kind of hacked.
            const string::size_type index = command_line.find_first_of( ' ' );
            if( index != string::npos ) {
                create_task( command_line.substr( index + 1 ), 50 );
            }
        }
        else if( command_parts[0] == "daily" ) {
            if( argument_count == 3 ) {
                change_daily( atoi( command_parts[1].c_str( ) ), atoi( command_parts[2].c_str( ) ) );
            }
        }
        else if( command_parts[0] == "delete" ) {
            if( argument_count == 2 ) {
                delete_task( atoi( command_parts[1].c_str( ) ) );
            }
        }
        else if( command_parts[0] == "priority" ) {
            if( argument_count == 3 ) {
                change_priority( atoi( command_parts[1].c_str( ) ), atoi( command_parts[2].c_str( ) ) );
            }
        }
        else if( command_parts[0] == "rename" ) {
            // This is kind of hacked.
            string::size_type index = command_line.find_first_of( ' ' );
            index = command_line.find_first_of( ' ', index + 1 );
            if( index != string::npos ) {
                rename( atoi( command_parts[1].c_str( ) ), command_line.substr( index + 1 ) );
            }
        }
        else if( command_parts[0] == "save" ) {
            save_tasks( );
        }
        else if( command_parts[0] == "start" ) {
            if( argument_count == 2 ) {
                start_task( atoi( command_parts[1].c_str( ) ) );
            }
        }
        else if( command_parts[0] == "stop" ) {
            stop_tasks( );
        }
        else if( command_parts[0] == "undo_daily" ) {
            undo_daily( );
        }
        else if( command_parts[0] == "zero" ) {
            zero_tasks( );
        }

        return true;
    }
}


//! Pixie entry point.
int main( int argc, char **argv )
{
    string command_line;
    int    rc = EXIT_SUCCESS;
 
    try {
        initialize_tasks( );
        while( 1 ) {
            display_tasks( );
            cout << "> " << flush;
            getline( cin, command_line );
            if( !process_command( command_line ) ) break;
        }
        cleanup_tasks( );
    }
    catch( exception &e ) {
        cout << "Pixie: Unhandled standard exception reached main!\n"
             << "       (" << e.what( ) << ")\n";
        rc = EXIT_FAILURE;
    }
    catch( ... ) {
        cout << "Pixie: Unknown, unhandled exception reached main!\n";
        rc = EXIT_FAILURE;
    }
    return rc;
}
